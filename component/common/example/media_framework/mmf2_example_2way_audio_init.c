 /******************************************************************************
	 *
 * Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#include "example_media_framework.h"


void two_way_reset(int sample_rate)
{
	uint8_t smpl_rate_idx = ASR_16KHZ;
	siso_pause(siso_audio_aac);
	//siso_pause(siso_aac_rtsp);
	siso_pause(siso_rtp_aad);
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
	siso_resume(siso_rtp_aad);
	siso_resume(siso_aad_audio);
}

mm_context_t* rtsp3_ctx            = NULL;

mm_simo_t* simo_aac_rtsp    = NULL;

void mmf2_example_2way_audio_init(void)
{
	
	audio_ctx = mm_module_open(&audio_module);
	if(audio_ctx){
		mm_module_ctrl(audio_ctx, CMD_AUDIO_SET_PARAMS, (int)&audio_params);
		mm_module_ctrl(audio_ctx, MM_CMD_SET_QUEUE_LEN, 6);
		mm_module_ctrl(audio_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		mm_module_ctrl(audio_ctx, CMD_AUDIO_APPLY, 0);
	}else{
		rt_printf("audio open fail\n\r");
		goto mmf2_exmaple_2way_audio_fail;
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
		goto mmf2_exmaple_2way_audio_fail;
	}
	
	rtsp2_ctx = mm_module_open(&rtsp2_module);
	if(rtsp2_ctx){
		mm_module_ctrl(rtsp2_ctx, CMD_RTSP2_SELECT_STREAM, 0);
		mm_module_ctrl(rtsp2_ctx, CMD_RTSP2_SET_PARAMS, (int)&rtsp2_a_params);
		mm_module_ctrl(rtsp2_ctx, CMD_RTSP2_SET_APPLY, 0);
		mm_module_ctrl(rtsp2_ctx, CMD_RTSP2_SET_STREAMMING, ON);
		//mm_module_ctrl(rtsp2_ctx, MM_CMD_SET_QUEUE_LEN, 3);
		//mm_module_ctrl(rtsp2_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
	}else{
		rt_printf("RTSP2 open fail\n\r");
		goto mmf2_exmaple_2way_audio_fail;
	}
	
	rt_printf("RTSP2 opened\n\r");
        
        //////////////////////
        rtsp3_ctx = mm_module_open(&rtsp2_module);
	if(rtsp3_ctx){
                rtsp2_a_params.u.a.samplerate=16000;
		mm_module_ctrl(rtsp3_ctx, CMD_RTSP2_SELECT_STREAM, 0);
		mm_module_ctrl(rtsp3_ctx, CMD_RTSP2_SET_PARAMS, (int)&rtsp2_a_params);
		mm_module_ctrl(rtsp3_ctx, CMD_RTSP2_SET_APPLY, 0);
		mm_module_ctrl(rtsp3_ctx, CMD_RTSP2_SET_STREAMMING, ON);
		//mm_module_ctrl(rtsp2_ctx, MM_CMD_SET_QUEUE_LEN, 3);
		//mm_module_ctrl(rtsp2_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
	}else{
		rt_printf("RTSP2 open fail\n\r");
		goto mmf2_exmaple_2way_audio_fail;
	}
	
	rt_printf("RTSP2 opened\n\r");
        /////////////////////
	
	rtp_ctx = mm_module_open(&rtp_module);
	if(rtp_ctx){
		mm_module_ctrl(rtp_ctx, CMD_RTP_SET_PARAMS, (int)&rtp_aad_params);
		mm_module_ctrl(rtp_ctx, MM_CMD_SET_QUEUE_LEN, 6);
		mm_module_ctrl(rtp_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		mm_module_ctrl(rtp_ctx, CMD_RTP_APPLY, 0);
		mm_module_ctrl(rtp_ctx, CMD_RTP_STREAMING, 1);	// streamming on
	}else{
		rt_printf("RTP open fail\n\r");
		goto mmf2_exmaple_2way_audio_fail;
	}

	aad_ctx = mm_module_open(&aad_module);
	if(aad_ctx){
		mm_module_ctrl(aad_ctx, CMD_AAD_SET_PARAMS, (int)&aad_rtp_params);
		mm_module_ctrl(aad_ctx, MM_CMD_SET_QUEUE_LEN, 6);
		mm_module_ctrl(aad_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		mm_module_ctrl(aad_ctx, CMD_AAD_APPLY, 0);
	}else{
		rt_printf("AAD open fail\n\r");
		goto mmf2_exmaple_2way_audio_fail;
	}

	siso_audio_aac = siso_create();
	if(siso_audio_aac){
		siso_ctrl(siso_audio_aac, MMIC_CMD_ADD_INPUT, (uint32_t)audio_ctx, 0);
		siso_ctrl(siso_audio_aac, MMIC_CMD_ADD_OUTPUT, (uint32_t)aac_ctx, 0);
		siso_start(siso_audio_aac);
	}else{
		rt_printf("siso1 open fail\n\r");
		goto mmf2_exmaple_2way_audio_fail;
	}
	
	rt_printf("siso1 started\n\r");
#if 0
	siso_aac_rtsp = siso_create();
	if(siso_aac_rtsp){
		siso_ctrl(siso_aac_rtsp, MMIC_CMD_ADD_INPUT, (uint32_t)aac_ctx, 0);
		siso_ctrl(siso_aac_rtsp, MMIC_CMD_ADD_OUTPUT, (uint32_t)rtsp2_ctx, 0);
		siso_start(siso_aac_rtsp);
	}else{
		rt_printf("siso2 open fail\n\r");
		goto mmf2_exmaple_2way_audio_fail;
	}
	
	rt_printf("siso2 started\n\r");
#else
        simo_aac_rtsp    = simo_create();
        
        if(simo_aac_rtsp){
		simo_ctrl(simo_aac_rtsp, MMIC_CMD_ADD_INPUT, (uint32_t)aac_ctx, 0);
		simo_ctrl(simo_aac_rtsp, MMIC_CMD_ADD_OUTPUT0, (uint32_t)rtsp2_ctx, 0);
		simo_ctrl(simo_aac_rtsp, MMIC_CMD_ADD_OUTPUT1, (uint32_t)rtsp3_ctx, 0);
		simo_start(simo_aac_rtsp);
	}else{
		rt_printf("simo open fail\n\r");
		//goto mmf2_exmaple_simo_fail;
                goto mmf2_exmaple_2way_audio_fail;
	}
#endif
	
	siso_rtp_aad = siso_create();
	if(siso_rtp_aad){
		siso_ctrl(siso_rtp_aad, MMIC_CMD_ADD_INPUT, (uint32_t)rtp_ctx, 0);
		siso_ctrl(siso_rtp_aad, MMIC_CMD_ADD_OUTPUT, (uint32_t)aad_ctx, 0);
		siso_start(siso_rtp_aad);
	}else{
		rt_printf("siso1 open fail\n\r");
		goto mmf2_exmaple_2way_audio_fail;
	}
	
	rt_printf("siso3 started\n\r");

	siso_aad_audio = siso_create();
	if(siso_aad_audio){
		siso_ctrl(siso_aad_audio, MMIC_CMD_ADD_INPUT, (uint32_t)aad_ctx, 0);
		siso_ctrl(siso_aad_audio, MMIC_CMD_ADD_OUTPUT, (uint32_t)audio_ctx, 0);
		siso_start(siso_aad_audio);
	}else{
		rt_printf("siso2 open fail\n\r");
		goto mmf2_exmaple_2way_audio_fail;
	}
	
	rt_printf("siso4 started\n\r");
	
	

	return;
mmf2_exmaple_2way_audio_fail:
	
	return;

}