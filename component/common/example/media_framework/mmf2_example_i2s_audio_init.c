 /******************************************************************************
 *
 * Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#include "example_media_framework.h"

void mmf2_example_i2s_audio_init(void)
{
	i2s_ctx = mm_module_open(&i2s_module);
        if(i2s_ctx){
		mm_module_ctrl(i2s_ctx, CMD_I2S_SET_PARAMS, (int)&i2s_params);
		mm_module_ctrl(i2s_ctx, MM_CMD_SET_QUEUE_LEN, 6);
		mm_module_ctrl(i2s_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		mm_module_ctrl(i2s_ctx, CMD_I2S_APPLY, 0);
	}else{
		rt_printf("i2s open fail\n\r");
		goto mmf2_exmaple_i2s_audio_fail;
	}
    audio_ctx = mm_module_open(&audio_module);
	if(audio_ctx){
		mm_module_ctrl(audio_ctx, CMD_AUDIO_SET_PARAMS, (int)&audio_params);
		mm_module_ctrl(audio_ctx, MM_CMD_SET_QUEUE_LEN, 6);
		mm_module_ctrl(audio_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		mm_module_ctrl(audio_ctx, CMD_AUDIO_APPLY, 0);
	}else{
		rt_printf("audio open fail\n\r");
		goto mmf2_exmaple_i2s_audio_fail;
	}
	siso_audio_loop = siso_create();
	if(siso_audio_loop){
		siso_ctrl(siso_audio_loop, MMIC_CMD_ADD_INPUT, (uint32_t)i2s_ctx, 0);
		siso_ctrl(siso_audio_loop, MMIC_CMD_ADD_OUTPUT, (uint32_t)audio_ctx, 0);
		siso_start(siso_audio_loop);
	}else{
		rt_printf("siso1 open fail\n\r");
		goto mmf2_exmaple_i2s_audio_fail;
	}
	
	rt_printf("siso1 started\n\r");


	return;
mmf2_exmaple_i2s_audio_fail:
	
	return;
}