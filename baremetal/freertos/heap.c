/**
 * \file heap_useNewlib.c
 * \brief Wrappers required to use newlib malloc-family within FreeRTOS.
 *
 * \par Overview
 * Route FreeRTOS memory management functions to newlib's malloc family.
 * Thus newlib and FreeRTOS share memory-management routines and memory pool,
 * and all newlib's internal memory-management requirements are supported.
 *
 * \author Dave Nadler
 * \date 7-August-2019
 * \version 23-Sep-2019 comments, check no malloc call inside ISR
 *
 * \see http://www.nadler.com/embedded/newlibAndFreeRTOS.html
 * \see https://sourceware.org/newlib/libc.html#Reentrancy
 * \see https://sourceware.org/newlib/libc.html#malloc
 * \see https://sourceware.org/newlib/libc.html#index-_005f_005fenv_005flock
 * \see https://sourceware.org/newlib/libc.html#index-_005f_005fmalloc_005flock
 * \see https://sourceforge.net/p/freertos/feature-requests/72/
 * \see http://www.billgatliff.com/newlib.html
 * \see http://wiki.osdev.org/Porting_Newlib
 * \see http://www.embecosm.com/appnotes/ean9/ean9-howto-newlib-1.0.html
 *
 *
 * \copyright
 * (c) Dave Nadler 2017-2019, All Rights Reserved.
 * Web:         http://www.nadler.com
 * email:       drn@nadler.com
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * - Use or redistributions of source code must retain the above copyright notice,
 *   this list of conditions, ALL ORIGINAL COMMENTS, and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <malloc.h>
#include <errno.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/unistd.h>

#include <baremetal/linker.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

register void *stack_ptr asm("sp");

void *_sbrk_r(struct _reent *pReent, int incr)
{
	static void *current_heap_end = NULL;
	vTaskSuspendAll();

	if (current_heap_end == NULL) {
		current_heap_end = &_heap_bottom;
	}

	void *previous_heap_end = current_heap_end;
	if (current_heap_end + incr > stack_ptr) {
#if( configUSE_MALLOC_FAILED_HOOK == 1 )
		extern void vApplicationMallocFailedHook(void);
		(void)xTaskResumeAll();
		vApplicationMallocFailedHook();
#else
		pReent->_errno = ENOMEM;
		(void)xTaskResumeAll();
#endif
		return (void *)-1;
	}

	current_heap_end += incr;
	(void)xTaskResumeAll();
	return previous_heap_end;
}

void __malloc_lock(struct _reent *r)
{
	vTaskSuspendAll();
}

void __malloc_unlock(struct _reent *r)
{
	(void)xTaskResumeAll();
}

void *pvPortMalloc( size_t xSize )
{
	void *p = malloc(xSize);
	return p;
}

void vPortFree( void *pv )
{
	free(pv);
}

size_t xPortGetFreeHeapSize(void)
{
	struct mallinfo mi = mallinfo();
	return mi.fordblks + (uint32_t)(stack_ptr - sbrk(0));
}

void vPortInitialiseBlocks(void)
{
}
