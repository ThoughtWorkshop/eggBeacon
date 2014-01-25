TOOLCHAIN_PATH = /opt/arm/gcc-arm-none-eabi-4_7-2013q3/bin/

# List all source files the application uses.
APPLICATION_SRCS = $(notdir $(wildcard ./*.c))  nrf_delay.c

# Use shell to find name of root folder. Possible but horrible to do in make.
PROJECT_NAME = $(shell basename "$(realpath ../)")

DEVICE = NRF51
BOARD = BOARD_PCA10000
#SEGGER_SERIAL = 

USE_SOFTDEVICE = S110

SDK_PATH = ../nrf51_sdk_v5_1_0_36092/nrf51822/
TEMPLATE_PATH = ../nrf51-pure-gcc-setup/template/

CFLAGS = -Os

GDB_PORT_NUMBER = 2331

include $(TEMPLATE_PATH)Makefile
