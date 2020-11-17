 /******************************************************************************
	 *
 * Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#include "example_media_framework.h"
void aacloop_reset(int sample_rate)
{
	uint8_t smpl_rate_idx = ASR_16KHZ;
	siso_pause(siso_audio_aac);
	//siso_pause(siso_aac_rtsp);
	siso_pause(siso_aac_e2d);
	siso_pause(siso_aad_audio);

	switch(sample_rate){
    	case 8000:  smpl_rate_idx = ASR_8KHZ;     break;
    	case 16000: smpl_rate_idx = ASR_16KHZ;    break;
    	case 32000: smpl_rate_idx = ASR_32KHZ;    break;
    	case 44100: smpl_rate_idx = ASR_44p1KHZ;  break;
    	case 48000: smpl_rate_idx = ASR_48KHZ;    break;
    	case 88200: smpl_rate_idx = ASR_88p2KHZ;  break;
    	case 96000: smpl_rate_idx = ASR_96KHZ;    break;
    	default: break;
	}
	mm_module_ctrl(audio_ctx, CMD_AUDIO_SET_SAMPLERATE, smpl_rate_idx);
	mm_module_ctrl(audio_ctx, CMD_AUDIO_SET_RESET, 0);

	//mm_module_ctrl(aac_ctx, CMD_AAC_STOP, 0);
	mm_module_ctrl(aac_ctx, CMD_AAC_SAMPLERATE, sample_rate);
	mm_module_ctrl(aac_ctx, CMD_AAC_RESET, 0);

	//vTaskDelay(100);

	mm_module_ctrl(aad_ctx, CMD_AAD_SAMPLERATE, sample_rate);
	mm_module_ctrl(aad_ctx, CMD_AAD_RESET, 0);

	siso_resume(siso_audio_aac);
	//siso_resume(siso_aac_rtsp);
	siso_resume(siso_aac_e2d);
	siso_resume(siso_aad_audio);
}

void mmf2_example_aacloop_init(void)
{
	audio_ctx = mm_module_open(&audio_module);
	if(audio_ctx){
		mm_module_ctrl(audio_ctx, CMD_AUDIO_SET_PARAMS, (int)&audio_params);
		mm_module_ctrl(audio_ctx, MM_CMD_SET_QUEUE_LEN, 6);
		mm_module_ctrl(audio_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		mm_module_ctrl(audio_ctx, CMD_AUDIO_APPLY, 0);
	}else{
		rt_printf("audio open fail\n\r");
		goto mmf2_exmaple_aacloop_fail;
	}

	aac_ctx = mm_module_open(&aac_module);
	if(aac_ctx){
		mm_module_ctrl(aac_ctx, CMD_AAC_SET_PARAMS, (int)&aac_params);
		mm_module_ctrl(aac_ctx, MM_CMD_SET_QUEUE_LEN, 6);
		mm_module_ctrl(aac_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
		mm_module_ctrl(aac_ctx, CMD_AAC_INIT_MEM_POOL, 0);
		mm_module_ctrl(aac_ctx, CMD_AAC_APPLY, 0);
	}else{
		rt_printf("AAC open fail\n\r");
		goto mmf2_exmaple_aacloop_fail;
	}	
	
	
	aad_ctx = mm_module_open(&aad_module);
	if(aad_ctx){
		mm_module_ctrl(aad_ctx, CMD_AAD_SET_PARAMS, (int)&aad_params);
		mm_module_ctrl(aad_ctx, MM_CMD_SET_QUEUE_LEN, 6);
		mm_module_ctrl(aad_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		mm_module_ctrl(aad_ctx, CMD_AAD_APPLY, 0);
	}else{
		rt_printf("AAD open fail\n\r");
		goto mmf2_exmaple_aacloop_fail;
	}
	
	
	siso_audio_aac = siso_create();
	if(siso_audio_aac){
		siso_ctrl(siso_audio_aac, MMIC_CMD_ADD_INPUT, (uint32_t)audio_ctx, 0);
		siso_ctrl(siso_audio_aac, MMIC_CMD_ADD_OUTPUT, (uint32_t)aac_ctx, 0);
		siso_start(siso_audio_aac);
	}else{
		rt_printf("siso1 open fail\n\r");
		goto mmf2_exmaple_aacloop_fail;
	}
	
	
	siso_aac_e2d = siso_create();
	if(siso_aac_e2d){
		siso_ctrl(siso_aac_e2d, MMIC_CMD_ADD_INPUT, (uint32_t)aac_ctx, 0);
		siso_ctrl(siso_aac_e2d, MMIC_CMD_ADD_OUTPUT, (uint32_t)aad_ctx, 0);
		siso_start(siso_aac_e2d);
	}else{
		rt_printf("siso2 open fail\n\r");
		goto mmf2_exmaple_aacloop_fail;
	}
	
	siso_aad_audio = siso_create();
	if(siso_aad_audio){
		siso_ctrl(siso_aad_audio, MMIC_CMD_ADD_INPUT, (uint32_t)aad_ctx, 0);
		siso_ctrl(siso_aad_audio, MMIC_CMD_ADD_OUTPUT, (uint32_t)audio_ctx, 0);
		siso_start(siso_aad_audio);
	}else{
		rt_printf("siso3 open fail\n\r");
		goto mmf2_exmaple_aacloop_fail;
	}
	
	rt_printf("siso1 started\n\r");


	return;
mmf2_exmaple_aacloop_fail:
	
	return;
}