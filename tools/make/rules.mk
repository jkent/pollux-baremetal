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
BAREMETAL_RELATIVE_PATH := $(shell realpath --relative-to $(BASEDIR) $(BAREMETAL_PATH))
BUILD := $(BASEDIR)/build
-include $(BASEDIR)/.config

includes += $(include-y)

CROSS_COMPILE := arm-none-eabi-

AS      := $(CROSS_COMPILE)as
LD      := $(CROSS_COMPILE)ld
CC      := $(CROSS_COMPILE)gcc
CXX     := $(CROSS_COMPILE)g++
CPP     := $(CROSS_COMPILE)gcc -E
AR      := $(CROSS_COMPILE)ar
NM      := $(CROSS_COMPILE)nm
STRIP   := $(CROSS_COMPILE)strip
OBJCOPY := $(CROSS_COMPILE)objcopy
OBJDUMP := $(CROSS_COMPILE)objdump
SIZE    := $(CROSS_COMPILE)size

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

ifeq ($(V),1)
  D := @true
  Q :=
else
  D := @echo
  Q := @
endif

objs :=

includes := $(includes) $(include-y)
define collect_baremetal
  include-y :=
  obj-y :=
  subdir-y :=
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
  obj-y :=
  subdir-y :=
  include $(BASEDIR)/$(1)/Makefile
  includes := $$(includes) $$(addprefix $(1)/,$$(include-y))
  objs := $$(objs) $$(addprefix $(BUILD)/$(1)/,$$(obj-y))
  $$(foreach dir,$$(subdir-y),\
    $$(eval dirs += $(1)/$$(dir))\
    $$(eval $$(call collect_project,$(1)/$$(dir)))\
  )
endef

$(eval $(call collect_baremetal,$(BAREMETAL_PATH)))
srcdirs ?= src
$(foreach dir,$(srcdirs),\
	$(eval $(call collect_project,$(dir)))\
)

all: $(BUILD)/$(target)
	@$(MAKE) -s -f $(firstword $(MAKEFILE_LIST)) deps

# dependency generation
.PHONY: deps
deps: $(BUILD)/.
	@rm -f $(BUILD)/deps.mk
	@find $(BAREMETAL_PATH) -name \*.d -type f -exec sh -c 'cat {} >> $(BUILD)/deps.mk' \;
	@find $(BUILD) -name \*.d -type f -exec sh -c 'cat {} >> $(BUILD)/deps.mk' \;
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

define make_build_rules
$$(BUILD)/%.lds: $(1)/%.lds.S | $$(DEPS)
	$$(D) "   CPP      $$<"
	$$(Q)$$(CPP) -P -MMD -MP -MF $$@.d -MQ $$@ -x c -DBUILD=$$(BUILD:./%=%) $$(INCLUDE) $$< -o $$@

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

$(eval $(call make_build_rules,$(BASEDIR)))
$(eval $(call make_build_rules,$(BAREMETAL_RELATIVE_PATH)))

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
