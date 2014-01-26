TOOLCHAIN_PATH = /opt/arm/gcc-arm-none-eabi-4_7-2013q3/bin/

# List all source files the application uses.
APPLICATION_SRCS = $(notdir $(wildcard ./*.c))  nrf_delay.c softdevice_handler.c ble_advdata.c

# Use shell to find name of root folder. Possible but horrible to do in make.
PROJECT_NAME = $(shell basename "$(realpath ../)")

DEVICE = NRF51
BOARD = SELF_BOARD
# BOARD = BOARD_PCA10000
#SEGGER_SERIAL = 

SDK_PATH = $(HOME)/Workspace/SDK/nrf51_sdk_v5_1_0_36092/nrf51822/
SOFTDEVICE_PATH = $(HOME)/Workspace/SDK/s110_nrf51822_6.0.0/
TEMPLATE_PATH = ../nrf51-pure-gcc-setup/template/

USE_SOFTDEVICE = S110
SOFTDEVICE = $(SOFTDEVICE_PATH)s110_nrf51822_6.0.0_softdevice.hex

CFLAGS = -Os

GDB_PORT_NUMBER = 2331

include $(TEMPLATE_PATH)Makefile
