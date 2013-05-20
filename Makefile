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

subdir-$(CONFIG_BAREMETAL_CLIB_NANOLIB) += nanolib
obj-$(CONFIG_BAREMETAL_CLIB_NEWLIB) += newlib_stubs.o
libs-$(CONFIG_BAREMETAL_CLIB_NEWLIB) += -lc

include-y += include

# entry and early are the first bit of code that executes
# they should stand alone except for the jump to startup
obj-y += entry.o early.o

# startup is the first relocated code to execute
# it will call main()
obj-y += startup.o

obj-y += halt.o
obj-$(CONFIG_BAREMETAL_UART) += uart.o
obj-$(CONFIG_BAREMETAL_CACHE) += _cache.o cache.o
obj-$(CONFIG_BAREMETAL_CLOCKING) += clocking.o

