obj-y += port.o
obj-y += portasm.o

ifeq ($(CONFIG_BAREMETAL_NEWLIB),)
	obj-y += ../../freertos/portable/MemMang/heap_1.o
else
	obj-y += newlib_heap.o
endif

include-y += .
