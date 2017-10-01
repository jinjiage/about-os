obj-m := yejinlei-fs.o  
MAKE := make
KERNELDIR := /usr/src/linux-headers-$(shell uname -r)  
PWD := $(shell pwd)  
modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
modules_install:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules_install
