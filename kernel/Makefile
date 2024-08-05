# Makefile for building the custom kernel

KERNELDIR := $(PWD)
KERNEL_CONFIG := $(KERNELDIR)/config

all:
    $(MAKE) -C $(KERNELDIR) ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- O=$(KERNELDIR) zImage
    $(MAKE) -C $(KERNELDIR) ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- O=$(KERNELDIR) modules

clean:
    $(MAKE) -C $(KERNELDIR) ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- O=$(KERNELDIR) clean
