# Makefile for building the custom driver

# Name of the kernel module
obj-m += my_custom_driver.o

# Object files for the kernel module
my_custom_driver-objs := src/driver.o src/device.o src/utils.o

# Specify the kernel build directory
KERNELDIR ?= /lib/modules/$(shell uname -r)/build

# Build target
all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

# Clean target
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
