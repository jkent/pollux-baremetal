ldscript-$(CONFIG_BAREMETAL_USE_LINKER_SCRIPT) += baremetal.lds

obj-$(CONFIG_BAREMETAL_USE_ENTRY_CODE) += entry.o
ifdef CONFIG_BAREMETAL_USE_STARTUP_CODE
obj-$(CONFIG_BAREMETAL_BOOT_SOURCE_RAM) += ram-startup.o
obj-$(CONFIG_BAREMETAL_BOOT_SOURCE_UART) += uart-startup.o
endif
ifdef CONFIG_BAREMETAL_USE_RUNTIME_CODE
obj-$(CONFIG_BAREMETAL_USE_RUNTIME_CODE) += runtime.o
endif

# Support code
subdir-y += driver
obj-y += cache.arm.o
obj-y += clocking.o
obj-y += crc32.o
obj-y += mmu.o mmu.arm.o
obj-y += util.o
