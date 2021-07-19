#include <stdint.h>
#include "mmf2_module.h"
#include "module_obj_detect.h"
#include "object_detection.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
//------------------------------------------------------------------------------


void obj_detect_thread(void *param)
{
    obj_detect_ctx_t *ctx = (obj_detect_ctx_t *)param;
    
    //printf("start_obj_detect_thread (w,h) = (%d, %d)\n",ctx->params.width, ctx->params.height);
    
    object_detection_setup(ctx->selected_model);
    
    while(1){
        ctx->hold_image_flag = 1;
        
        //check hold image done
        while(1){
            if(xSemaphoreTake(ctx->hold_image_sema, portMAX_DELAY) == pdTRUE)
                break;
        }
   
        if(ctx->hold_image_address != NULL && ctx->params.width != 0 && ctx->params.height != 0){
            //without padding 0
            object_detection(ctx->hold_image_address, ctx->params.width, ctx->params.height, 1, ctx->box.output_boxes, ctx->box.output_classes, ctx->box.output_scores, ctx->box.output_num_detections, 1);
        }
        //vTaskDelay(100);
    }
	vTaskDelete(NULL);
}

void start_obj_detect_thread(obj_detect_ctx_t *ctx){
    //recognition thread
    if(ctx->selected_model < 0){
        printf("please select a model\n");
        return;    
    }
    
    if(xTaskCreate(obj_detect_thread, ((const char*)"obj_detect_thread"), 512, ctx, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(obj_detect_thread) failed", __FUNCTION__);
}

int obj_detect_handle(void* p, void* input, void* output)
{
    obj_detect_ctx_t *ctx = (obj_detect_ctx_t*)p;
	mm_queue_item_t* input_item = (mm_queue_item_t*)input;
	mm_queue_item_t* output_item = (mm_queue_item_t*)output;
	uint8_t* input_buf = (uint8_t*)input_item->data_addr;
	uint8_t* output_buf = (uint8_t*)output_item->data_addr;
    
    if(ctx->hold_image_flag && ctx->set_detect == 1){
        //printf("\n..........hold_imageing............\n");
        memcpy(ctx->hold_image_address, input_item->data_addr, input_item->size);
        
        ctx->hold_image_flag = 0;
        xSemaphoreGive(ctx->hold_image_sema);
    }
        
	return output_item->size;
}

int obj_detect_control(void *p, int cmd, int arg)
{
	obj_detect_ctx_t *ctx = (obj_detect_ctx_t*)p;
	
	switch(cmd){	
	case CMD_OBJ_DETECT_SET_HEIGHT:
		ctx->params.height = arg;
		break;
	case CMD_OBJ_DETECT_SET_WIDTH:
		ctx->params.width = arg;
		break;
	case CMD_OBJ_DETECT_SET_PARAMS:
		memcpy(&ctx->params, ((obj_detect_params_t*)arg), sizeof(obj_detect_params_t));
		break;
	case CMD_OBJ_DETECT_GET_PARAMS:
		memcpy(((obj_detect_params_t*)arg), &ctx->params, sizeof(obj_detect_params_t));
		break;
    case CMD_OBJ_DETECT_SET_DETECT:
		ctx->set_detect = arg;
        if(ctx->set_detect){
            if(!ctx->hold_image_address)
                ctx->hold_image_address = (uint8_t*) malloc(ctx->params.height * ctx->params.width * 3 / 2);//YUV420
            if(!ctx->hold_image_address)
                printf("ctx->hold_image_address malloc failed\n");
            
            ctx->hold_image_sema = xSemaphoreCreateBinary();
            start_obj_detect_thread(ctx);
        }
        break;
    case CMD_OBJ_DETECT_GET_BOX:
        memcpy(((Boxes*)arg), &ctx->box, sizeof(Boxes));
        break;
    case CMD_OBJ_DETECT_FACE:
        ctx->selected_model = face_224_025_int8_post;
		break;
    case CMD_OBJ_DETECT_HUMAN:
        ctx->selected_model = human_224_025_int8_post;
		break;
	}
    return 0;
}

void* obj_detect_destroy(void* p)
{
	obj_detect_ctx_t *ctx = (obj_detect_ctx_t*)p;
    
    if(ctx->hold_image_sema) {
		vSemaphoreDelete(ctx->hold_image_sema);
		ctx->hold_image_sema = NULL;
    }
    if(ctx->hold_image_address)
        free(ctx->hold_image_address);
    
    if(ctx) free(ctx);
    
    return NULL;
}

void* obj_detect_create(void* parent)
{
    obj_detect_ctx_t *ctx = (obj_detect_ctx_t *)malloc(sizeof(obj_detect_ctx_t));
    if(!ctx) return NULL;
    memset(ctx, 0, sizeof(obj_detect_ctx_t));
    ctx->parent = parent;
    ctx->hold_image_address = NULL;
    
    return ctx;
}

void* obj_detect_new_item(void *p)
{
	obj_detect_ctx_t *ctx = (obj_detect_ctx_t*)p;
	void *n;
	n = (void*)malloc((ctx->params.width+8)*(ctx->params.height+8)*3/2);
    return n;
}

void* obj_detect_del_item(void *p, void *d)
{
	if(d) free(d);
    return NULL;
}

mm_module_t obj_detect_module = {
    .create = obj_detect_create,
    .destroy = obj_detect_destroy,
    .control = obj_detect_control,
    .handle = obj_detect_handle,
    
    .new_item = obj_detect_new_item,
    .del_item = obj_detect_del_item,
    
    .output_type = MM_TYPE_VSINK | MM_TYPE_VDSP,     // output for video algorithm
    .module_type = MM_TYPE_VDSP,     // module type is video algorithm
	.name = "OBJ_DETECT"
};
