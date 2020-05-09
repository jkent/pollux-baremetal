ldscript-$(CONFIG_BAREMETAL_USE_LINKER_SCRIPT) += baremetal.lds

obj-$(CONFIG_BAREMETAL_USE_ENTRY) += entry.o
obj-$(CONFIG_BAREMETAL_USE_EARLY) += early.o
obj-$(CONFIG_BAREMETAL_USE_STARTUP) += startup.o

# Support code
subdir-y += driver
obj-y += cache.o
obj-y += clocking.o
obj-y += crc32.o
obj-y += interrupt.o
obj-y += mmu.o mmu.arm.o
obj-y += util.o
