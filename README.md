# AmebaPro with KVS WebRTC and Producer
This project is going to demonstrate how to use KVS Producer and WebRTC on AmebaPro
<a href="https://www.amebaiot.com/zh/amebapro/">
  <img src="https://img.shields.io/badge/Realtek%20IoT-AmebaPro-blue" valign="middle" alt="test image size" height="15%" width="15%"/>
</a>  

Amazon FreeRTOS-LTS libraries are supported on AmebaPro now, it can be used to communicate with AWS IoT core easily!
[Version 202012.00](https://github.com/aws/amazon-freertos/tree/202012.00)

You can review the [ChangeLog](https://github.com/HungTseLee/KVS_WebRTC_on_AmebaPro#ChangeLog) before using the project.

## Brief Introduction to Amazon KVS and FreeRTOS-LTS  
:blue_book: **Amazon Kinesis Video Streams**  
&nbsp; include two main services, which are Producer and WebRTC
<a href="https://aws.amazon.com/kinesis/video-streams/?nc1=h_ls&amazon-kinesis-video-streams-resources-blog.sort-by=item.additionalFields.createdDate&amazon-kinesis-video-streams-resources-blog.sort-order=desc">
  <img src="https://img.shields.io/badge/-Link-lightgrey" valign="middle" alt="test image size" height="4%" width="4%"/>
</a>  

:blue_book: **KVS Producer**  
&nbsp; stream live video from devices to the AWS Cloud, or build applications for batch-oriented video analytics.
<a href="https://docs.aws.amazon.com/kinesisvideostreams/latest/dg/what-is-kinesis-video.html">
  <img src="https://img.shields.io/badge/-Link-lightgrey" valign="middle" alt="test image size" height="4%" width="4%"/>
</a>  

:blue_book: **KVS WebRTC**  
&nbsp; enable real-time communication (RTC) across browsers and mobile applications via simple APIs.
<a href="https://docs.aws.amazon.com/kinesisvideostreams-webrtc-dg/latest/devguide/what-is-kvswebrtc.html">
  <img src="https://img.shields.io/badge/-Link-lightgrey" valign="middle" alt="test image size" height="4%" width="4%"/>
</a>  

:blue_book: **FreeRTOS-LTS Libraries**  
&nbsp; provides feature stability, and security patches and critical bug fixes for two years from release date.
<a href="https://www.freertos.org/lts-libraries.html">
  <img src="https://img.shields.io/badge/-Link-lightgrey" valign="middle" alt="test image size" height="4%" width="4%"/>
</a>

## Applications on AmebaPro  
### :bulb: AI Face Detection
&nbsp; AmebaPro(Producer) + Rekognition(AWS AI) = video cloud storage and content analytics :cloud:  
<table width="100%" table-layout:fixed>
  <tr>
    <td width=50%><img src="photo/face_detection.jpg" valign="middle" alt="test image size" height=233px width=400px/></td>
    <td align=Left width=50%>
      1. Stream live video from AmebaPro to KVS<BR><BR>2. AI face detection by using AWS Rekognition API<BR><BR>&nbsp; :point_right: &nbsp;
      <a href="https://github.com/HungTseLee/KVS_WebRTC_on_AmebaPro/blob/main/AmebaPro_Amazon_KVS_Producer_Getting_Started_Guide_v1.1.pdf">
        <img src="https://img.shields.io/badge/-Getting%20Started-green" valign="middle" height=25px width=120px/>
      </a>
    </td>
  </tr>
</table>  

### :bulb: Real-time communucation  
&nbsp; AmebaPro(WebRTC master) + Viewer(WebRTC Client) = real-time communication, 1-way video & 2-way audio  
<table width="100%" table-layout:fixed>
  <tr>
    <td width=50%><img src="photo/p2p.jpg" valign="middle" alt="test image size" height=206px width=400px/></td>
    <td align=Left width=50%>
      1. AmebaPro start a signaling channel, as a master<BR><BR>2. Browser run as a viewer (client)<BR><BR>3. Start a P2P connection<BR><BR>&nbsp; :point_right: &nbsp;
      <a href="https://github.com/HungTseLee/KVS_WebRTC_on_AmebaPro/blob/main/AmebaPro_Amazon_KVS_WebRTC_Getting_Started_Guide_v1.1.pdf">
        <img src="https://img.shields.io/badge/-Getting%20Started-green" valign="middle" height=25px width=120px/>
      </a>
    </td>
  </tr>
</table>

### :bulb: Object Detection on Cloud
&nbsp; AmebaPro(image uploader) + Rekognition(AWS AI) = object detection and classification :cloud:  
<table style="width:100%; table-layout:fixed">
  <tr>
    <td width=50%><img src="photo/object_detection.jpg" valign="middle" alt="test image size" height=225px width=400px/></td>
    <td align=Left width=50%>
      1. Take a snapshot by camera sensor<BR><BR>2. Upload image from AmebaPro to S3<BR><BR>3. Trigger Lambda function to do object detection<BR><BR>&nbsp; :point_right: &nbsp;
      <a href="https://github.com/HungTseLee/KVS_WebRTC_on_AmebaPro/blob/main/AmebaPro_AWS_S3+Rekognition_Getting_Started_Guide_v1.2.pdf">
        <img src="https://img.shields.io/badge/-Getting%20Started-green" valign="middle" height=25px width=120px/>
      </a>
      <BR><BR>Notes: Based on FreeRTOS-v202012-LTS framework
    </td>
  </tr>
</table>  
      
### :bulb: FreeRTOS-LTS-v202012.00 Libraries
&nbsp; AmebaPro can connect to AWS IoT with the long term support libraries maintained by Amazon.
<a href="https://github.com/HungTseLee/KVS_WebRTC_on_AmebaPro/blob/main/AmebaPro_Amazon_FreeRTOS-LTS_Getting_Started_Guide_v1.2.pdf">
  <img src="https://img.shields.io/badge/-Getting%20Started-green" valign="middle" height=25px width=120px/>
</a>  
&nbsp; [FreeRTOS demos](https://docs.aws.amazon.com/freertos/latest/userguide/freertos-next-steps.html): coreHTTP, coreMQTT, Over-the-air updates(OTA), AWS IoT Device Shadow...  

### :bulb: Edge AI - Human Detection and Face Detetcion on AmebaPro
&nbsp; AmebaPro can do human detection or face detetcion by itself! (inference on edge device).
<a href="https://github.com/HungTseLee/KVS_WebRTC_on_AmebaPro/blob/main/Object_detection_demo.md">
  <img src="https://img.shields.io/badge/-Getting%20Started-green" valign="middle" height=25px width=120px/>
</a>


## Demo code  
:pencil2: **KVS WebRTC** &nbsp; &nbsp;`project/component/common/example/kvs_webrtc`  

:pencil2: **KVS Producer** &nbsp; &nbsp;`project/component/common/example/kvs_producer`  

:pencil2: **S3 file upload** &nbsp; &nbsp;`project/component/common/application/amazon/JPEG_snapshot_s3_upload_example`  

:pencil2: **FreeRTOS-LTS** &nbsp; &nbsp;`project/component/common/application/amazon/amazon-freertos-202012.00/demos`  


## IDE/toolchain Requirement

:hammer: **IAR Embedded Workbench - IAR Systems**  
&nbsp; Please use IAR version 8.3  

:hammer: **GCC toolchain**  
&nbsp; Linux: asdk-6.4.1-linux-newlib-build-3026-x86_64  
&nbsp; Cygwin: asdk-6.4.1-cygwin-newlib-build-2778-i686  


## Clone Project  
To check out this repository:  

```
git clone --recurse-submodules https://github.com/HungTseLee/KVS_WebRTC_on_AmebaPro.git
```

If you already have a checkout, run the following command to sync submodules recursively:

```
git submodule update --init --recursive
```

If there is GCC makefile error like: "No rule to make target …", it may mean that some codes have not been downloaded correctly.  
Please run the above command again to download the missing codes.  

If there is compile error with shell script in "component/soc/realtek/8195b/misc/gcc_utility/", you may need to run following command  
```
dos2unix component/soc/realtek/8195b/misc/gcc_utility/*
```


## ChangeLog
* (Jul 12, 2021) Release version v2.0 for using KVS and LTS library on AmebaPro.
* (Jul 09, 2021) Support Amazon FreeRTOS-LTS library and its demos. version 202012.00.<br>The branch: **AmebaPro-202012.00-LTS-dev** has been merged into **main**.
* (May 12, 2021) Release version v1.0 for using KVS on AmebaPro.