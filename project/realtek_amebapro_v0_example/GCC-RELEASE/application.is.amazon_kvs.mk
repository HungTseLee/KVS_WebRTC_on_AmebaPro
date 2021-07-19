
# Initialize tool chain
# -------------------------------------------------------------------
#ARM_GCC_TOOLCHAIN = ../../../tools/arm-none-eabi-gcc/gcc6/bin/

AMEBAPRO_TOOLDIR	= ../../../component/soc/realtek/8195b/misc/iar_utility
FLASH_TOOLDIR = ../../../component/soc/realtek/8195b/misc/gcc_utility

OS := $(shell uname)

ifeq ($(findstring CYGWIN, $(OS)), CYGWIN)
	ARM_GCC_TOOLCHAIN = ../../../tools/arm-none-eabi-gcc/asdk/cygwin/newlib/bin
	ELF2BIN = $(AMEBAPRO_TOOLDIR)/elf2bin.exe
	CHKSUM = $(AMEBAPRO_TOOLDIR)/checksum.exe
endif

ifeq ($(findstring MINGW32, $(OS)), MINGW32)
	ARM_GCC_TOOLCHAIN = ../../../tools/arm-none-eabi-gcc/asdk/mingw32/newlib/bin
	ELF2BIN = $(AMEBAPRO_TOOLDIR)/elf2bin.exe
	CHKSUM = $(AMEBAPRO_TOOLDIR)/checksum.exe
endif

ifeq ($(findstring Linux, $(OS)), Linux)
	ARM_GCC_TOOLCHAIN = ../../../tools/arm-none-eabi-gcc/asdk/linux/newlib/bin
	ELF2BIN = $(AMEBAPRO_TOOLDIR)/elf2bin.linux	
	CHKSUM = $(AMEBAPRO_TOOLDIR)/checksum.linux
endif

#CROSS_COMPILE = $(ARM_GCC_TOOLCHAIN)/arm-none-eabi-
CROSS_COMPILE = $(ARM_GCC_TOOLCHAIN)/arm-none-eabi-

# Compilation tools
AR = $(CROSS_COMPILE)ar
CC = $(CROSS_COMPILE)gcc
AS = $(CROSS_COMPILE)as
NM = $(CROSS_COMPILE)nm
LD = $(CROSS_COMPILE)gcc
GDB = $(CROSS_COMPILE)gdb
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump

OS := $(shell uname)

LDSCRIPT := ./rtl8195bhp_ram_is.ld
#LDSCRIPT := ./rtl8195bhp_ram_mps2.ld


# Initialize target name and target object files
# -------------------------------------------------------------------

all: prebuild build_info application sensor manipulate_images

mp:  prebuild build_info application manipulate_images

TARGET=application_is

OBJ_DIR=$(TARGET)/Debug/obj
BIN_DIR=$(TARGET)/Debug/bin
INFO_DIR=$(TARGET)/Debug/info

ROMIMG = 

# Include folder list
# -------------------------------------------------------------------

INCLUDES =
INCLUDES += -I../inc
INCLUDES += -I../../../lib_amazon/gcc_include
INCLUDES += -I../src/eval/sensor_board_v1
INCLUDES += -I../../../component/soc/realtek/8195b/cmsis/rtl8195b-hp/include
INCLUDES += -I../../../component/common/drivers/sdio/realtek/sdio_host/src
INCLUDES += -I../../../component/soc/realtek/8195b/cmsis/cmsis-core/include
INCLUDES += -I../../../component/soc/realtek/8195b/cmsis/rtl8195b-hp/lib/include
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/include
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/lib/include
INCLUDES += -I../../../component/soc/realtek/8195b/app/rtl_printf/include
INCLUDES += -I../../../component/soc/realtek/8195b/app/shell
INCLUDES += -I../../../component/soc/realtek/8195b/app/stdio_port
INCLUDES += -I../../../component/os/freertos
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/include
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/GCC/ARM_RTL8195B
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/secure
INCLUDES += -I../../../component/os/os_dep/include
INCLUDES += -I../../../component/soc/realtek/8195b/misc/utilities/include
INCLUDES += -I../../../component/soc/realtek/8195b/misc/platform
INCLUDES += -I../../../component/soc/realtek/8195b/misc/driver
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/include/usb_otg
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/lib/include/usb_otg
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/lib/video/video/include
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/lib/video/lcdc/include
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/lib/video/isp/include
INCLUDES += -I../../../component/common/api
INCLUDES += -I../../../component/common/api/at_cmd
INCLUDES += -I../../../component/common/api/platform
INCLUDES += -I../../../component/common/api/wifi
INCLUDES += -I../../../component/common/api/network/include
INCLUDES += -I../../../component/common/audio/haac
INCLUDES += -I../../../component/common/audio/speex
INCLUDES += -I../../../component/common/network/lwip/lwip_v2.0.2/src/include
INCLUDES += -I../../../component/common/network/lwip/lwip_v2.0.2/src/include/lwip
INCLUDES += -I../../../component/common/network/lwip/lwip_v2.0.2/port/realtek
INCLUDES += -I../../../component/common/network/lwip/lwip_v2.0.2/port/realtek/freertos
INCLUDES += -I../../../component/common/drivers/wlan/realtek/include
INCLUDES += -I../../../component/common/drivers/wlan/realtek/src/osdep
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/video/lcdc/include
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/video/isp/include
INCLUDES += -I../../../component/common/mbed/hal
INCLUDES += -I../../../component/common/mbed/hal_ext
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/include/usb_otg
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/video/video/include
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/video/lcdc/include
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/video/isp/include
INCLUDES += -I../../../component/soc/realtek/8195b/mbed-drivers/include
INCLUDES += -I../../../component/os/freertos
INCLUDES += -I../../../component/os/os_dep/include
INCLUDES += -I../../../component/common/media/mmfv2
INCLUDES += -I../../../component/common/media/rtp_codec
INCLUDES += -I../../../component/common/media/samples
INCLUDES += -I../../../component/common/network
INCLUDES += -I../../../component/common/example
INCLUDES += -I../../../component/common/example/qr_code_scanner
INCLUDES += -I../../../component/common/drivers/video/realtek/common
INCLUDES += -I../../../component/common/drivers/video/realtek/common/h264enc/inc
INCLUDES += -I../../../component/common/drivers/video/realtek/common/h264enc/source/common
INCLUDES += -I../../../component/common/drivers/video/realtek/common/h264enc/source/camstab
INCLUDES += -I../../../component/common/drivers/video/realtek/common/h264enc/source/h264
INCLUDES += -I../../../component/common/drivers/video/realtek/common
INCLUDES += -I../../../component/common/drivers/video/realtek/common/include
INCLUDES += -I../../../component/soc/realtek/8195b/cmsis/cmsis-dsp/include
INCLUDES += -I../../../component/common/audio/faac/libfaac
INCLUDES += -I../../../component/common/audio/faac/include
INCLUDES += -I../../../component/soc/realtek/8195b/mbed-hal/targets/hal/rtl8195bh
INCLUDES += -I../../../component/common/file_system/fatfs
INCLUDES += -I../../../component/common/file_system/fatfs/r0.14
INCLUDES += -I../../../component/common/drivers/sdio/realtek/sdio_host/inc
INCLUDES += -I../../../component/soc/realtek/8195b/cmsis/cmsis-core/include
INCLUDES += -I../../../component/soc/realtek/8195a/fwlib/rtl8195a
INCLUDES += -I../../../component/soc/realtek/8195a/misc/os
INCLUDES += -I../../../component/soc/realtek/8195b/mbed-hal/targets/hal/rtl8195bh
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/lib/video/enc/include
INCLUDES += -I../../../component/common/api/wifi/rtw_wpa_supplicant/src
INCLUDES += -I../../../component/soc/realtek/8711b/swlib/std_lib/include
INCLUDES += -I../../../component/common/network/http2/nghttp2-1.31.0/includes
INCLUDES += -I../../../component/common/application/mqtt/MQTTClient
INCLUDES += -I../../../component/common/network/coap/include
INCLUDES += -I../../../component/common/network/ssl/polarssl-1.3.8/include
INCLUDES += -I../../../component/common/network/ssl/mbedtls-2.16.6/include
INCLUDES += -I../../../component/common/network/ssl/ssl_ram_map/rom
INCLUDES += -I../../../component/common/drivers/i2s
INCLUDES += -I../../../component/common/utilities
INCLUDES += -I../../../component/common/application
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/include
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/lib/include/usb_otg
INCLUDES += -I../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/source/ram_ns/include
INCLUDES += -I../../../component/common/video/v4l2/inc
INCLUDES += -I../../../component/common/drivers/usb_class/host/uvc/inc
INCLUDES += -I../../../component/common/drivers/usb_class/device
INCLUDES += -I../../../component/common/drivers/usb_class/device/class
INCLUDES += -I../../../component/common/drivers/modules
INCLUDES += -I../../../component/common/media/framework
INCLUDES += -I../../../component/common/media/codec/mp3
INCLUDES += -I../../../component/common/media/rtp_codec/mjpeg
INCLUDES += -I../../../component/common/media/muxer
INCLUDES += -I../../../component/common/media/mmfv2
INCLUDES += -I../../../component/common/audio
INCLUDES += -I../../../component/common/media/rtp_codec
INCLUDES += -I../../../component/soc/realtek/8195b/app/xmodem/rom
INCLUDES += -I../../../component/common/test
INCLUDES += -I../../../component/common/file_system
INCLUDES += -I../../../component/common/file_system/dct
INCLUDES += -I../../../component/common/drivers/video/realtek/common/include/feature
INCLUDES += -I../../../component/common/mbed/hal
INCLUDES += -I../../../component/common/mbed/hal_ext
INCLUDES += -I../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh
INCLUDES += -I../../../component/common/application/qr_code_scanner/inc
INCLUDES += -I../../../component/common/application/qr_code_scanner/src
INCLUDES += -I../../../component/common/application/qr_code_scanner/src/zbar
INCLUDES += -I../../../component/common/application/qr_code_scanner/src/zbar/decoder
INCLUDES += -I../../../component/common/application/qr_code_scanner/src/zbar/include
INCLUDES += -I../../../component/common/application/qr_code_scanner/src/zbar/qrcode
#INCLUDES += -I../../../component/common/audio/AEC/WebrtcAEC
#INCLUDES += -I../../../component/common/audio/AEC/WebrtcAEC/utility
#INCLUDES += -I../../../component/common/audio/AEC/WebrtcAEC/include
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/include
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/FreeRTOS-Plus-POSIX/include/portable/realtek/rtl8195
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/FreeRTOS-Plus-POSIX/include
INCLUDES += -I../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/include/private
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-pic/src/client/include
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-pic/src/common/include
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-pic/src/heap/include
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-pic/src/state/include
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-pic/src/trace/include
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-pic/src/utils/include
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-pic/src/view/include
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-pic/src/mkvgen/include
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-producer-c/src/include
INCLUDES += -I../../../lib_amazon/libsrtp/crypto/include
INCLUDES += -I../../../lib_amazon/libsrtp/include
INCLUDES += -I../../../lib_amazon/libsrtp
INCLUDES += -I../../../lib_amazon/libwebsockets
INCLUDES += -I../../../lib_amazon/libwebsockets/include
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/core
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/core-net
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/event-libs
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/event-libs/poll
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/plat/freertos
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/plat/freertos/esp32
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/roles
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/roles/h1
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/roles/h2
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/roles/http
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/roles/ws
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/system/smd
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/tls
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/tls/mbedtls/wrapper/include
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/tls/mbedtls/wrapper/include/internal
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/tls/mbedtls/wrapper/include/openssl
INCLUDES += -I../../../lib_amazon/libwebsockets/lib/tls/mbedtls/wrapper/include/platform
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-webrtc-sdk-c/src/include
INCLUDES += -I../../../lib_amazon/amazon-kinesis-video-streams-producer-embedded-c/src/include
INCLUDES += -I../../../component/common/audio/libogg-1.3.3
INCLUDES += -I../../../component/common/audio/libogg-1.3.3/include
INCLUDES += -I../../../component/common/audio/opus-1.3.1
INCLUDES += -I../../../component/common/audio/opus-1.3.1/celt
INCLUDES += -I../../../component/common/audio/opus-1.3.1/include
INCLUDES += -I../../../component/common/audio/opus-1.3.1/silk
INCLUDES += -I../../../component/common/audio/opus-1.3.1/silk/fixed
INCLUDES += -I../../../component/common/audio/opus-1.3.1/src
INCLUDES += -I../../../component/common/audio/opus-1.3.1/test
INCLUDES += -I../../../component/common/audio/opusfile-0.11/
INCLUDES += -I../../../component/common/audio/opusfile-0.11/examples
INCLUDES += -I../../../component/common/audio/opusfile-0.11/include
INCLUDES += -I../../../component/common/audio/opusfile-0.11/src
INCLUDES += -I../../../component/common/audio/libopusenc-0.2.1/src
INCLUDES += -I../../../component/common/audio/libopusenc-0.2.1/include
INCLUDES += -I../../../lib_amazon/libusrsctp/usrsctplib
INCLUDES += -I../../../lib_amazon/libusrsctp/usrsctplib/netinet
INCLUDES += -I../../../lib_amazon/libusrsctp/usrsctplib/netinet6
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/freertos_plus/standard/utils/include
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/logging/include
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/abstractions/wifi/include
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/3rdparty/unity/src
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/3rdparty/unity/extras/fixture/src
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/common/include
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/abstractions/platform/freertos/include
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/abstractions/platform/include
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/abstractions/secure_sockets/include
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/common/include/private
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/abstractions/pkcs11/corePKCS11/source/include
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/abstractions/pkcs11/corePKCS11/source/dependency/3rdparty/pkcs11
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/common/include/private
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/common/include/private
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/abstractions/backoff_algorithm/source/include
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/coreHTTP/source/include
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/coreHTTP/source/interface
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/abstractions/transport/secure_sockets
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/coreMQTT/source/include
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/3rdparty/jsmn
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/freertos_plus/aws/ota/include
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/3rdparty/mbedtls_utils
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/3rdparty/mbedtls_config______
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/3rdparty/mbedtls/include______
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/freertos_plus/standard/crypto/include
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/demos/dev_mode_key_provisioning/include
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/c_sdk/aws/defender/include
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/mqtt/include
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/serializer/include
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/c_sdk/aws/shadow/include
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/mqtt/test/access
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/coreHTTP/source/dependency/3rdparty/http_parser
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/https/include
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/https/test/access
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/mqtt/src
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/c_sdk/standard/mqtt/test/mock
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/3rdparty/tinycbor/src
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/freertos_plus/aws/ota/src
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/freertos_plus/standard/tls/include
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/demos/common/pkcs11_helpers
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/demos/include
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/demos/network_manager
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/vendors/realtek/boards/amebaPro/aws_demos/config_files
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/demos/common/http_demo_helpers
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/device_shadow_for_aws/source/include
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/coreJSON/source/include
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/demos/common/mqtt_demo_helpers
INCLUDES += -I../../../component/common/application/amazon/amazon-freertos-202012.00/libraries/freertos_plus/aws/ota/test


# Source file list
# SRC_C -> to Flash
# SRAM_C -> to internal ram
# ERAM_C -> to external ram
# -------------------------------------------------------------------

SRC_ASM = 
SRC_C =
SRAM_C =
ERAM_C =
CINIT_C = 
ITCM_C = 

# -------------------------------------------------------------------
#cmsis
#dsp
SRC_C += ../../../component/soc/realtek/8195b/cmsis/cmsis-dsp/source/BasicMathFunctions/arm_add_f32.c
SRC_ASM += ../../../component/soc/realtek/8195b/cmsis/cmsis-dsp/source/TransformFunctions/arm_bitreversal2.S
SRC_C += ../../../component/soc/realtek/8195b/cmsis/cmsis-dsp/source/TransformFunctions/arm_cfft_f32.c
SRC_C += ../../../component/soc/realtek/8195b/cmsis/cmsis-dsp/source/TransformFunctions/arm_cfft_radix8_f32.c
SRC_C += ../../../component/soc/realtek/8195b/cmsis/cmsis-dsp/source/ComplexMathFunctions/arm_cmplx_mag_f32.c
SRC_C += ../../../component/soc/realtek/8195b/cmsis/cmsis-dsp/source/CommonTables/arm_common_tables.c
SRC_C += ../../../component/soc/realtek/8195b/cmsis/cmsis-dsp/source/CommonTables/arm_const_structs.c
SRC_C += ../../../component/soc/realtek/8195b/cmsis/cmsis-dsp/source/StatisticsFunctions/arm_max_f32.c
SRC_C += ../../../component/soc/realtek/8195b/cmsis/cmsis-dsp/source/BasicMathFunctions/arm_mult_f32.c
SRC_C += ../../../component/soc/realtek/8195b/cmsis/cmsis-dsp/source/TransformFunctions/arm_rfft_fast_f32.c
SRC_C += ../../../component/soc/realtek/8195b/cmsis/cmsis-dsp/source/TransformFunctions/arm_rfft_fast_init_f32.c
SRC_C += ../../../component/soc/realtek/8195b/cmsis/cmsis-dsp/source/BasicMathFunctions/arm_scale_f32.c

SRC_C += ../../../component/soc/realtek/8195b/cmsis/rtl8195b-hp/source/ram_s/app_start.c
SRC_C += ../../../component/soc/realtek/8195b/cmsis/rtl8195b-hp/source/ram/mpu_config.c

#console
SRC_C += ../../../component/common/api/at_cmd/atcmd_isp.c
SRC_C += ../../../component/common/api/at_cmd/atcmd_lwip.c
SRC_C += ../../../component/common/api/at_cmd/atcmd_media.c
SRC_C += ../../../component/common/api/at_cmd/atcmd_sys.c
SRC_C += ../../../component/common/api/at_cmd/atcmd_wifi.c
SRC_C += ../../../component/common/api/at_cmd/atcmd_qr_code.c
SRC_C += ../../../component/soc/realtek/8195b/app/shell/cmd_shell.c
SRC_C += ../../../component/soc/realtek/8195b/misc/driver/log_service.c
SRC_C += ../../../component/soc/realtek/8195b/misc/driver/low_level_io.c
SRC_C += ../../../component/soc/realtek/8195b/misc/driver/rtl_console.c

#multimedia
#mmfv2
SRC_C += ../../../component/common/media/mmfv2/module_aac.c
SRC_C += ../../../component/common/media/mmfv2/module_aad.c
SRC_C += ../../../component/common/media/mmfv2/module_array.c
SRC_C += ../../../component/common/media/mmfv2/module_audio.c
SRC_C += ../../../component/common/media/mmfv2/module_g711.c
SRC_C += ../../../component/common/media/mmfv2/module_h264.c
SRC_C += ../../../component/common/media/mmfv2/module_i2s.c
SRC_C += ../../../component/common/media/mmfv2/module_isp.c
SRC_C += ../../../component/common/media/mmfv2/module_jpeg.c
SRC_C += ../../../component/common/media/mmfv2/module_mp4.c
SRC_C += ../../../component/common/media/mmfv2/module_rtp.c
SRC_C += ../../../component/common/media/mmfv2/module_rtsp2.c
SRC_C += ../../../component/common/media/mmfv2/module_uvcd.c
SRC_C += ../../../component/common/media/mmfv2/module_httpfs.c
SRC_C += ../../../component/common/media/mmfv2/module_dup.c

#mmfv2_example
SRC_C += ../../../component/common/example/media_framework/mmf2_example_2way_audio_init.c
SRC_C += ../../../component/common/example/media_framework/mmf2_example_a_init.c
SRC_C += ../../../component/common/example/media_framework/mmf2_example_aac_array_rtsp_init.c
SRC_C += ../../../component/common/example/media_framework/mmf2_example_aacloop_init.c
SRC_C += ../../../component/common/example/media_framework/mmf2_example_audioloop_init.c
SRC_C += ../../../component/common/example/media_framework/mmf2_example_av21_init.c
SRC_C += ../../../component/common/example/media_framework/mmf2_example_av2_init.c
SRC_C += ../../../component/common/example/media_framework/mmf2_example_av_init.c
SRC_C += ../../../component/common/example/media_framework/mmf2_example_av_mp4_init.c
SRC_C += ../../../component/common/example/media_framework/mmf2_example_av_rtsp_mp4_init.c
SRC_C += ../../../component/common/example/media_framework/mmf2_example_av_mp4_httpfs_init.c
SRC_C += ../../../component/common/example/media_framework/mmf2_example_g711loop_init.c
SRC_C += ../../../component/common/example/media_framework/mmf2_example_h264_2way_audio_pcmu_doorbell_init.c
SRC_C += ../../../component/common/example/media_framework/mmf2_example_h264_2way_audio_pcmu_init.c
SRC_C += ../../../component/common/example/media_framework/mmf2_example_h264_array_rtsp_init.c
SRC_C += ../../../component/common/example/media_framework/mmf2_example_i2s_audio_init.c
SRC_C += ../../../component/common/example/media_framework/mmf2_example_joint_test_init.c
SRC_C += ../../../component/common/example/media_framework/mmf2_example_joint_test_rtsp_mp4_init.c
SRC_C += ../../../component/common/example/media_framework/mmf2_example_param.c
SRC_C += ../../../component/common/example/media_framework/mmf2_example_pcmu_array_rtsp_init.c
SRC_C += ../../../component/common/example/media_framework/mmf2_example_rtp_aad_init.c
SRC_C += ../../../component/common/example/media_framework/mmf2_example_simo_init.c
SRC_C += ../../../component/common/example/media_framework/mmf2_example_v1_init.c
SRC_C += ../../../component/common/example/media_framework/mmf2_example_v1_param_change_init.c
SRC_C += ../../../component/common/example/media_framework/mmf2_example_v2_init.c
SRC_C += ../../../component/common/example/media_framework/mmf2_example_v3_init.c
SRC_C += ../../../component/common/example/media_framework/mmf2_example_av_dup_init.c
SRC_C += ../../../component/common/example/media_framework/mmf2_example_mp4_dual_init.c
SRC_C += ../../../component/common/example/media_framework/snapshot_setting.c
#SRC_C += ../../../component/common/example/media_framework/example_media_framework_sd_detect.c
SRC_C += ../../../component/common/example/media_uvcd/usbd_uvc_parm.c

#sensor
SRC_C += ../../../component/common/media/framework/sensor_service.c
SRC_C += ../../../component/common/drivers/video/realtek/common/encoder_buffer_handler.c
SRC_C += ../../../component/common/media/framework/jpeg_snapshot.c
SRC_C += ../../../component/common/media/media_amebacam_broadcast.c
SRC_C += ../../../component/common/media/framework/mmf_command.c
SRC_C += ../../../component/common/media/framework/snapshot_sd_handler.c
SRC_C += ../../../component/common/media/framework/snapshot_tftp_handler.c

#network
#api
#wifi
#rtw_wpa_supplicant
SRC_C += ../../../component/common/api/wifi/rtw_wpa_supplicant/src/crypto/tls_polarssl.c
SRC_C += ../../../component/common/api/wifi/rtw_wpa_supplicant/wpa_supplicant/wifi_eap_config.c
SRC_C += ../../../component/common/api/wifi/rtw_wpa_supplicant/wpa_supplicant/wifi_p2p_config.c
SRC_C += ../../../component/common/api/wifi/rtw_wpa_supplicant/wpa_supplicant/wifi_wps_config.c
SRC_C += ../../../component/common/api/wifi/wifi_conf.c
SRC_C += ../../../component/common/api/wifi/wifi_ind.c
SRC_C += ../../../component/common/api/wifi/wifi_promisc.c
SRC_C += ../../../component/common/api/wifi/wifi_simple_config.c
SRC_C += ../../../component/common/api/wifi/wifi_util.c
SRC_C += ../../../component/common/api/lwip_netconf.c

#app
#mqtt
##Debug
##SRC_C += ../../../component/common/application/mqtt/MQTTClient/MQTTClient.c
##SRC_C += ../../../component/common/application/mqtt/MQTTPacket/MQTTConnectClient.c
##SRC_C += ../../../component/common/application/mqtt/MQTTPacket/MQTTConnectServer.c
##SRC_C += ../../../component/common/application/mqtt/MQTTPacket/MQTTDeserializePublish.c
##SRC_C += ../../../component/common/application/mqtt/MQTTPacket/MQTTFormat.c
##SRC_C += ../../../component/common/application/mqtt/MQTTClient/MQTTFreertos.c
##SRC_C += ../../../component/common/application/mqtt/MQTTPacket/MQTTPacket.c
##SRC_C += ../../../component/common/application/mqtt/MQTTPacket/MQTTSerializePublish.c
##SRC_C += ../../../component/common/application/mqtt/MQTTPacket/MQTTSubscribeClient.c
##SRC_C += ../../../component/common/application/mqtt/MQTTPacket/MQTTSubscribeServer.c
##SRC_C += ../../../component/common/application/mqtt/MQTTPacket/MQTTUnsubscribeClient.c
##SRC_C += ../../../component/common/application/mqtt/MQTTPacket/MQTTUnsubscribeServer.c

SRC_C += ../../../component/soc/realtek/8195b/misc/platform/ota_8195b.c
SRC_C += ../../../component/common/api/network/src/ping_test.c
SRC_C += ../../../component/common/utilities/ssl_client.c
SRC_C += ../../../component/common/utilities/ssl_client_ext.c
SRC_C += ../../../component/common/utilities/tcptest.c
SRC_C += ../../../component/common/api/network/src/wlan_network.c

#coap
SRC_C += ../../../component/common/network/coap/sn_coap_ameba_port.c
SRC_C += ../../../component/common/network/coap/sn_coap_builder.c
SRC_C += ../../../component/common/network/coap/sn_coap_header_check.c
SRC_C += ../../../component/common/network/coap/sn_coap_parser.c
SRC_C += ../../../component/common/network/coap/sn_coap_protocol.c

#googlenest
SRC_C += ../../../component/common/application/google/google_tls.c

#http
SRC_C += ../../../component/common/network/httpc/httpc_tls.c
SRC_C += ../../../component/common/network/httpd/httpd_tls.c

#lwip
#api
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/api/api_lib.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/api/api_msg.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/api/err.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/api/netbuf.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/api/netdb.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/api/netifapi.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/api/sockets.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/api/tcpip.c

#core
#ipv4
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/ipv4/autoip.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/ipv4/dhcp.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/ipv4/etharp.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/ipv4/icmp.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/ipv4/igmp.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/ipv4/ip4.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/ipv4/ip4_addr.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/ipv4/ip4_frag.c
#ipv6
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/ipv6/dhcp6.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/ipv6/ethip6.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/ipv6/icmp6.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/ipv6/inet6.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/ipv6/ip6.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/ipv6/ip6_addr.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/ipv6/ip6_frag.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/ipv6/mld6.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/ipv6/nd6.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/def.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/dns.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/inet_chksum.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/init.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/ip.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/netif.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/pbuf.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/raw.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/stats.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/sys.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/tcp.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/tcp_in.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/tcp_out.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/timeouts.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/udp.c
##ITMC -> DTCM
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/mem.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/core/memp.c

#netif
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/netif/ethernet.c
SRC_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/netif/ppp/auth.c
SRC_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/netif/ppp/ccp.c
SRC_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/netif/ppp/chap-md5.c
SRC_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/netif/ppp/chap-new.c
SRC_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/netif/ppp/chap_ms.c
SRC_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/netif/ppp/demand.c
SRC_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/netif/ppp/eap.c
SRC_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/netif/ppp/eui64.c
SRC_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/netif/ppp/fsm.c
SRC_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/netif/ppp/ipcp.c
SRC_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/netif/ppp/ipv6cp.c
SRC_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/netif/ppp/lcp.c
SRC_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/netif/ppp/lwip_ecp.c
SRC_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/netif/ppp/magic.c
SRC_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/netif/ppp/polarssl/lwip_md5.c
SRC_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/netif/ppp/mppe.c
SRC_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/netif/ppp/multilink.c
SRC_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/netif/ppp/ppp.c
SRC_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/netif/ppp/pppapi.c
SRC_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/netif/ppp/pppcrypt.c
SRC_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/netif/ppp/pppoe.c
SRC_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/netif/ppp/pppol2tp.c
SRC_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/netif/ppp/pppos.c
SRC_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/netif/ppp/upap.c
SRC_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/netif/ppp/utils.c
SRC_C += ../../../component/common/network/lwip/lwip_v2.0.2/src/netif/ppp/vj.c

#port
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/port/realtek/freertos/ethernetif.c
ITCM_C += ../../../component/common/drivers/wlan/realtek/src/osdep/lwip_intf.c
ITCM_C += ../../../component/common/network/lwip/lwip_v2.0.2/port/realtek/freertos/sys_arch.c

ITCM_C += ../../../component/common/network/dhcp/dhcps.c
ITCM_C += ../../../component/common/network/sntp/sntp.c

#mdns
SRC_C += ../../../component/common/network/mDNS/mDNSPlatform.c

#ssl
#mbedtls
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/aes_alt.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/aesni.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/arc4.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/aria.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/asn1parse.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/asn1write.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/base64.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/bignum.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/blowfish.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/camellia.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/ccm.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/certs.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/chacha20.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/chachapoly.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/cipher.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/cipher_wrap.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/cmac.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/ctr_drbg.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/debug.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/des.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/dhm.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/ecdh.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/ecdsa.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/ecjpake.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/ecp.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/ecp_curves.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/entropy.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/entropy_alt.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/entropy_poll.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/error.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/gcm.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/havege.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/hkdf.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/hmac_drbg.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/md.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/md2.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/md4.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/md5.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/md_wrap.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/memory_buffer_alloc.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/net_sockets.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/nist_kw.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/oid.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/padlock.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/pem.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/pk.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/pk_wrap.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/pkcs11.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/pkcs12.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/pkcs5.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/pkparse.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/pkwrite.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/platform.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/platform_util.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/poly1305.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/ripemd160.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/rsa.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/rsa_internal.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/sha1.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/sha256.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/sha512.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/ssl_cache.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/ssl_ciphersuites.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/ssl_cli.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/ssl_cookie.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/ssl_srv.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/ssl_ticket.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/ssl_tls.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/threading.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/timing.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/version.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/version_features.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/x509.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/x509_create.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/x509_crl.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/x509_crt.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/x509_csr.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/x509write_crt.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/x509write_csr.c
SRC_C += ../../../component/common/network/ssl/mbedtls-2.16.6/library/xtea.c

#ssl_ram_map
SRC_C += ../../../component/common/network/ssl/ssl_ram_map/rom/rom_ssl_ram_map.c
SRC_C += ../../../component/common/network/ssl/ssl_func_stubs/ssl_func_stubs.c

#websocket
SRC_C += ../../../component/common/network/websocket/wsclient_tls.c
SRC_C += ../../../component/common/network/websocket/wsserver_tls.c

#rtw_opt_skbuf
SRC_C += ../../../component/common/drivers/wlan/realtek/src/core/option/rtw_opt_skbuf.c

#os
#freertos
#portable
##SRC_C += ../../../component/os/freertos/freertos_v10.0.0/portable/MemMang/heap_4.c
##Debug
ITCM_C += ../../../component/os/freertos/freertos_v10.0.0/portable/GCC/ARM_RTL8195B/port.c
ITCM_C += ../../../component/os/freertos/freertos_v10.0.0/croutine.c
ITCM_C += ../../../component/os/freertos/freertos_v10.0.0/event_groups.c
ITCM_C += ../../../component/os/freertos/freertos_v10.0.0/list.c
ITCM_C += ../../../component/os/freertos/freertos_v10.0.0/queue.c
ITCM_C += ../../../component/os/freertos/freertos_v10.0.0/stream_buffer.c
ITCM_C += ../../../component/os/freertos/freertos_v10.0.0/tasks.c
ITCM_C += ../../../component/os/freertos/freertos_v10.0.0/timers.c
#posix
ITCM_C += ../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_clock.c
ITCM_C += ../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_mqueue.c
ITCM_C += ../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_pthread.c
ITCM_C += ../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_pthread_barrier.c
ITCM_C += ../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_pthread_cond.c
ITCM_C += ../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_pthread_mutex.c
ITCM_C += ../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_sched.c
ITCM_C += ../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_semaphore.c
ITCM_C += ../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_timer.c
ITCM_C += ../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_unistd.c
ITCM_C += ../../../component/os/freertos/freertos_v10.0.0/portable/posix/lib/FreeRTOS-Plus-POSIX/source/FreeRTOS_POSIX_utils.c
SRC_C += ../../../component/os/freertos/cmsis_os.c
SRC_C += ../../../component/os/os_dep/device_lock.c
SRC_C += ../../../component/os/freertos/freertos_cb.c
SRC_C += ../../../component/os/freertos/freertos_service.c
SRC_C += ../../../component/os/os_dep/osdep_service.c

#peripheral
#api
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh/analogin_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh/audio_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh/crypto_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh/dma_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh/efuse_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh/ethernet_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh/gpio_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh/gpio_irq_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh/i2c_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh/i2s_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh/icc_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh/pcm_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh/pinmap.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh/pinmap_common.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh/power_mode_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh/pwmout_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh/serial_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh/sgpio_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh/spdio_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh/spi_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh/sys_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh/timer_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh/us_ticker.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh/us_ticker_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh/wait_api.c
SRC_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh/wdt_api.c

#hal
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/source/ram_ns/hal_adc.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/source/ram_ns/hal_audio.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/source/ram_s/hal_efuse.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/source/ram_ns/hal_eth.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/source/ram/hal_gdma.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/source/ram/hal_gpio.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/source/ram_ns/hal_i2c.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/source/ram_ns/hal_i2s.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/source/ram_s/hal_icc.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/source/ram/hal_icc_app.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/source/ram/hal_misc.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/source/ram_ns/hal_pcm.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/source/ram_ns/hal_pwm.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/source/ram_ns/hal_sdio_host.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/source/ram_ns/hal_sgpio.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/source/ram_s/hal_spic.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/source/ram_ns/hal_ssi.c
SRC_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/source/ram/hal_uart.c

#utilities
#example
SRC_C += ../../../component/common/example/bcast/example_bcast.c
SRC_C += ../../../component/common/example/cJSON/example_cJSON.c
SRC_C += ../../../component/common/example/coap/example_coap.c
SRC_C += ../../../component/common/example/dct/example_dct.c
SRC_C += ../../../component/common/example/eap/example_eap.c
SRC_C += ../../../component/common/example/example_entry.c
SRC_C += ../../../component/common/example/fatfs/example_fatfs.c
SRC_C += ../../../component/common/example/std_file/example_std_file.c
SRC_C += ../../../component/common/example/sd_hot_plug/example_sd_hotplug.c
SRC_C += ../../../component/common/example/media_mp4_demuxer/example_media_mp4_demuxer.c
SRC_C += ../../../component/common/example/get_beacon_frame/example_get_beacon_frame.c
SRC_C += ../../../component/common/example/high_load_memory_use/example_high_load_memory_use.c
SRC_C += ../../../component/common/example/http_client/example_http_client.c
SRC_C += ../../../component/common/example/http_download/example_http_download.c
SRC_C += ../../../component/common/example/httpc/example_httpc.c
SRC_C += ../../../component/common/example/httpd/example_httpd.c
SRC_C += ../../../component/common/example/isp/example_isp_osd_multi.c
SRC_C += ../../../component/common/example/isp/example_md.c
SRC_C += ../../../component/common/example/mcast/example_mcast.c
SRC_C += ../../../component/common/example/mdns/example_mdns.c
SRC_C += ../../../component/common/example/media_framework/example_media_framework.c
SRC_C += ../../../component/common/example/media_h264_to_sdcard/example_media_h264_to_sdcard.c
SRC_C += ../../../component/common/example/media_uvcd/example_media_uvcd.c
SRC_C += ../../../component/common/example/mqtt/example_mqtt.c
#SRC_C += ../../../component/common/example/nonblock_connect/example_nonblock_connect.c
SRC_C += ../../../component/common/example/ota_sdcard/example_ota_sdcard.c
SRC_C += ../../../component/common/example/ota_http/example_ota_http.c
SRC_C += ../../../component/common/example/usb_dfu_ota/example_usb_dfu_ota.c
SRC_C += ../../../component/common/example/qr_code_scanner/example_qr_code_scanner.c
SRC_C += ../../../component/common/example/rarp/example_rarp.c
SRC_C += ../../../component/common/example/sdcard_upload_httpd/example_sdcard_upload_httpd.c
SRC_C += ../../../component/common/example/sntp_showtime/example_sntp_showtime.c
SRC_C += ../../../component/common/example/socket_select/example_socket_select.c
SRC_C += ../../../component/common/example/socket_tcp_trx/example_socket_tcp_trx_1.c
SRC_C += ../../../component/common/example/socket_tcp_trx/example_socket_tcp_trx_2.c
SRC_C += ../../../component/common/example/tcp_keepalive/example_tcp_keepalive.c
SRC_C += ../../../component/common/example/usb_mass_storage/example_usb_msc.c
SRC_C += ../../../component/common/example/wifi_mac_monitor/example_wifi_mac_monitor.c
SRC_C += ../../../component/common/example/wifi_roaming/example_wifi_roaming.c
SRC_C += ../../../component/common/example/wlan_fast_connect/example_wlan_fast_connect.c
##SRC_C += ../../../component/common/example/wowlan/example_wowlan.c
SRC_C += ../../../component/common/example/websocket_server/example_ws_server.c
SRC_C += ../../../component/common/example/websocket_client/example_wsclient.c
SRC_C += ../../../component/common/example/xml/example_xml.c
SRC_C += ../../../component/common/example/std_file/example_std_file.c
SRC_C += ../../../component/common/example/wlan_scenario/example_wlan_scenario.c
SRC_C += ../../../component/common/example/pppoe/example_pppoe.c
SRC_C += ../../../component/common/example/kvs_webrtc/Common.c
SRC_C += ../../../component/common/example/kvs_webrtc/example_kvs_webrtc.c
SRC_C += ../../../component/common/example/kvs_producer/kvs_producer.c
SRC_C += ../../../component/common/example/kvs_producer/example_kvs_producer.c
SRC_C += ../../../component/common/application/amazon/amazon-freertos-202012.00/vendors/realtek/boards/amebaPro/aws_demos/application_code/aws_main.c
SRC_C += ../../../component/common/example/amazon_freertos/example_amazon_freertos.c

##amazon_freertos_LTS - demos
#common
SRC_C += ../../../component/common/application/amazon/amazon-freertos-202012.00/demos/common/http_demo_helpers/http_demo_utils.c
SRC_C += ../../../component/common/application/amazon/amazon-freertos-202012.00/demos/common/mqtt_demo_helpers/mqtt_demo_helpers.c
SRC_C += ../../../component/common/application/amazon/amazon-freertos-202012.00/demos/common/pkcs11_helpers/pkcs11_helpers.c
#coreHTTP
SRC_C += ../../../component/common/application/amazon/amazon-freertos-202012.00/demos/coreHTTP/http_demo_mutual_auth.c
SRC_C += ../../../component/common/application/amazon/JPEG_snapshot_s3_upload_example/http_demo_s3_upload.c
#coreMQTT
SRC_C += ../../../component/common/application/amazon/amazon-freertos-202012.00/demos/coreMQTT/mqtt_demo_mutual_auth.c
#demo_runner
SRC_C += ../../../component/common/application/amazon/amazon-freertos-202012.00/demos/demo_runner/aws_demo.c
SRC_C += ../../../component/common/application/amazon/amazon-freertos-202012.00/demos/demo_runner/aws_demo_version.c
SRC_C += ../../../component/common/application/amazon/amazon-freertos-202012.00/demos/demo_runner/iot_demo_freertos.c
SRC_C += ../../../component/common/application/amazon/amazon-freertos-202012.00/demos/demo_runner/iot_demo_runner.c
#dev_mode_key_provisioning
SRC_C += ../../../component/common/application/amazon/amazon-freertos-202012.00/demos/dev_mode_key_provisioning/src/aws_dev_mode_key_provisioning.c
#device_shadow_for_aws
SRC_C += ../../../component/common/application/amazon/amazon-freertos-202012.00/demos/device_shadow_for_aws/shadow_demo_main.c
#network_manager
SRC_C += ../../../component/common/application/amazon/amazon-freertos-202012.00/demos/network_manager/aws_iot_demo_network.c
SRC_C += ../../../component/common/application/amazon/amazon-freertos-202012.00/demos/network_manager/aws_iot_network_manager.c
#ota
SRC_C += ../../../component/common/application/amazon/amazon-freertos-202012.00/demos/ota/aws_iot_ota_update_demo.c

##Object detection
SRC_C += ../src/obj_detect/skynet_device.c
SRC_C += ../src/obj_detect/skynet_wakeup.c
SRC_C += ../src/obj_detect/module_skynet.c
SRC_C += ../src/obj_detect/module_obj_detect.c
SRC_C += ../src/obj_detect/object_detection_init.c


#FatFs
#disk_if
SRC_C += ../../../component/common/file_system/fatfs/disk_if/src/sdcard.c
##SRC_C += ../../../component/common/drivers/sdio/realtek/sdio_host/src/sdio_combine.c
##Debug
SRC_C += ../../../component/common/file_system/fatfs/disk_if/src/usbdisk.c

#fatfs_ext
SRC_C += ../../../component/common/file_system/fatfs/fatfs_ext/src/ff_driver.c

#r0.10c
#option
#SRC_C += ../../../component/common/file_system/fatfs/r0.10c/src/option/ccsbcs.c
SRC_C += ../../../component/common/file_system/fatfs/r0.14/diskio.c
SRC_C += ../../../component/common/file_system/fatfs/r0.14/ff.c
SRC_C += ../../../component/common/file_system/fatfs/r0.14/ffsystem.c
SRC_C += ../../../component/common/file_system/fatfs/r0.14/ffunicode.c
SRC_C += ../../../component/common/file_system/fatfs/fatfs_flash_api.c
SRC_C += ../../../component/common/file_system/fatfs/fatfs_reent.c
SRC_C += ../../../component/common/file_system/fatfs/fatfs_sdcard_api.c
SRC_C += ../../../component/common/utilities/cJSON.c
SRC_C += ../../../component/common/utilities/http_client.c
SRC_C += ../../../component/common/utilities/xml.c

#user
#evalutaion_board
#sensor_board_v1
SRC_C += ../src/eval/sensor_board_v1/AL3042.c
SRC_C += ../src/eval/sensor_board_v1/ambient_light_sensor.c
SRC_C += ../src/eval/sensor_board_v1/ir_ctrl.c
SRC_C += ../src/eval/sensor_board_v1/ir_cut.c
SRC_C += ../src/eval/sensor_board_v1/sensor_external_ctrl.c

SRC_C += ../src/main.c
##SRC_CPP = ../src/test.cpp

#CINIT
# -------------------------------------------------------------------
#@CINIT
CINIT_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/source/ram/hal_timer.c
CINIT_C += ../../../component/os/freertos/freertos_v10.0.0/portable/MemMang/heap_4_2.c
CINIT_C += ../../../component/soc/realtek/8195b/misc/utilities/source/ram/libc_wrap.c
CINIT_C += ../../../project/realtek_amebapro_v0_example/src/isp_boot_config.c

#SRAM
# -------------------------------------------------------------------
#@SRAM
SRAM_C += ../../../component/common/mbed/targets/hal/rtl8195b/hal/rtl8195bh/flash_api.c
SRAM_C += ../../../component/soc/realtek/8195b/misc/driver/flash_api_ext.c
SRAM_C += ../../../component/common/file_system/fatfs/disk_if/src/flash_fatfs.c
SRAM_C += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/source/ram_s/hal_flash.c

#ERAM
# -------------------------------------------------------------------
#@ERAM
ERAM_C +=




# Generate obj list
# -------------------------------------------------------------------

ASM_O = $(patsubst %.S,%.o,$(SRC_ASM))
SRC_O = $(patsubst %.c,%.o,$(SRC_C))
CPP_O = $(patsubst %.cpp,%.o,$(SRC_CPP))
ERAM_O = $(patsubst %.c,%.o,$(ERAM_C))
SRAM_O = $(patsubst %.c,%.o,$(SRAM_C))
CINIT_O = $(patsubst %.c,%.o,$(CINIT_C))
ITCM_O = $(patsubst %.c,%.o,$(ITCM_C))
DTCM_O = $(patsubst %.c,%.o,$(DTCM_C))

DEPENDENCY_LIST = $(patsubst %.S,%.d,$(SRC_ASM))
DEPENDENCY_LIST += $(patsubst %.c,%.d,$(SRC_C))
DEPENDENCY_LIST += $(patsubst %.cpp,%.d,$(SRC_CPP))
DEPENDENCY_LIST += $(patsubst %.c,%.d,$(ERAM_C))
DEPENDENCY_LIST += $(patsubst %.c,%.d,$(SRAM_C))
DEPENDENCY_LIST += $(patsubst %.c,%.d,$(CINIT_C))
DEPENDENCY_LIST += $(patsubst %.c,%.d,$(ITCM_C))

SRC_C_LIST = $(notdir $(SRC_C)) $(notdir $(ERAM_C)) $(notdir $(SRAM_C)) $(notdir $(CINIT_C)) $(notdir $(ITCM_C))
OBJ_LIST = $(addprefix $(OBJ_DIR)/,$(patsubst %.c,%.o,$(SRC_C_LIST))) 
OBJ_LIST += $(addprefix $(OBJ_DIR)/,$(patsubst %.S,%.o,$(notdir $(SRC_ASM))))
OBJ_LIST += $(addprefix $(OBJ_DIR)/,$(patsubst %.cpp,%.o,$(notdir $(SRC_CPP))))


# Compile options
# -------------------------------------------------------------------

GCCFLAGS =
GCCFLAGS += -march=armv8-m.main+dsp -mthumb -mcmse -mfloat-abi=softfp -mfpu=fpv5-sp-d16 -g -gdwarf-3 -Os -c -MMD --save-temps
GCCFLAGS += -nostartfiles -nodefaultlibs -nostdlib -fstack-usage -fdata-sections -ffunction-sections -fno-common
#-fno-short-enums

# Define Macro
GCCFLAGS += -D__thumb2__ -DCONFIG_PLATFORM_8195B -DCONFIG_PLATFORM_8195BHP -D__FPU_PRESENT -D__ARM_ARCH_7M__=0 -D__ARM_ARCH_7EM__=0 -D__ARM_ARCH_8M_MAIN__=1 -D__ARM_ARCH_8M_BASE__=0 
GCCFLAGS += -DCONFIG_BUILD_RAM=1 -DCONFIG_BUILD_LIB=1
GCCFLAGS += -DV8M_STKOVF -DARM_MATH_CM7 -DCONFIG_USBD -DCONFIG_FATFS_WRAPPER=1

CFLAGS = $(GCCFLAGS)
CFLAGS += -Wall -Wpointer-arith -Wstrict-prototypes -Wundef -Wno-write-strings -Wno-maybe-uninitialized

CPPFLAGS = $(GCCFLAGS)
CPPFLAGS += -std=c++11 -fno-use-cxa-atexit
CPPFLAGS += -Wall -Wpointer-arith -Wundef -Wno-write-strings -Wno-maybe-uninitialized

LFLAGS = 
LFLAGS += -march=armv8-m.main+dsp -mthumb -mcmse -mfloat-abi=softfp -mfpu=fpv5-sp-d16 -Os -nostartfiles -specs=nosys.specs -nodefaultlibs -nostdlib
LFLAGS += -Wl,--gc-sections -Wl,-Map=$(BIN_DIR)/$(TARGET).map -Wl,--cref -Wl,--build-id=none -Wl,--use-blx 
##noisy warning option
##LFLAGS += -Wl,--warn-section-align
# libc api wrapper
LFLAGS += -Wl,-wrap,strcat  -Wl,-wrap,strchr   -Wl,-wrap,strcmp
LFLAGS += -Wl,-wrap,strncmp -Wl,-wrap,strnicmp -Wl,-wrap,strcpy
LFLAGS += -Wl,-wrap,strncpy -Wl,-wrap,strlcpy  -Wl,-wrap,strlen
LFLAGS += -Wl,-wrap,strnlen -Wl,-wrap,strncat  -Wl,-wrap,strpbrk
LFLAGS += -Wl,-wrap,strspn  -Wl,-wrap,strstr   -Wl,-wrap,strtok
LFLAGS += -Wl,-wrap,strxfrm -Wl,-wrap,strsep   -Wl,-wrap,strtod
LFLAGS += -Wl,-wrap,strtof  -Wl,-wrap,strtold  -Wl,-wrap,strtoll
LFLAGS += -Wl,-wrap,strtoul -Wl,-wrap,strtoull -Wl,-wrap,atoi
LFLAGS += -Wl,-wrap,atoui   -Wl,-wrap,atol     -Wl,-wrap,atoul
LFLAGS += -Wl,-wrap,atoull  -Wl,-wrap,atof
LFLAGS += -Wl,-wrap,malloc  -Wl,-wrap,realloc  -Wl,-wrap,free
LFLAGS += -Wl,-wrap,calloc
LFLAGS += -Wl,-wrap,memcmp  -Wl,-wrap,memcpy
LFLAGS += -Wl,-wrap,memmove -Wl,-wrap,memset
LFLAGS += -Wl,-wrap,printf
# LFLAGS += -Wl,-wrap,sprintf
# LFLAGS += -Wl,-wrap,snprintf  -Wl,-wrap,vsnprintf  
LFLAGS += -Wl,-wrap,vprintf
LFLAGS += -Wl,-wrap,abort
LFLAGS += -Wl,-wrap,puts
LFLAGS += -Wl,-wrap,fopen     -Wl,-wrap,fclose
LFLAGS += -Wl,-wrap,fread     -Wl,-wrap,fwrite
LFLAGS += -Wl,-wrap,fseek     -Wl,-wrap,fflush
LFLAGS += -Wl,-wrap,rename    -Wl,-wrap,feof
LFLAGS += -Wl,-wrap,ferror    -Wl,-wrap,ftell
LFLAGS += -Wl,-wrap,fputc     -Wl,-wrap,fputs
LFLAGS += -Wl,-wrap,fgets     -Wl,-wrap,remove
LFLAGS += -Wl,-wrap,opendir   -Wl,-wrap,readdir
LFLAGS += -Wl,-wrap,closedir  -Wl,-wrap,scandir
LFLAGS += -Wl,-wrap,rmdir     -Wl,-wrap,mkdir
LFLAGS += -Wl,-wrap,access    -Wl,-wrap,stat


LIBFLAGS =
LIBFLAGS += ../../../component/soc/realtek/8195b/fwlib/hal-rtl8195b-hp/lib/lib/hal_pmc_hs.a
LIBFLAGS += -L../../../component/soc/realtek/8195b/misc/bsp/lib/common/GCC/
all: LIBFLAGS += -l_codec -l_dct -l_faac -l_h264 -l_haac -l_http -l_mmf -l_muxer -l_p2p -l_rtsp -l_sdcard -l_soc_is -l_speex -l_usbd -l_wlan -l_wps -l_qr_code -l_mdns -l_tftp
mp: LIBFLAGS += -l_codec -l_dct -l_faac -l_h264 -l_haac -l_http -l_mmf -l_muxer -l_p2p -l_rtsp -l_sdcard -l_soc_is -l_speex -l_usbd -l_wlan_mp -l_wps -l_qr_code -l_mdns -l_tftp
all: LIBFLAGS += -lrtstream -lrtscamkit -lrtsv4l2 -lrtsisp -lrtsosd -l_kvs_webrtc -l_webrtc_producer_c -l_webrtc_pic -lsrtp2 -lwebsockets -l_kvs_producer -l_opus -l_opusenc -l_opusfile -l_amazon_LTS
LIBFLAGS += ../src/obj_detect/GCC/libSkynetAPI_iotD.a
LIBFLAGS += ../src/obj_detect/GCC/lib_obj_detect.a

LIBFLAGS += -Wl,-u,ram_start -Wl,-u,cinit_start


LIBFLAGS += -lm -lc -lnosys -lgcc -lstdc++

# Sensor
include sensor.mk

# Prebuild
# -------------------------------------------------------------------
	
.PHONY: prebuild
prebuild:	
	@echo ===========================================================
	@echo Prebuild
	@echo ===========================================================
ifeq ($(findstring Linux, $(OS)), Linux)
	chmod 0774 ../../../component/soc/realtek/8195b/misc/iar_utility/elf2bin.linux
	chmod 0774 ../../../component/soc/realtek/8195b/misc/iar_utility/checksum.linux
	chmod 0774 ../../../component/soc/realtek/8195b/misc/gcc_utility/postbuild.sh
endif
	$(ELF2BIN) prebuild GCC xip_fw.ld FW


# Compile
# -------------------------------------------------------------------

.PHONY: application
application: prerequirement $(SRC_O) $(ERAM_O) $(SRAM_O) $(CINIT_O) $(ASM_O) $(ITCM_O) $(CPP_O)
	$(LD) $(LFLAGS) -o $(BIN_DIR)/$(TARGET).axf  $(OBJ_LIST) $(ROMIMG) $(LIBFLAGS) -T$(LDSCRIPT)
	$(OBJDUMP) -d $(BIN_DIR)/$(TARGET).axf > $(BIN_DIR)/$(TARGET).asm


# Manipulate Image
# -------------------------------------------------------------------
	
.PHONY: manipulate_images
manipulate_images:	| application
	@echo ===========================================================
	@echo Image manipulating
	@echo ===========================================================
	cp  ../../../component/soc/realtek/8195b/misc/bsp/image/boot.bin application_is/boot.bin
	$(ELF2BIN) keygen keycfg.json
	$(ELF2BIN) convert amebapro_bootloader.json PARTITIONTABLE
	$(ELF2BIN) convert amebapro_firmware_is.json FIRMWARE
	$(ELF2BIN) combine application_is/flash_is.bin PTAB=partition.bin,BOOT=application_is/boot.bin,FW1=application_is/firmware_is.bin
	$(CHKSUM) application_is/firmware_is.bin
	$(FLASH_TOOLDIR)/postbuild.sh $(ELF2BIN)
	

# Generate build info
# -------------------------------------------------------------------	

.PHONY: build_info
build_info:
	@echo \#define RTL_FW_COMPILE_TIME RTL8195BFW_COMPILE_TIME\ > .ver
	@echo \#define RTL_FW_COMPILE_DATE RTL8195BFW_COMPILE_DATE\ >> .ver
	@echo \#define UTS_VERSION \"`date +%Y/%m/%d-%T`\" >> .ver
	@echo \#define RTL8195BFW_COMPILE_TIME \"`date +%Y/%m/%d-%T`\" >> .ver
	@echo \#define RTL8195BFW_COMPILE_DATE \"`date +%Y%m%d`\" >> .ver
	@echo \#define RTL8195BFW_COMPILE_BY \"`id -u -n`\" >> .ver
	@echo \#define RTL8195BFW_COMPILE_HOST \"`$(HOSTNAME_APP)`\" >> .ver
	@if [ -x /bin/dnsdomainname ]; then \
		echo \#define RTL8195BFW_COMPILE_DOMAIN \"`dnsdomainname`\"; \
	elif [ -x /bin/domainname ]; then \
		echo \#define RTL8195BFW_COMPILE_DOMAIN \"`domainname`\"; \
	else \
		echo \#define RTL8195BFW_COMPILE_DOMAIN ; \
	fi >> .ver

	@echo \#define RTL8195BFW_COMPILER \"gcc `$(CC) $(CFLAGS) -dumpversion | tr --delete '\r'`\" >> .ver
	@mv -f .ver ../inc/$@.h

.PHONY: prerequirement
prerequirement:
	@echo ===========================================================
	@echo Build $(TARGET)
	@echo ===========================================================
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)
	mkdir -p $(INFO_DIR)
	
$(ASM_O): %.o : %.S
	#$(AS) -march=armv8-m.main+dsp -mthumb -mfloat-abi=softfp -mfpu=fpv5-sp-d16 -g $< -o $@
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	cp $@ $(OBJ_DIR)/$(notdir $@)
	mv $(notdir $*.s) $(INFO_DIR)
	chmod 777 $(OBJ_DIR)/$(notdir $@)

$(CPP_O): %.o : %.cpp
	$(CC) $(CPPFLAGS) $(INCLUDES) -c $< -o $@
	cp $@ $(OBJ_DIR)/$(notdir $@)
	mv $(notdir $*.i) $(INFO_DIR)
	mv $(notdir $*.s) $(INFO_DIR)
	chmod 777 $(OBJ_DIR)/$(notdir $@)

$(SRC_O): %.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	#$(CC) $(CFLAGS) $(INCLUDES) -c $< -MM -MT $@ -MF $(OBJ_DIR)/$(notdir $(patsubst %.o,%.d,$@))
	cp $@ $(OBJ_DIR)/$(notdir $@)
	mv $(notdir $*.i) $(INFO_DIR)
	mv $(notdir $*.s) $(INFO_DIR)
	chmod 777 $(OBJ_DIR)/$(notdir $@)

$(SRAM_O): %.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(OBJCOPY) --prefix-alloc-sections .sram $@
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -MM -MT $@ -MF $(OBJ_DIR)/$(notdir $(patsubst %.o,%.d,$@))
	cp $@ $(OBJ_DIR)/$(notdir $@)
	mv $(notdir $*.i) $(INFO_DIR)
	mv $(notdir $*.s) $(INFO_DIR)
	chmod 777 $(OBJ_DIR)/$(notdir $@)

$(ERAM_O): %.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(OBJCOPY) --prefix-alloc-sections .eram $@
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -MM -MT $@ -MF $(OBJ_DIR)/$(notdir $(patsubst %.o,%.d,$@))
	cp $@ $(OBJ_DIR)/$(notdir $@)
	mv $(notdir $*.i) $(INFO_DIR)
	mv $(notdir $*.s) $(INFO_DIR)
	chmod 777 $(OBJ_DIR)/$(notdir $@)

$(CINIT_O): %.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(OBJCOPY) --prefix-alloc-sections .cinit $@
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -MM -MT $@ -MF $(OBJ_DIR)/$(notdir $(patsubst %.o,%.d,$@))
	cp $@ $(OBJ_DIR)/$(notdir $@)
	mv $(notdir $*.i) $(INFO_DIR)
	mv $(notdir $*.s) $(INFO_DIR)
	chmod 777 $(OBJ_DIR)/$(notdir $@)	

$(ITCM_O): %.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(OBJCOPY) --prefix-alloc-sections .itcm $@
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -MM -MT $@ -MF $(OBJ_DIR)/$(notdir $(patsubst %.o,%.d,$@))
	cp $@ $(OBJ_DIR)/$(notdir $@)
	mv $(notdir $*.i) $(INFO_DIR)
	mv $(notdir $*.s) $(INFO_DIR)
	chmod 777 $(OBJ_DIR)/$(notdir $@)

$(DTCM_O): %.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(OBJCOPY) --prefix-alloc-sections .dtcm $@
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -MM -MT $@ -MF $(OBJ_DIR)/$(notdir $(patsubst %.o,%.d,$@))
	cp $@ $(OBJ_DIR)/$(notdir $@)
	mv $(notdir $*.i) $(INFO_DIR)
	mv $(notdir $*.s) $(INFO_DIR)
	chmod 777 $(OBJ_DIR)/$(notdir $@)

-include $(DEPENDENCY_LIST)

# Generate build info
# -------------------------------------------------------------------	
#ifeq (setup,$(firstword $(MAKECMDGOALS)))
#  # use the rest as arguments for "run"
#  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
#  # ...and turn them into do-nothing targets
#  $(eval $(RUN_ARGS):;@:)
#endif

.PHONY: setup
setup:
	@echo "----------------"
	@echo Setup $(GDB_SERVER)
	@echo "----------------"
ifeq ($(GDB_SERVER), openocd)
	cp -p $(FLASH_TOOLDIR)/rtl_gdb_debug_openocd.txt $(FLASH_TOOLDIR)/rtl_gdb_debug.txt
#	cp -p $(FLASH_TOOLDIR)/rtl_gdb_ramdebug_openocd.txt $(FLASH_TOOLDIR)/rtl_gdb_ramdebug.txt
#	cp -p $(FLASH_TOOLDIR)/rtl_gdb_flash_write_openocd.txt $(FLASH_TOOLDIR)/rtl_gdb_flash_write.txt
else
	cp -p $(FLASH_TOOLDIR)/rtl_gdb_debug_jlink.txt $(FLASH_TOOLDIR)/rtl_gdb_debug.txt
#	cp -p $(FLASH_TOOLDIR)/rtl_gdb_ramdebug_jlink.txt $(FLASH_TOOLDIR)/rtl_gdb_ramdebug.txt
#	cp -p $(FLASH_TOOLDIR)/rtl_gdb_flash_write_jlink.txt $(FLASH_TOOLDIR)/rtl_gdb_flash_write.txt
endif

.PHONY: flashburn
flashburn:
#	@if [ ! -f $(FLASH_TOOLDIR)/rtl_gdb_flash_write.txt ] ; then echo Please do /"make setup GDB_SERVER=[jlink or openocd]/" first; echo && false ; fi
#ifeq ($(findstring CYGWIN, $(OS)), CYGWIN) 
#	$(FLASH_TOOLDIR)/Check_Jtag.sh
#endif
	chmod +rx $(FLASH_TOOLDIR)/flashloader.sh
	$(FLASH_TOOLDIR)/flashloader.sh
	$(GDB) -x $(FLASH_TOOLDIR)/rtl_gdb_flashloader_jlink.txt
	
.PHONY: debug
debug:
#	@if [ ! -f $(FLASH_TOOLDIR)/rtl_gdb_debug.txt ] ; then echo Please do /"make setup GDB_SERVER=[jlink or openocd]/" first; echo && false ; fi

	chmod +rx $(FLASH_TOOLDIR)/debug.sh
	$(FLASH_TOOLDIR)/debug.sh $(BIN_DIR)/$(TARGET).axf
	$(GDB) -x $(FLASH_TOOLDIR)/rtl_gdb_debug_jlink.txt


.PHONY: clean
clean:
	rm -rf $(TARGET)
	rm -f $(patsubst %.o,%.d,$(SRC_O)) $(patsubst %.o,%.d,$(ERAM_O)) $(patsubst %.o,%.d,$(SRAM_O))
	rm -f $(patsubst %.o,%.d,$(CINIT_O)) $(patsubst %.o,%.d,$(ITCM_O)) $(patsubst %.o,%.d,$(DTCM_O))
	rm -f $(patsubst %.o,%.d,$(ASM_O)) $(patsubst %.o,%.d,$(CPP_O))
	rm -f $(patsubst %.o,%.su,$(SRC_O)) $(patsubst %.o,%.su,$(ERAM_O)) $(patsubst %.o,%.su,$(SRAM_O))
	rm -f $(patsubst %.o,%.su,$(CINIT_O)) $(patsubst %.o,%.su,$(ITCM_O)) $(patsubst %.o,%.su,$(DTCM_O))
	rm -f $(patsubst %.o,%.su,$(ASM_O)) $(patsubst %.o,%.su,$(CPP_O))
	rm -f $(SRC_O) $(ERAM_O) $(SRAM_O) $(CINIT_O) $(ITCM_O) $(ASM_O) $(CPP_O) $(DTCM_O)
	rm -f *.i
	rm -f *.s

