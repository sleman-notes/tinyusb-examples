CC=arm-none-eabi-gcc
TARGET=flash
APP ?= main

MACH=-mcpu=cortex-m4
FLOAT=-mfloat-abi=soft

BUILD_DIR = Build
TINYUSB_DIR = lib/tinyusb/src

PORT ?= /dev/ttyUSB0
BAUD ?= 115200

LINKER= -T drivers/Device/linkers/STM32F411.ld
MAP_FILE= -Wl,-Map=$(BUILD_DIR)/$(TARGET).map

CFLAGS= -c $(MACH) -mthumb $(FLOAT) -DSTM32F411xE -DCFG_TUSB_MCU=OPT_MCU_STM32F4 \
			-std=gnu99 -Wall -O0 -g3 \
			--specs=nano.specs -ffunction-sections -fdata-sections

LDFLAGS = $(MACH) -mthumb $(FLOAT) --specs=nosys.specs $(LINKER) $(MAP_FILE) -g3 \
			-Wl,--gc-sections -static --specs=nano.specs -Wl,--start-group -lc -lm \
			-Wl,--end-group -Wl,--print-memory-usage

OBJCOPY=arm-none-eabi-objcopy

###########################################
#				 INCLUDES
###########################################

INCLUDES+= -I app/Inc
INCLUDES+= -I drivers/Inc
INCLUDES+= -I drivers/Device/cmsis
INCLUDES+= -I $(TINYUSB_DIR)


############################################
# 				SOURCE FILES
############################################

OBJS		+= $(BUILD_DIR)/$(APP).o
OBJS		+= $(BUILD_DIR)/config.o
OBJS		+= $(BUILD_DIR)/startup.o
OBJS		+= $(BUILD_DIR)/syscalls.o
OBJS		+= $(BUILD_DIR)/system_stm32f4xx.o

DRIVERS		+= $(BUILD_DIR)/driver_clock.o
DRIVERS		+= $(BUILD_DIR)/driver_systick.o
DRIVERS		+= $(BUILD_DIR)/driver_gpio.o
DRIVERS		+= $(BUILD_DIR)/driver_uart.o
DRIVERS		+= $(BUILD_DIR)/driver_interrupt.o

TINYUSB     += $(BUILD_DIR)/tusb.o
TINYUSB     += $(BUILD_DIR)/tusb_fifo.o
TINYUSB     += $(BUILD_DIR)/usbd.o
TINYUSB     += $(BUILD_DIR)/cdc_device.o
TINYUSB     += $(BUILD_DIR)/dcd_dwc2.o
TINYUSB     += $(BUILD_DIR)/dwc2_common.o


PREREQ = $(BUILD_DIR)

all: $(PREREQ) $(BUILD_DIR)/$(TARGET).elf

$(PREREQ):
	mkdir -p $(PREREQ)

$(BUILD_DIR)/%.o: app/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o app/Src/$(*).c

$(BUILD_DIR)/%.o: drivers/Src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o drivers/Src/$(*).c

$(BUILD_DIR)/%.o: drivers/Device/startup/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o drivers/Device/startup/$(*).c

$(BUILD_DIR)/%.o: drivers/Device/system/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o drivers/Device/system/$(*).c

$(BUILD_DIR)/%.o: $(TINYUSB_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o $(TINYUSB_DIR)/$(*).c

$(BUILD_DIR)/%.o: $(TINYUSB_DIR)/common/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o $(TINYUSB_DIR)/common/$(*).c

$(BUILD_DIR)/%.o: $(TINYUSB_DIR)/device/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o $(TINYUSB_DIR)/device/$(*).c

$(BUILD_DIR)/%.o: $(TINYUSB_DIR)/class/cdc/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o $(TINYUSB_DIR)/class/cdc/$(*).c

$(BUILD_DIR)/%.o: $(TINYUSB_DIR)/portable/synopsys/dwc2/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(*).o $(TINYUSB_DIR)/portable/synopsys/dwc2/$(*).c

# TARGET ELF
$(BUILD_DIR)/$(TARGET).elf: $(OBJS) $(DRIVERS) $(TINYUSB)
	$(CC) $(LDFLAGS) -o $@ $^
	$(OBJCOPY) -O binary $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).bin
	arm-none-eabi-size $(BUILD_DIR)/$(TARGET).elf

load:
	jlink flash.jlink

monitor:
	picocom -b $(BAUD) $(PORT)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all load monitor clean
