#ifndef EXAMPLE_OBJECT_DETECTION_INIT_H
#define EXAMPLE_OBJECT_DETECTION_INIT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sensor.h"
#include "video_common_api.h"
#include "platform_opts.h"
#if (SENSOR_USE== SENSOR_PS5270)
#define MAX_W 1440
#define MAX_H 1440
#else
#define MAX_W 1280//1920
#define MAX_H 720//1080
#endif

#define V1_WIDTH  1280
#define V1_HEIGHT 720
#define V2_WIDTH  224//320
#define V2_HEIGHT 224//180

#define USE_H264 1
#define USE_SKYNET 0
#define USE_RTSP 1

#ifdef __cplusplus
}
#endif

#endif /* EXAMPLE_OBJECT_DETECTION_INIT_H */

