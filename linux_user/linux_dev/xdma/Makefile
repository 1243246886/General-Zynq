obj-m += xdma.o

# Path to the Linux kernel, if not passed in as arg, set default.
#ifeq ($(KDIR),)
KDIR := /root/work/linux-xlnx
#endif


all:
	make -C $(KDIR) M=$(PWD) modules ARCH=arm

clean:
	make -C $(KDIR) M=$(PWD) clean
