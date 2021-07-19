#include <stdint.h>
#include "mmf2_module.h"
#include "module_skynet.h"
#include <wifi_conf.h>
#include "SKYNET_IOTAPI.h"
   
//wathdog
#include "wdt_api.h"
#define WATCHDOG_REFRESH 8000
#define WATCHDOG_TIMEOUT 10000

//audio
#include "avcodec.h"
#define BIAS        (0x84)
static short seg_end[8] = {0xFF, 0x1FF, 0x3FF, 0x7FF, 0xFFF, 0x1FFF, 0x3FFF, 0x7FFF};  
static char audioBuf[640];
static int audioSize = 0;

int wait_for_i = 1;
static int skynet_h264_handle(void* p, void* input, void* output);
static int skynet_audio_handle_handle(void* p, void* input, void* output);
extern AV_Client gClientInfo[MAX_CLIENT_NUMBER];
//------------------------------------------------------------------------------
static void watchdog_thread(void *param)
{
	while(1) {
		watchdog_refresh();
		vTaskDelay(WATCHDOG_REFRESH);
	}
}

int skynet_handle(void* p, void* input, void* output)
{
    //printf("\n@@@@@@@@@@\nskynet_handle...\r\n");
    mm_queue_item_t* input_item = (mm_queue_item_t*)input;
  
    if(input_item->type == AV_CODEC_ID_H264){
        skynet_h264_handle(p, input, output);
    }
    else if(input_item->type == AV_CODEC_ID_PCM_RAW){
        //printf("audio_input\n");  
        skynet_audio_handle_handle(p, input, output);
    }
		
	return 0;
}
static int skynet_h264_handle(void* p, void* input, void* output)
{
    skynet_ctx_t *ctx = (skynet_ctx_t*)p;
	
	/*P2 Part*/
	char drop=1;
	int i;
	int nHeadLen=sizeof(st_AVStreamIOHead)+sizeof(st_AVFrameHead);
	char *pBufVideo;//=&a_buf[nHeadLen];
	st_AVStreamIOHead *pstStreamIOHead;//=(st_AVStreamIOHead *)a_buf;
	st_AVFrameHead    *pstFrameHead;//	  =(st_AVFrameHead *)&a_buf[sizeof(st_AVStreamIOHead)];
	unsigned long nCurTick = myGetTickCount();
	int UserCount = 0, nRet=0;
	int frameCnt = 0;
	
	mm_queue_item_t* input_item = (mm_queue_item_t*)input;
    	       
	drop = 1;
	for(i=0 ; i<MAX_CLIENT_NUMBER; i++){
		if(gClientInfo[i].SID >= 0 && gClientInfo[i].bEnableVideo == 1){
			drop=0;
		}
	}
	//printf("drop = %d\r\n",drop);
    if(drop == 1)
              return 0;
    
   
	//printf("dest_addr= 0x%x len = %d\r\n",(uint32_t)input_item->data_addr,ctx->dest_actual_len);
	if((uint32_t)input_item->data_addr == 0x00){
		ctx->dest_actual_len = 0x00;
	}
	else{
        ctx->dest_actual_len = input_item->size;
        
		uint8_t* stream_data = (uint8_t*)input_item->data_addr;
		if(*(stream_data+4) == 0x27)
			wait_for_i = 0;
		if((drop == 0) && (wait_for_i == 0)) 
		{
            //printf("drop == 0) && (wait_for_i == 0)\r\n");
			/*
			printf("stream_data(%d x %d) length:%d data:%x %x %x %x %x %x %x %x\r\n",
			h264_ctx->h264_parm.width,h264_ctx->h264_parm.height,ctx->dest_actual_len,
			*stream_data,*(stream_data+1),*(stream_data+2),*(stream_data+3),
			*(stream_data+4),*(stream_data+5),*(stream_data+6),
			*(stream_data+7));
			*/
				
			UserCount = 0;
			for(i=0 ; i <MAX_CLIENT_NUMBER; i++) {/* send to multi client */
				if(gClientInfo[i].SID < 0 || gClientInfo[i].bEnableVideo == 0){
					continue;
				}

				xSemaphoreTake(gClientInfo[i].pBuf_mutex, portMAX_DELAY);
				//Video Part
							
				pBufVideo = &gClientInfo[i].pBuf[nHeadLen];
				pstStreamIOHead =(st_AVStreamIOHead *)gClientInfo[i].pBuf;
				pstFrameHead = (st_AVFrameHead *)&gClientInfo[i].pBuf[sizeof(st_AVStreamIOHead)];

				pstFrameHead->nCodecID  = CODECID_V_H264;				
				pstFrameHead->nTimeStamp = nCurTick;
				pstFrameHead->nDataSize = ctx->dest_actual_len;
				UserCount++;
				pstFrameHead->nOnlineNum=3;//UserCount;
				pstFrameHead->top_x = 0;//
				pstFrameHead->top_y = 0;//
				pstFrameHead->width = 0;//
				pstFrameHead->height = 0;//

				pstStreamIOHead->nStreamIOHead=sizeof(st_AVFrameHead)+ctx->dest_actual_len;
				pstStreamIOHead->uionStreamIOHead.nStreamIOType=SIO_TYPE_VIDEO;

				if(*(stream_data+4) == 0x27){
					//printf("Sned I Frame\n");
					pstFrameHead->flag = VFRAME_FLAG_I;
					frameCnt = 0;
				}
				else{
					//printf("Sned P Frame\n");
					pstFrameHead->flag = VFRAME_FLAG_P;
					frameCnt++;
				}

				memcpy(pBufVideo, stream_data, ctx->dest_actual_len);

				//nRet = SKYNET_send_video(gClientInfo[i].SID, gClientInfo[i].pBuf, ctx->dest_actual_len+nHeadLen) ;	
				//wait_rf_ready();
				//printf("11111111(%d) %d\r\n",ret,ctx->dest_actual_len+nHeadLen);
				if((nRet = SKYNET_send(gClientInfo[i].SID, gClientInfo[i].pBuf, ctx->dest_actual_len+nHeadLen)) < 0 ) {
					printf("\r\n\r\nSKYNET_send Error Video type:%d nRet:%d i:%d SID:%d data_size:%d\r\n\r\n",pstFrameHead->flag,nRet,i,gClientInfo[i].SID,ctx->dest_actual_len+nHeadLen);
					wait_for_i = 1;
					vTaskDelay(200 / portTICK_PERIOD_MS);
				} //else {
								//printf("nSKYNET_send Video type:%d nRet:%d data_size:%d\r\n",pstFrameHead->flag,nRet,ctx->dest_actual_len+nHeadLen);
							//}
							
				xSemaphoreGive(gClientInfo[i].pBuf_mutex);
			}
		}
	}
    
	return 0;
    
}

static short search(short val, short *table, short size)  
{  
    short i;  
    for (i = 0; i < size; i++) {  
        if (val <= *table++)  
            return (i);  
    }  
    return (size);  
}
static unsigned char linear2ulaw(short pcm_val)    /* 2's complement (16-bit range) */  
{  
    short     mask;  
    short     seg;  
    unsigned char   uval;  
  
    /* Get the sign and the magnitude of the value. */  
    if (pcm_val < 0) {  
        pcm_val = BIAS - pcm_val;  
        mask = 0x7F;  
    } else {  
        pcm_val += BIAS;  
        mask = 0xFF;  
    }  
  
    /* Convert the scaled magnitude to segment number. */  
    seg = search(pcm_val, seg_end, 8);  
  
    /* 
     * Combine the sign, segment, quantization bits; 
     * and complement the code word. 
     */  
    if (seg >= 8)        /* out of range, return maximum value. */  
        return (0x7F ^ mask);  
    else {  
        uval = (seg << 4) | ((pcm_val >> (seg + 3)) & 0xF);  
        return (uval ^ mask);  
    }  
  
} 

static int skynet_audio_handle_handle(void* p, void* input, void* output)
{
	skynet_ctx_t *ctx = (skynet_ctx_t*)p;
    //aac_ctx_t *ctx = (aac_ctx_t*)p;
	mm_queue_item_t* input_item = (mm_queue_item_t*)input;
	//mm_queue_item_t* output_item = (mm_queue_item_t*)output;

	/*P2 Part*/
	char drop=1;
	int i;
	int nHeadLen=sizeof(st_AVStreamIOHead)+sizeof(st_AVFrameHead);
	char *pBufVideo;//=&a_buf[nHeadLen];
	st_AVStreamIOHead *pstStreamIOHead;//=(st_AVStreamIOHead *)a_buf;
	st_AVFrameHead    *pstFrameHead;//	  =(st_AVFrameHead *)&a_buf[sizeof(st_AVStreamIOHead)];
	unsigned long nCurTick=myGetTickCount();
	int UserCount = 0, nRet=0;
	//char audioBuf[200];
	//int audioSize = 0;
		
	//output_item->timestamp = input_item->timestamp;
	// set timestamp to 1st sample (cache head)
	//output_item->timestamp -= 1000 * (ctx->cache_idx/2) / ctx->params.sample_rate;
	
	/*
	if (ctx->params.bit_length==8)
		samples_read = input_item->size;
	else if (ctx->params.bit_length==16)
		samples_read = input_item->size/2;
	*/

	#if 1
	drop = 1;
	for(i=0 ; i<MAX_CLIENT_NUMBER; i++){
		if(gClientInfo[i].SID >= 0 && gClientInfo[i].bEnableVideo == 1){
			drop = 0;
		}
	}

	if(drop == 0) {
		short* stream_data = (short*)input_item->data_addr;
		for (i = 0; i < input_item->size/2; i++) {
			audioBuf[i+audioSize] = linear2ulaw(*(stream_data + i));
		}
		audioSize += input_item->size/2;

		if(audioSize >= 640) {
			for(i=0 ; i <MAX_CLIENT_NUMBER; i++) {/* send to multi client */
				if(gClientInfo[i].SID < 0 || gClientInfo[i].bEnableAudio == 0){
					continue;
				}
				xSemaphoreTake(gClientInfo[i].pBuf_mutex, portMAX_DELAY);
				pBufVideo = &gClientInfo[i].pBuf[nHeadLen];
				pstStreamIOHead =(st_AVStreamIOHead *)gClientInfo[i].pBuf;
				pstFrameHead = (st_AVFrameHead *)&gClientInfo[i].pBuf[sizeof(st_AVStreamIOHead)];

				pstFrameHead->nCodecID  = CODECID_A_G711_U;				
				pstFrameHead->nTimeStamp = nCurTick;
				pstFrameHead->nDataSize = audioSize;
				UserCount++;
				pstFrameHead->nOnlineNum=UserCount;
	
				pstStreamIOHead->nStreamIOHead=sizeof(st_AVFrameHead)+audioSize;
				pstStreamIOHead->uionStreamIOHead.nStreamIOType=SIO_TYPE_AUDIO;

				pstFrameHead->flag = (ASAMPLE_RATE_8K << 2) | (ADATABITS_16 << 1) | (ACHANNEL_MONO);

				memcpy(pBufVideo, audioBuf, audioSize);

				nRet = SKYNET_send(gClientInfo[i].SID, gClientInfo[i].pBuf, audioSize+nHeadLen) ;

				/*
				if(nRet == -11) {
					vTaskDelay(10);
					nRet = SKYNET_send(gClientInfo[i].SID, gClientInfo[i].pBuf, audioSize+nHeadLen) ;
					if(nRet == -11) {
						vTaskDelay(10);
						nRet = SKYNET_send(gClientInfo[i].SID, gClientInfo[i].pBuf, audioSize+nHeadLen) ;
					}
				}
				*/
			
				if(nRet < 0)
					printf("SKYNET_send Audio %d i:%d SID:%d data_size:%d\r\n",nRet,i,gClientInfo[i].SID,audioSize+nHeadLen);
			
				xSemaphoreGive(gClientInfo[i].pBuf_mutex);
			}
			audioSize = 0;
		}
	}
	#endif
	

	return 0;
}


int skynet_control(void *p, int cmd, int arg)
{
	skynet_ctx_t *ctx = (skynet_ctx_t*)p;
	
	switch(cmd){	
	case CMD_SKYNET_START:
        rltk_is_video_streaming(1);
        skynet_device_run();
		break;
	case CMD_SKYNET_START_WATCHDOG:
        printf("WatchDog setup\n");
        watchdog_init(WATCHDOG_TIMEOUT);
        watchdog_start();
		if(xTaskCreate(watchdog_thread, ((const char*)"watchdog_thread"), 1024, NULL, tskIDLE_PRIORITY + 5, NULL) != pdPASS)
            printf("\n\r%s xTaskCreate(watchdog_thread) failed", __FUNCTION__);
		break;
        
        }
        return 0;
}

void* skynet_destroy(void* p)
{
	skynet_ctx_t *ctx = (skynet_ctx_t*)p;
	if(ctx) free(ctx);
    return NULL;
}

void* skynet_create(void* parent)
{
    skynet_ctx_t *ctx = malloc(sizeof(skynet_ctx_t));
    if(!ctx) return NULL;
    memset(ctx, 0, sizeof(skynet_ctx_t));
    ctx->parent = parent;
    
    printf("skynet_create...\r\n");
    
    return ctx;
}


mm_module_t skynet_module = {
    .create = skynet_create,
    .destroy = skynet_destroy,
    .control = skynet_control,
    .handle = skynet_handle,
        
    .output_type = MM_TYPE_NONE,    // output for video sink
    .module_type = MM_TYPE_VDSP,     // module type is video algorithm
	.name = "SKYNET"
};