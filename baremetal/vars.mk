ldscript-$(CONFIG_BAREMETAL_LINKER_SCRIPT) += baremetal.lds

obj-$(CONFIG_BAREMETAL_ENTRY) += entry.o
obj-$(CONFIG_BAREMETAL_STARTUP) += startup.o

# Support code
obj-y += cache.o
obj-y += clocking.o
obj-y += crc32.o
obj-$(CONFIG_BAREMETAL_EXCEPTION) += exception.o
obj-$(CONFIG_BAREMETAL_MMU) += mmu.o
obj-$(CONFIG_BAREMETAL_NEWLIB) += newlib_stubs.o
obj-y += util.o

subdir-y += driver
subdir-$(CONFIG_BAREMETAL_FREERTOS) += freertos
