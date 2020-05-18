subdir-y += baremetal
include-y += include

include-$(CONFIG_BAREMETAL_FREERTOS) += freertos/include
obj-$(CONFIG_BAREMETAL_FREERTOS) += freertos/croutine.o \
	freertos/event_groups.o freertos/list.o freertos/queue.o \
	freertos/stream_buffer.o freertos/tasks.o freertos/timers.o
#cflags-$(CONFIG_BAREMETAL_FREERTOS) += -DTHUMB_INTERWORK
