#ifndef _MODULE_SKYNET_H
#define _MODULE_SKYNET_H

#include "mmf2_module.h"

#define CMD_SKYNET_START        	    MM_MODULE_CMD(0x00)
#define CMD_SKYNET_START_WATCHDOG	    MM_MODULE_CMD(0x01)

typedef struct skynet_ctx_s{
	void* parent;
 		
	uint32_t dest_actual_len;

	unsigned int stream_id;
}skynet_ctx_t;

typedef struct skynet_params_s{
	uint32_t width;
	uint32_t height;
	uint32_t bps;
	uint32_t fps;
	uint32_t stream_id;
}skynet_params_t;

extern mm_module_t skynet_module;


#endif