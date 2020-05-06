#
#  Copyright (C) 2013-2020 Jeff Kent <jeff@jkent.net>
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License version 2 as
#  published by the Free Software Foundation.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#

# default rule
.PHONY: all
all:

BASEDIR ?= $(patsubst %/,%,$(dir $(firstword $(MAKEFILE_LIST))))
BUILD := $(BASEDIR)/build
-include $(BASEDIR)/.config

CROSS_COMPILE := arm-none-eabi-

AS      := $(CROSS_COMPILE)as
LD      := $(CROSS_COMPILE)ld
CC      := $(CROSS_COMPILE)gcc
CXX     := $(CROSS_COMPILE)g++
CPP     := $(CC) -E
AR      := $(CROSS_COMPILE)ar
NM      := $(CROSS_COMPILE)nm
STRIP   := $(CROSS_COMPILE)strip
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump
SIZE    := $(CROSS_COMPILE)size

CFLAGS   = -std=gnu99 -Wall -fms-extensions $(cflags-y)
ASFLAGS := -Wa,--defsym,_entry=$(CONFIG_)
LDFLAGS := -Wl,-M,-Map,$(BUILD)/$(basename $(target)).map
LIBS     = -lgcc $(libs-y)
INCLUDE  = --include $(BUILD)/config.h $(addprefix -I$(BASEDIR)/,$(BUILD) $(includes))

cflags-y += -mlittle-endian -msoft-float -mtune=arm9tdmi -march=armv5te -mthumb -mthumb-interwork -nostartfiles
ldscript-y := baremetal/baremetal.lds

ifdef CONFIG_DEBUG
  cflags-y += -O0 -g3 -DDEBUG
else
  cflags-y += -Os
endif

ifeq ($(V),1)
  D := @true
  Q :=
else
  D := @echo
  Q := @
endif

includes :=
objs :=
define collect_baremetal
  include-y :=
  subdir-y :=
  obj-y :=
  relative := $(shell realpath --relative-to $(BAREMETAL_PATH) $(1))
  include $(1)/Makefile
  includes := $$(includes) $$(addprefix $(1)/,$$(include-y))
  objs := $$(objs) $$(addprefix $(BUILD)/$$(relative)/,$$(obj-y))
  $$(foreach dir,$$(subdir-y),\
    $$(eval dirs += $(1)/$$(dir))\
    $$(eval $$(call collect_baremetal,$(1)/$$(dir)))\
  )
endef

define collect_project
  include-y :=
  subdir-y :=
  obj-y :=
  include $(BASEDIR)/$(1)/Makefile
  includes := $$(includes) $$(addprefix $(1)/,$$(include-y))
  objs := $$(objs) $$(addprefix $(BUILD)/$(1)/,$$(obj-y))
  $$(foreach dir,$$(subdir-y),\
    $$(eval dirs += $(1)/$$(dir))\
    $$(eval $$(call collect_project,$(1)/$$(dir)))\
  )
endef


$(eval $(call collect_baremetal,$(BAREMETAL_PATH)))
dirs :=
$(foreach dir,$(srcdirs),\
	$(eval $(call collect_project,$(dir)))\
)

all: $(BUILD)/$(target)
	@$(MAKE) -s -f $(firstword $(MAKEFILE_LIST)) deps

-include $(BUILD)/deps.mk

.PHONY: deps
deps:
	@rm -f $(BUILD)/deps.mk
	@$(foreach dir,$(dirs),\
	  $(foreach file,$(wildcard $(BUILD)/$(dir)/*.d),\
	    cat $(file) >> $(BUILD)/deps.mk;\
	  )\
	)

.PRECIOUS: $(BUILD)/. $(BUILD)%/.
$(BUILD)/.:
	$(Q)mkdir -p $@
$(BUILD)%/.:
	$(Q)mkdir -p $@
.SECONDEXPANSION:

compile_deps := $$(@D)/. $(BUILD)/config.h

$(BASEDIR)/.config:
	$(Q)$(BAREMETAL_PATH)/tools/kconfig/menuconfig.py

$(BUILD)/config.h: $(BASEDIR)/.config | $$(@D)/.
	$(Q)$(BAREMETAL_PATH)/tools/kconfig/genconfig.py --header-path $@

$(BUILD)/%.lds: $(BASEDIR)/%.lds.S | $(compile_deps)
	$(D) "   CPP      $<"
	$(Q)$(CPP) -P -MMD -MP -MF $@.d -MQ $@ -x c -DBUILD=$(BUILD:./%=%) $(INCLUDE) $< -o $@

$(BUILD)/%.lds: $(BAREMETAL_PATH)/%.lds.S | $(compile_deps)
	$(D) "   CPP      $<"
	$(Q)$(CPP) -P -MMD -MP -MF $@.d -MQ $@ -x c -DBUILD=$(BUILD:./%=%) $(INCLUDE) $< -o $@

$(BUILD)/%.o: $(BASEDIR)/%.S | $$(@D)/. $(BUILD)/config.h
	$(D) "   AS       $<"
	$(Q)$(CC) -c -MMD -MP -MF $@.d -MQ $@ $(CFLAGS) $(ASFLAGS) $(INCLUDE) $< -o $@

$(BUILD)/%.o: $(BAREMETAL_PATH)/%.S | $(compile_deps)
	$(D) "   AS       $<"
	$(Q)$(CC) -c -MMD -MP -MF $@.d -MQ $@ $(CFLAGS) $(ASFLAGS) $(INCLUDE) $< -o $@

$(BUILD)/%.o: $(BASEDIR)/%.c | $(compile_deps)
	$(D) "   CC       $<"
	$(Q)$(CC) -c -MMD -MP -MF $@.d -MQ $@ $(CFLAGS) $(INCLUDE) $< -o $@

$(BUILD)/%.o: $(BAREMETAL_PATH)/%.c | $(compile_deps)
	$(D) "   CC       $<"
	$(Q)$(CC) -c -MMD -MP -MF $@.d -MQ $@ $(CFLAGS) $(INCLUDE) $< -o $@

$(BUILD)/%.o: $(BASEDIR)/%.cpp | $(compile_deps)
	$(D) "   CXX      $<"
	$(Q)$(CC) -c -MMD -MP -MF $@.d -MQ $@ $(CFLAGS) $(INCLUDE) $< -o $@

$(BUILD)/%.o: $(BAREMETAL_PATH)/%.cpp | $(compile_deps)
	$(D) "   CXX      $<"
	$(Q)$(CC) -c -MMD -MP -MF $@.d -MQ $@ $(CFLAGS) $(INCLUDE) $< -o $@

$(BUILD)/%.o: $(BASEDIR)/%.cc | $(compile_deps)
	$(D) "   CXX      $<"
	$(Q)$(CC) -c -MMD -MP -MF $@.d -MQ $@ $(CFLAGS) $(INCLUDE) $< -o $@

$(BUILD)/%.o: $(BAREMETAL_PATH)/%.cc | $(compile_deps)
	$(D) "   CXX      $<"
	$(Q)$(CC) -c -MMD -MP -MF $@.d -MQ $@ $(CFLAGS) $(INCLUDE) $< -o $@

$(BUILD)/$(basename $(target)).elf: $(BUILD)/$(ldscript-y) $(objs) | $$(@D)/.
	$(D) "   LD       $<"
	$(Q)$(CC) $(CFLAGS) $(LDFLAGS) -T $^ $(LIBS) -o $@

$(BUILD)/$(basename $(target)).bin: $(BUILD)/$(basename $(target)).elf
	$(D) "   OBJDUMP  $<"
	$(Q)$(OBJDUMP) -d -m armv5te $< > $(@:.bin=.dis)
	$(D) "   OBJCOPY  $<"
	$(Q)$(OBJCOPY) -S -I elf32-littlearm -O binary $< $@
	@echo
	@$(SIZE) $<
	@$(SIZE) --target=binary $@

.PHONY: clean
clean:
	@rm -rf $(BUILD)

.PHONY: boot
boot: $(BUILD)/$(target)
	${MICROMON_PATH}/bootstrap.py $< 115200
