#
#  Copyright (C) 2013 Jeff Kent <jeff@jkent.net>
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

NAME    = baremetal
TARGET  = $(NAME).a

DIRS    = ./

CC      = $(CROSS_COMPILE)gcc
AR      = $(CROSS_COMPILE)ar
RANLIB  = $(CROSS_COMPILE)ranlib
 
# pedantic removed due to braced expressions
CFLAGS  = -std=gnu99 -Wall -fms-extensions \
          -mcpu=arm926ej-s -mlittle-endian -msoft-float \
          -ffast-math
ASFLAGS = -Wa,
INCLUDE = -I./include

ifneq ($(NODEBUG), 1)
	CFLAGS += -O0 -g3 -DDEBUG
else
	CFLAGS += -Os
endif


.SECONDARY:
.PHONY: all
all: $(TARGET)
	@$(MAKE) -s deps

-include obj/deps.mk

define new_c_rule
$(2)%.o: $(1)%.c
	@mkdir -p $$(@D)
	$(CC) -c $$(CFLAGS) $$(INCLUDE) -o $$@ -c $$<
	@$(CC) -MM $$(CFLAGS) $$(INCLUDE) $$< | \
	  sed -e 's/.*:/$$(subst /,\/,$$@):/' > $(2)$$*.d
endef

define new_s_rule
$(2)%.o: $(1)%.S
	@mkdir -p $$(@D)
	$(CC) -c $$(CFLAGS) $$(INCLUDE) -Wa,--defsym,_start=0 -o $$@ $$<
	@$(CC) -MM $$(CFLAGS) $$(INCLUDE) -Wa,--defsym,_start=0 $$< | \
	  sed -e 's/.*:/$$(subst /,\/,$$@):/' > $(2)$$*.d
endef

$(foreach src_dir,$(sort $(DIRS)), \
	$(eval S_SRCS += $(wildcard $(src_dir)*.S)) \
	$(eval C_SRCS += $(wildcard $(src_dir)*.c)) \
	$(eval obj_dir = $(subst ./,obj/,$(src_dir))) \
	$(eval $(call new_s_rule,$(src_dir),$(obj_dir))) \
	$(eval $(call new_c_rule,$(src_dir),$(obj_dir))) \
)

OBJS    = $(subst ./,./obj/,$(S_SRCS:.S=.o) $(C_SRCS:.c=.o))

%.a: $(OBJS)
	@mkdir -p $(@D)
	$(AR) rc $@ $^
	$(RANLIB) $@

.PHONY: deps
deps: $(TARGET)
	@rm -f ./obj/deps.mk
	@$(foreach directory,$(subst ./,./obj/,$(DIRS)), \
	  $(foreach file,$(wildcard $(directory)/*.d), \
		cat $(file) >> ./obj/deps.mk; \
	  ) \
	)

.PHONY: clean
clean:
	rm -rf ./obj
	rm -f $(TARGET)

