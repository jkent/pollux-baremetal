obj-y += port.o
obj-y += portISR.o

ifeq ($(CONFIG_BAREMETAL_NEWLIB),)
	obj-y += ../../freertos/portable/MemMang/heap_1.o
else
	obj-y += heap.o
endif

include-y += .
