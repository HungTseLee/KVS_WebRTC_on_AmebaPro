# Edge AI - human detection or face detetcion on AmebaPro

How to implement human detection or face detetcion on edge device (AmebaPro)

## Check the model of camera sensor 

Please check your camera sensor model, and define it in <AmebaPro_SDK>/project/realtek_amebapro_v0_example/inc/sensor.h.

```
#define SENSOR_USE      	SENSOR_XXXX
```

## Configure Example Setting

Before run the example, you need to check the object detection is enabled in <AmebaPro_SDK>/project/realtek_amebapro_v0_example/inc/platform_opts.h.

```
/* For object detection example */
#define CONFIG_EXAMPLE_OBJECT_DETECTION         1
```

## Build project and flash image

To build the example run the following command:

```
cd <AmebaPro_SDK>/project/realtek_amebapro_v0_example/GCC-RELEASE
make -f Makefile_amazon_kvs all
```

If there is compile error with shell script in "component/soc/realtek/8195b/misc/gcc_utility/", you may need to run following command

```
$ dos2unix component/soc/realtek/8195b/misc/gcc_utility/*
```

The image is located in <AmebaPro_SDK>/project/realtek_amebapro_v0_example/GCC-RELEASE/application_is/flash_is.bin

Make sure your AmebaPro is connected and powered on. Use the Realtek image tool to flash image and check the logs.

[How to use Realtek image tool? See section 1.3 in AmebaPro's application note](https://github.com/HungTseLee/KVS_WebRTC_on_AmebaPro/blob/main/doc/AN0300%20Realtek%20AmebaPro%20application%20note.en.pdf)

## Run the example and use VLC to validate the result  

Reboot your device and check the logs.  

Then, open VLC and create a network stream with URL: rtsp://192.168.x.xx:554   

If everything works fine, you should see the object detection result on VLC player.


### Additional settings

1. In object_detection_init.h, use the macro USE_SKYNET and USE_RTSP to select weither to stream with skynet or rtsp(default).  

2. In module_obj_detect, command "CMD_OBJ_DETECT_HUMAN" is set to detect human(default). "CMD_OBJ_DETECT_FACE" is set to detect face.  

3. With padding method, the last parameter of object_detection function in "module_obj_detect.c" should be set to 1.<br>
```
object_detection(ctx->hold_image_address, ctx->params.width, ctx->params.height, 1, ctx->box.output_boxes, ctx->box.output_classes, ctx->box.output_scores, ctx->box.output_num_detections, 1);
```

4. Ch2 image size can be set by changing V2_WIDTH and V2_HEIGHT in "object_detection_init.h"  
```
#define V2_WIDTH  224//320
#define V2_HEIGHT 224//180
```