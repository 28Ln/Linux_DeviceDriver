obj-m += test_haha.o
test_haha-objs += haha.o test.o
KVER = $(shell uname -r)
KDIR = /lib/modules/$(KVER)/build
all:
	make -C $(KDIR) M=`pwd` modules
clean:
	make -C $(KDIR) M=`pwd` modules clean
	rm -f modules.order

