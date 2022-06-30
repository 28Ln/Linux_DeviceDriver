obj-m += test.o
KBUILD_EXTRA_SYMBOLS += /home/leon/Desktop/Project_2022/Linux_DeviceDriver/2rd初探linux内核模块helloworld/6th/core/Module.symvers
KVER = $(shell uname -r)
KDIR = /lib/modules/$(KVER)/build
all:
	make -C $(KDIR) M=`pwd` modules
clean:
	make -C $(KDIR) M=`pwd` modules clean
	rm -f modules.order

