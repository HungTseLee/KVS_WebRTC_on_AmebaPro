#ifndef _MODULE_OBJ_DETECT_H
#define _MODULE_OBJ_DETECT_H

#include "mmf2_module.h"

#include "FreeRTOS.h"
#include "semphr.h"

#define CMD_OBJ_DETECT_SET_PARAMS			MM_MODULE_CMD(0x00)
#define CMD_OBJ_DETECT_GET_PARAMS			MM_MODULE_CMD(0x01)
#define CMD_OBJ_DETECT_SET_HEIGHT			MM_MODULE_CMD(0x02)
#define CMD_OBJ_DETECT_SET_WIDTH			MM_MODULE_CMD(0x03)
#define CMD_OBJ_DETECT_SET_DETECT	        MM_MODULE_CMD(0x04)
#define CMD_OBJ_DETECT_GET_BOX	            MM_MODULE_CMD(0x05)

//model select
#define CMD_OBJ_DETECT_FACE                 MM_MODULE_CMD(0x06)
#define CMD_OBJ_DETECT_HUMAN                MM_MODULE_CMD(0x07)

typedef struct BBox {
	float output_boxes[10*4];
	float output_classes[10];
	float output_scores[10];
	int output_num_detections[1];
} Boxes;

typedef struct obj_detect_params_s{
	uint32_t width;
	uint32_t height;
}obj_detect_params_t;

typedef struct obj_detect_ctx_s{
	void* parent;
	obj_detect_params_t params;
    uint8_t set_detect;
    Boxes box;
    int selected_model;
    uint8_t* hold_image_address;
    uint8_t hold_image_flag;
    SemaphoreHandle_t hold_image_sema;
    
}obj_detect_ctx_t;

extern mm_module_t obj_detect_module;

#endif //_MODULE_OBJ_DETECT_H
