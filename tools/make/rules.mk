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

ifndef RECURSIVE_INCLUDE
RECURSIVE_INCLUDE := 1

# default rule
.PHONY: all
all:

BASEDIR ?= $(patsubst %/,%,$(dir $(firstword $(MAKEFILE_LIST))))
BAREMETAL_RELATIVE_PATH := $(shell realpath --relative-to $(BASEDIR) $(BAREMETAL_PATH))
BUILD := $(BASEDIR)/build
-include $(BASEDIR)/.config

CC      := arm-none-eabi-gcc
OBJCOPY := arm-none-eabi-objcopy
OBJDUMP := arm-none-eabi-objdump
SIZE    := arm-none-eabi-size

CFLAGS   = -std=gnu99 -Wall -fms-extensions $(cflags-y)
ASFLAGS := -Wa,-defsym,_entry=$(CONFIG_BAREMETAL_ENTRY_ADDRESS)
LDFLAGS := -Wl,--gc-sections -Wl,-M,-Map,$(BUILD)/$(basename $(target)).map
LIBS     = -lgcc $(libs-y)
INCLUDE  = --include $(BUILD)/config.h $(addprefix -I,$(BUILD) $(includes))

cflags-y += -mlittle-endian -msoft-float -mtune=arm9tdmi -march=armv5te -mthumb -mthumb-interwork -nostartfiles
ldscript-y ?= baremetal/baremetal.lds

ifdef CONFIG_DEBUG
  cflags-y += -O0 -g3 -DDEBUG
else
  cflags-y += -Os
endif

# traverse directories for variables
includes := 
objs :=
dirs :=
define collect_vars
  include-y :=
  obj-y :=
  subdir-y :=
  relative := $(shell realpath --relative-to $(if $2,$2,$1) $1)
  include $1/Makefile
  includes := $$(includes) $$(addprefix $1/,$$(include-y))
  objs := $$(objs) $$(addprefix $(BUILD)/$$(relative)/,$$(obj-y))
  $$(foreach dir,$$(subdir-y),\
    $$(eval dirs += $1/$$(dir))\
    $$(eval $$(call collect_vars,$(1)/$$(dir),$(if $2,$2,$1)))\
  )
endef
$(eval $(call collect_vars,$(BAREMETAL_PATH)))
$(eval $(call collect_vars,$(BASEDIR)))

ifeq ($(V),1)
  D := @true
  Q :=
else
  D := @echo
  Q := @
endif

all: $(BUILD)/$(target)
	$(Q)$(MAKE) -s -f $(firstword $(MAKEFILE_LIST)) deps

# dependency generation
.PHONY: deps
deps: $(BUILD)/.
	$(Q)rm -f $(BUILD)/deps.mk
	$(Q)find $(BAREMETAL_PATH) -name \*.d -type f -exec sh -c 'cat {} >> $(BUILD)/deps.mk' \;
	$(Q)find $(BUILD) -name \*.d -type f -exec sh -c 'cat {} >> $(BUILD)/deps.mk' \;
-include $(BUILD)/deps.mk

# magic to automatically create $(BUILD) directory
.PRECIOUS: $(BUILD)/. $(BUILD)%/.
$(BUILD)/.:
	$(Q)mkdir -p $@
$(BUILD)%/.:
	$(Q)mkdir -p $@
.SECONDEXPANSION:

DEPS := $$(@D)/. $(BUILD)/config.h

.PHONY: config
$(BASEDIR)/.config config:
	$(Q)if [ -f $(BASEDIR)/.config -o ! -f $(BASEDIR)/defconfig ]; then \
		menuconfig.py || touch $(BASEDIR)/.config; \
	else \
		defconfig.py $(BASEDIR)/defconfig; \
	fi

define generate_rules
$$(BUILD)/%.lds: $(1)/%.lds.S | $$(DEPS)
	$$(D) "   CPP      $$<"
	$$(Q)$$(CC) -E -P -MMD -MP -MF $$@.d -MQ $$@ -x c -DBUILD=$$(BUILD:./%=%) $$(INCLUDE) $$< -o $$@

$$(BUILD)/%.o: $(1)/%.S | $$(DEPS)
	$$(D) "   AS       $$<"
	$$(Q)$$(CC) -c -MMD -MP -MF $$@.d -MQ $$@ $$(CFLAGS) $$(ASFLAGS) $$(INCLUDE) $$< -o $$@

$$(BUILD)/%.o: $(1)/%.c | $$(DEPS)
	$$(Q) mkdir -p $$(@D)
	$$(D) "   CC       $$<"
	$$(Q)$$(CC) -c -MMD -MP -MF $$@.d -MQ $$@ $$(CFLAGS) $$(INCLUDE) $$< -o $$@

$$(BUILD)/%.o: $(1)/%.cpp | $$(DEPS)
	$$(Q) mkdir -p $$(@D)
	$$(D) "   CXX      $$<"
	$$(Q)$$(CC) -c -MMD -MP -MF $$@.d -MQ $$@ $$(CFLAGS) $$(CXXFLAGS) $$(INCLUDE) $$< -o $$@

$$(BUILD)/%.o: $(1)/%.cc | $$(DEPS)
	$$(Q) mkdir -p $$(@D)
	$$(D) "   CXX      $$<"
	$$(Q)$$(CC) -c -MMD -MP -MF $$@.d -MQ $$@ $$(CFLAGS) $$(CXXFLAGS) $$(INCLUDE) $$< -o $$@
endef

$(eval $(call generate_rules,$(BASEDIR)))
$(eval $(call generate_rules,$(BAREMETAL_RELATIVE_PATH)))

$(BUILD)/config.h: $(BASEDIR)/.config | $$(@D)/.
	$(Q)genconfig.py --header-path $@

$(BUILD)/$(basename $(target)).elf: $(BUILD)/$(ldscript-y) $(objs) | $$(@D)/.
	$(Q) mkdir -p $(@D)
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

endif