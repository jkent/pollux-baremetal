/*
 * Copyright (C) 2020 Jeff Kent <jeff@jkent.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
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

#include <asm/io.h>
#include <asm/types.h>
#include <driver/uart.h>
#include <stdio.h> 
#include <stdlib.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

static void a_task(void *pvParameters);
static void b_task(void *pvParameters);

int main(void)
{
    //puts("Creating tasks");
    uart0_writeb('1');

    BaseType_t result = xTaskCreate(a_task, "a", 1024, NULL, tskIDLE_PRIORITY + 1, NULL);
    uart0_writeb(result == pdPASS ? '+' : '-');
    result = xTaskCreate(b_task, "b", 1024, NULL, tskIDLE_PRIORITY + 1, NULL);
    uart0_writeb(result == pdPASS ? '+' : '-');

    //puts("Starting scheduler");
    uart0_writeb('2');

    vTaskStartScheduler();

    return 0;
}

static void a_task(void *pvParameters)
{
    while(1) {
        uart0_writeb('a');
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

static void b_task(void *pvParameters)
{
    while(1) {
        uart0_writeb('b');
        //portYIELD();
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
