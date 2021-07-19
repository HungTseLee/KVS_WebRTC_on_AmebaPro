#include "module_isp.h"
#include "module_obj_detect.h"
#include "module_h264.h"
#include "module_skynet.h"
#include "module_rtsp2.h"

#include "mmf2_link.h"
#include "mmf2_siso.h"
#include "mmf2_simo.h"
#include "mmf2_miso.h"
#include "mmf2_mimo.h"

#include "sensor_service.h"
#include "object_detection_init.h"
#include "platform_opts.h"

#include "hal_cache.h"

#include "wifi_conf.h" //for wifi_is_ready_to_transceive
#define wifi_wait_time 500 //Here we wait 5 second to wiat the fast connect 

//------------------------------------------------------------------------------
// Parameter for modules
//------------------------------------------------------------------------------
mm_context_t* isp_obj_detect_ctx        = NULL;
mm_context_t* isp_obj_detect_ctx_v2     = NULL;
mm_context_t* obj_detect_ctx            = NULL;
mm_context_t* obj_detect_ctx_v2         = NULL;
mm_context_t* h264_obj_detect_ctx       = NULL;
mm_context_t* skynet_obj_detect_ctx     = NULL;
mm_context_t* rtsp2_obj_detect_ctx      = NULL;

mm_siso_t* siso_isp_obj_detect          = NULL;
mm_siso_t* siso_isp_obj_detect_v2       = NULL;
mm_siso_t* siso_obj_detect_h264         = NULL;
mm_siso_t* siso_h264_skynet_obj_detect  = NULL;
mm_siso_t* siso_h264_rtsp2_obj_detect   = NULL;


#define BLOCK_SIZE						1024*10
#define FRAME_SIZE						(V1_WIDTH*V1_HEIGHT/2)
#define BUFFER_SIZE						(FRAME_SIZE*3)

#define FORMAT_NV16 ISP_FORMAT_YUV420_SEMIPLANAR//ISP_FORMAT_YUV422_SEMIPLANAR//ISP_FORMAT_BAYER_PATTERN

#define YUY2_FPS 15
#define H264_FPS 15
#define H264_BPS 1024*1024//64*1024

void plot_detect_result_cb(uint8_t* input_buf, int input_buf_size);

isp_params_t isp_params_obj_detect = {
	.width    = V1_WIDTH, 
	.height   = V1_HEIGHT,
	.fps      = YUY2_FPS,
	.slot_num = 2,
	.buff_num = 3,
	.format   = FORMAT_NV16,
	//.bayer_type = BAYER_TYPE_BEFORE_BLC
};

obj_detect_params_t obj_detect_params = {
	.width          = V1_WIDTH,
	.height         = V1_HEIGHT,
};

isp_params_t isp_params_obj_detect_v2 = {
	.width    = V2_WIDTH,
	.height   = V2_HEIGHT,
	.fps      = YUY2_FPS,
	.slot_num = 2,
	.buff_num = 3,
	.format   = FORMAT_NV16,
	//.bayer_type = BAYER_TYPE_BEFORE_BLC
};
obj_detect_params_t obj_detect_params_v2 = {
	.width          = V2_WIDTH,
	.height         = V2_HEIGHT,
};

h264_params_t h264_params_obj_detect = {
	.width          = V1_WIDTH,
	.height         = V1_HEIGHT,
	.bps            = H264_BPS,
	.fps            = H264_FPS,
	.gop            = H264_FPS,
	.rc_mode        = RC_MODE_H264CBR,//RC_MODE_H264CBR
	.mem_total_size = BUFFER_SIZE,
	.mem_block_size = BLOCK_SIZE,
	.mem_frame_size = FRAME_SIZE,
	.input_type     = ISP_FORMAT_YUV420_SEMIPLANAR
};

rtsp2_params_t rtsp2_obj_detect_params = {
	.type = AVMEDIA_TYPE_VIDEO,
	.u = {
		.v = {
			.codec_id = AV_CODEC_ID_H264,
			.fps      = H264_FPS,
			.bps      = H264_BPS
		}
	}
};

static void common_init()
{
	uint32_t wifi_wait_count = 0;
	
	while (wifi_is_ready_to_transceive(RTW_STA_INTERFACE) != RTW_SUCCESS){
		vTaskDelay(10);
		wifi_wait_count++;
		if(wifi_wait_count == wifi_wait_time){
			printf("\r\nuse ATW0, ATW1, ATWC to make wifi connection\r\n");
			printf("wait for wifi connection...\r\n");
		}
	}
	
#if CONFIG_LIGHT_SENSOR
	init_sensor_service();
#else
	ir_cut_init(NULL);
	ir_cut_enable(1);
#endif

}

void object_detection_init(void)
{
    common_init();
    
	isp_obj_detect_ctx = mm_module_open(&isp_module);
	if(isp_obj_detect_ctx){
		mm_module_ctrl(isp_obj_detect_ctx, CMD_ISP_SET_PARAMS, (int)&isp_params_obj_detect);
		mm_module_ctrl(isp_obj_detect_ctx, MM_CMD_SET_QUEUE_LEN, isp_params_obj_detect.buff_num);
		mm_module_ctrl(isp_obj_detect_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		mm_module_ctrl(isp_obj_detect_ctx, CMD_ISP_APPLY, 2);	// start channel 2
	}else{
		rt_printf("ISP open fail\n\r");
		goto mmf2_example_skynet_fail;
	}
    //isp ch2 for detection
    isp_obj_detect_ctx_v2 = mm_module_open(&isp_module);
	if(isp_obj_detect_ctx_v2){
		mm_module_ctrl(isp_obj_detect_ctx_v2, CMD_ISP_SET_PARAMS, (int)&isp_params_obj_detect_v2);
		mm_module_ctrl(isp_obj_detect_ctx_v2, MM_CMD_SET_QUEUE_LEN, isp_params_obj_detect_v2.buff_num);
		mm_module_ctrl(isp_obj_detect_ctx_v2, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		mm_module_ctrl(isp_obj_detect_ctx_v2, CMD_ISP_APPLY, 1);	// start channel 1
	}else{
		rt_printf("ISP open fail\n\r");
		goto mmf2_example_skynet_fail;
	}   
    
    obj_detect_ctx_v2 = mm_module_open(&obj_detect_module);
	if(obj_detect_ctx_v2){
		mm_module_ctrl(obj_detect_ctx_v2, CMD_OBJ_DETECT_SET_PARAMS, (int)&obj_detect_params_v2);
		mm_module_ctrl(obj_detect_ctx_v2, MM_CMD_SET_QUEUE_LEN, 1);
		mm_module_ctrl(obj_detect_ctx_v2, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
        
        mm_module_ctrl(obj_detect_ctx_v2, CMD_OBJ_DETECT_HUMAN,0);
        mm_module_ctrl(obj_detect_ctx_v2, CMD_OBJ_DETECT_SET_DETECT, 1);
	}else{
		rt_printf("obj_detect open fail\n\r");
		goto mmf2_example_skynet_fail;
	}
    
    
    siso_isp_obj_detect_v2 = siso_create();
    if(siso_isp_obj_detect_v2){
		siso_ctrl(siso_isp_obj_detect_v2, MMIC_CMD_ADD_INPUT, (uint32_t)isp_obj_detect_ctx_v2, 0);
		siso_ctrl(siso_isp_obj_detect_v2, MMIC_CMD_ADD_OUTPUT, (uint32_t)obj_detect_ctx_v2, 0);
        siso_start(siso_isp_obj_detect_v2);
	}else{
		rt_printf("siso1 open fail\n\r");
		goto mmf2_example_skynet_fail;
	}
    
#if USE_H264
    h264_obj_detect_ctx = mm_module_open(&h264_module);
    if(h264_obj_detect_ctx){
        mm_module_ctrl(h264_obj_detect_ctx, CMD_H264_SET_PARAMS, (int)&h264_params_obj_detect);
        mm_module_ctrl(h264_obj_detect_ctx, MM_CMD_SET_QUEUE_LEN, 3);
        mm_module_ctrl(h264_obj_detect_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
        mm_module_ctrl(h264_obj_detect_ctx, CMD_H264_INIT_MEM_POOL, 0);
        mm_module_ctrl(h264_obj_detect_ctx, CMD_H264_APPLY, 0);
    }else{
        rt_printf("H264 open fail\n\r");
        goto mmf2_example_skynet_fail;
    }
    
    siso_obj_detect_h264 = siso_create();
    
    if(siso_obj_detect_h264){
        siso_ctrl(siso_obj_detect_h264, MMIC_CMD_ADD_INPUT, (uint32_t)isp_obj_detect_ctx, 0);
        siso_ctrl(siso_obj_detect_h264, MMIC_CMD_ADD_OUTPUT, (uint32_t)h264_obj_detect_ctx, 0);
        siso_ctrl(siso_obj_detect_h264, MMIC_CMD_SET_PREPROCESS_CB, (int)plot_detect_result_cb, 0);
        siso_start(siso_obj_detect_h264);
    }else{
        rt_printf("siso1 open fail\n\r");
        goto mmf2_example_skynet_fail;
    }

#if USE_RTSP
        rtsp2_obj_detect_ctx = mm_module_open(&rtsp2_module);
        if(rtsp2_obj_detect_ctx){
            mm_module_ctrl(rtsp2_obj_detect_ctx, CMD_RTSP2_SELECT_STREAM, 0);
            mm_module_ctrl(rtsp2_obj_detect_ctx, CMD_RTSP2_SET_PARAMS, (int)&rtsp2_obj_detect_params);
            mm_module_ctrl(rtsp2_obj_detect_ctx, CMD_RTSP2_SET_APPLY, 0);
            mm_module_ctrl(rtsp2_obj_detect_ctx, CMD_RTSP2_SET_STREAMMING, ON);
            //mm_module_ctrl(rtsp2_obj_detect_ctx, CMD_RTSP2_SET_URL,(int)&"stream_01");
            //mm_module_ctrl(rtsp2_ctx, MM_CMD_SET_QUEUE_LEN, 3);
            //mm_module_ctrl(rtsp2_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
        }else{
            rt_printf("RTSP2 open fail\n\r");
            goto mmf2_example_skynet_fail;
        }    
        siso_h264_rtsp2_obj_detect = siso_create();
        if(siso_h264_rtsp2_obj_detect){
            siso_ctrl(siso_h264_rtsp2_obj_detect, MMIC_CMD_ADD_INPUT, (uint32_t)h264_obj_detect_ctx, 0);
            siso_ctrl(siso_h264_rtsp2_obj_detect, MMIC_CMD_ADD_OUTPUT, (uint32_t)rtsp2_obj_detect_ctx, 0);   
            
            siso_start(siso_h264_rtsp2_obj_detect);
        }else{
            rt_printf("siso4 open fail\n\r");
            goto mmf2_example_skynet_fail;
        } 
#endif
          
#if USE_SKYNET          
          skynet_obj_detect_ctx = mm_module_open(&skynet_module);
          if(skynet_obj_detect_ctx){
                mm_module_ctrl(skynet_obj_detect_ctx, MM_CMD_SET_QUEUE_LEN, 3);
                mm_module_ctrl(skynet_obj_detect_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
                mm_module_ctrl(skynet_obj_detect_ctx, CMD_SKYNET_START, 0);
                //mm_module_ctrl(skynet_obj_detect_ctx, CMD_SKYNET_START_WATCHDOG, 0);
          }else{
                rt_printf("Skynet open fail\n\r");
                goto mmf2_example_skynet_fail;
          }
          
        siso_h264_skynet_obj_detect = siso_create();
        if(siso_h264_skynet_obj_detect){
            siso_ctrl(siso_h264_skynet_obj_detect, MMIC_CMD_ADD_INPUT, (uint32_t)h264_obj_detect_ctx, 0);//h264_v1_ctx
            siso_ctrl(siso_h264_skynet_obj_detect, MMIC_CMD_ADD_OUTPUT, (uint32_t)skynet_obj_detect_ctx, 0);       
            siso_start(siso_h264_skynet_obj_detect);
        }else{
            rt_printf("siso1 open fail\n\r");
                goto mmf2_example_skynet_fail;
        }
#endif//USE_SKYNET 
#endif
        
mmf2_example_skynet_fail:
	
	return;
}

void plot_detect_result_cb(uint8_t* input_buf, int input_buf_size){
    
    Boxes box;
    mm_module_ctrl(obj_detect_ctx_v2, CMD_OBJ_DETECT_GET_BOX, (int)&box);
    int xmin, xmax, ymin, ymax;
    int xscale = V1_WIDTH, yscale = V1_HEIGHT;
    int num_boxes = (int) box.output_num_detections[0];
#if (V2_WIDTH == 224 && V2_HEIGHT == 224)
    int x_shift = (V1_WIDTH - V1_HEIGHT)/2;
    for(int i = 0; i < num_boxes; ++i)
    {
        ymin = (int)(box.output_boxes[i*4+0] * yscale);
        xmin = (int)(box.output_boxes[i*4+1] * yscale) + x_shift;
        ymax = (int)(box.output_boxes[i*4+2] * yscale);
        xmax = (int)(box.output_boxes[i*4+3] * yscale) + x_shift;
                    
        ymax = ymax<yscale?ymax:yscale-1;
        xmax = xmax<xscale?xmax:xscale-1;

        for(int x_cursor = xmin; x_cursor < xmax; x_cursor++){
            input_buf[ymin*xscale+x_cursor] = 255;
            input_buf[ymax*xscale+x_cursor] = 255;
        }
        for(int y_cursor = ymin; y_cursor < ymax; y_cursor++){
            input_buf[y_cursor*xscale+xmin] = 255;
            input_buf[y_cursor*xscale+xmax] = 255;
        }
        //printf("(x, y, w, h) = (%d, %d, %d, %d)\n",xmin, ymin, (xmax-xmin), (ymax-ymin) );
    }
#else
    for(int i = 0; i < num_boxes; ++i)
    {
        ymin = (int)(box.output_boxes[i*4+0] * yscale);
        xmin = (int)(box.output_boxes[i*4+1] * xscale);
        ymax = (int)(box.output_boxes[i*4+2] * yscale);
        xmax = (int)(box.output_boxes[i*4+3] * xscale);
                    
        ymax = ymax<yscale?ymax:yscale-1;
        xmax = xmax<xscale?xmax:xscale-1;

        for(int x_cursor = xmin; x_cursor < xmax; x_cursor++){
            input_buf[ymin*xscale+x_cursor] = 255;
            input_buf[ymax*xscale+x_cursor] = 255;
        }
        for(int y_cursor = ymin; y_cursor < ymax; y_cursor++){
            input_buf[y_cursor*xscale+xmin] = 255;
            input_buf[y_cursor*xscale+xmax] = 255;
        }
        //printf("(x, y, w, h) = (%d, %d, %d, %d)\n",xmin, ymin, (xmax-xmin), (ymax-ymin) );
    }
#endif
    
    dcache_clean_by_addr((uint32_t *)input_buf, input_buf_size);    
}

void example_object_detection_init_thread(void *param)
{
        object_detection_init();
        vTaskDelete(NULL);
}

void example_object_detection(void) {
	if(xTaskCreate(example_object_detection_init_thread, ((const char*)"object_detection_init_process"), 512, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {//256
		printf("\n\r%s xTaskCreate(skynet_thread) failed", __FUNCTION__);
	}  
}
