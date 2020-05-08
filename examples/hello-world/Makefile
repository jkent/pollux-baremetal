ifndef BAREMETAL_PATH
$(error Not in a baremetal enabled shell)
endif
include $(BAREMETAL_PATH)/tools/make/rules.mk

target := hello-world.bin

obj-y += main.o

.PHONY: run
run: $(BUILD)/$(target)
	bootstrap.py $<