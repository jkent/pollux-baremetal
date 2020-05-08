subdir-y += driver
obj-y += crc32.o
ifndef CONFIG_BAREMETAL_CUSTOM_ENTRY
obj-y += entry.o
endif
obj-y += ram.o
ifndef CONFIG_BAREMETAL_CUSTOM_STARTUP
obj-$(CONFIG_BAREMETAL_BOOT_SOURCE_UART) += uart-startup.o
obj-$(CONFIG_BAREMETAL_BOOT_SOURCE_RAM) += ram-startup.o
endif