obj-m += test.o
KVER = $(shell uname -r)
KDIR = /lib/modules/$(KVER)/build
all:
	make -C $(KDIR) M=`pwd` modules
clean:
	make -C $(KDIR) M=`pwd` modules clean
	rm -f modules.order

