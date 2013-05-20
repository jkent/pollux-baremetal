/*
 * Copyright (C) 2013 Jeff Kent <jeff@jkent.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef _CACHE_H
#define _CACHE_H

#include "config.h"

#if defined(CONFIG_BAREMETAL_CACHE)
# if defined(__thumb__)
	extern void _thumb_enable_cache(void);
	extern void _thumb_disable_cache(void);
#  define enable_cache() _thumb_enable_cache()
#  define disable_cache() _thumb_disable_cache()
#  if defined(CONFIG_BAREMETAL_ENABLE_DCACHE)
	extern void _thumb_assign_tlb(void *tlb);
#   define assign_tlb(p) _thumb_assign_tlb(p)
#  endif
# else
	extern void _enable_cache(void);
	extern void _disable_cache(void);
#  define enable_cache() _enable_cache()
#  define disable_cache() _disable_cache()
#  if defined(CONFIG_BAREMETAL_ENABLE_DCACHE)
	extern void _assign_tlb(void *tlb);
#   define assign_tlb(p) _assign_tlb(p)
#  endif
# endif
# if defined(CONFIG_BAREMETAL_ENABLE_DCACHE)
	extern void *main_tlb;
	extern void init_tlb(void *tlb);
# endif
#else
	#define enable_cache()
	#define disable_cache()
#endif

#endif /* _CACHE_H */
