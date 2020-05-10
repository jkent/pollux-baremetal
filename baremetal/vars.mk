ldscript-$(CONFIG_BAREMETAL_LINKER_SCRIPT) += baremetal.lds

obj-$(CONFIG_BAREMETAL_ENTRY) += entry.o
obj-$(CONFIG_BAREMETAL_EARLY) += early.o
obj-$(CONFIG_BAREMETAL_STARTUP) += startup.o

# Support code
obj-y += cache.o
obj-y += clocking.o
obj-y += crc32.o
obj-y += interrupt.o
obj-y += mmu.o mmu.arm.o
obj-y += newlib_stubs.o
obj-y += util.o

subdir-y += driver
