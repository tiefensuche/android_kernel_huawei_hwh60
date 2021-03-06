#
# Makefile for DWC_otg Highspeed USB controller driver
#

ifneq ($(KERNELRELEASE),)

# Use the BUS_INTERFACE variable to compile the software for either 
# PCI(PCI_INTERFACE) or LM(LM_INTERFACE) bus.
ifeq ($(BUS_INTERFACE),)
#	BUS_INTERFACE = -DPCI_INTERFACE
	BUS_INTERFACE = -DLM_INTERFACE
endif

#EXTRA_CFLAGS	+= -DDEBUG 

COMMONLIB         := $(shell pwd)/drivers/usb/dwc_common_port/
# Use one of the following flags to compile the software in host-only or
# device-only mode.
EXTRA_CFLAGS        += -DDWC_HOST_ONLY
#EXTRA_CFLAGS        += -DDWC_DEVICE_ONLY

EXTRA_CFLAGS	+= -Dlinux -DDWC_HS_ELECT_TST
#EXTRA_CFLAGS	+= -DDWC_EN_ISOC
EXTRA_CFLAGS   	+= -I$(PWD)/drivers/usb/dwc_common_port
EXTRA_CFLAGS   	+= -I$(COMMONLIB)
EXTRA_CFLAGS   	+= -DDWC_LINUX
EXTRA_CFLAGS   	+= $(CFI)
EXTRA_CFLAGS	+= $(BUS_INTERFACE)
#EXTRA_CFLAGS	+= -DDWC_DEV_SRPCAP

obj-y	:= dwc_otg.o

dwc_otg-objs	:= dwc_otg_driver.o dwc_otg_attr.o 
dwc_otg-objs	+= dwc_otg_cil.o dwc_otg_cil_intr.o 
dwc_otg-objs	+= dwc_otg_pcd_linux.o dwc_otg_pcd.o dwc_otg_pcd_intr.o 
dwc_otg-objs	+= dwc_otg_hcd.o dwc_otg_hcd_linux.o dwc_otg_hcd_intr.o dwc_otg_hcd_queue.o dwc_otg_hcd_ddma.o
dwc_otg-objs	+= dwc_otg_adp.o
ifneq ($(CFI),)
dwc_otg-objs	+= dwc_otg_cfi.o
endif
ifeq ($(strip $(CFG_FEATURE_BCM_VERSION)),43239)
dwc_otg-objs	+= dwc_otg_balong.o
endif
else

PWD		:= $(shell pwd)
PORTLIB		:= $(PWD)/../dwc_common_port

# Command paths
CTAGS		:= $(CTAGS)
DOXYGEN		:= $(DOXYGEN)

default: portlib
	$(MAKE) -C$(KDIR) M=$(PWD) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules
	
install: default
	$(MAKE) -C$(KDIR) M=$(PORTLIB) modules_install
	$(MAKE) -C$(KDIR) M=$(PWD) modules_install	

portlib:
	$(MAKE) -C$(KDIR) M=$(PORTLIB) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) modules
	cp $(PORTLIB)/Module.symvers $(PWD)/
	
docs:	$(wildcard *.[hc]) doc/doxygen.cfg
	$(DOXYGEN) doc/doxygen.cfg

tags:	$(wildcard *.[hc])
	$(CTAGS) -e $(wildcard *.[hc]) $(wildcard linux/*.[hc]) $(wildcard $(KDIR)/include/linux/usb*.h)


clean:
	rm -rf   *.o *.ko .*cmd *.mod.c .tmp_versions Module.symvers

endif
