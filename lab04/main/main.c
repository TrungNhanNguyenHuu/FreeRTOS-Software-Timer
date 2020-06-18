#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "sdkconfig.h"
#include "driver/gpio.h"
#include "freertos/timers.h"


xTimerHandle timerHnd2Sec;
xTimerHandle timerHnd3Sec;

int timesFirstTimer = 0;
int timesSecondTimer = 0;

void task1(void *p){
    while(1){

    }
    vTaskDelete(NULL);
}

static void vTimerCallBackExpired(xTimerHandle pxTimer){
    if (pxTimer == timerHnd2Sec){
        printf("ahihi\n");
        timesFirstTimer = timesFirstTimer + 1;
    }

    if (timesFirstTimer == 10){
        timesFirstTimer = 0;
        xTimerDelete(timerHnd2Sec, 0);
    }

    if (pxTimer == timerHnd3Sec){
        printf("    ihahha\n");
        timesSecondTimer = timesSecondTimer + 1;
    }

    if (timesSecondTimer == 5){
        timesSecondTimer = 0;
        xTimerDelete(timerHnd3Sec, 0);
    }

}

void app_main(void)
{
    xTaskCreate(&task1, "task1", 1024*1, (void*) 0, tskIDLE_PRIORITY + 0, NULL);

    timerHnd2Sec = xTimerCreate("timer2sec", pdMS_TO_TICKS(2000), pdTRUE, (void*)0, vTimerCallBackExpired);
    xTimerStart(timerHnd2Sec, 0);

    timerHnd3Sec = xTimerCreate("timer3sec", pdMS_TO_TICKS(3000), pdTRUE, (void*)0, vTimerCallBackExpired);
    xTimerStart(timerHnd3Sec, 0); 
}



/*
void task1(void *p){
    while(1){

    }
    vTaskDelete(NULL);
}

void task2(void *p){
    while(1){
        printf("1752392\n");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}
*/

    //xTaskCreate(&task1, "task1", 1024*1, (void*) 0, tskIDLE_PRIORITY + 0, NULL);
    //xTaskCreate(&task2, "task2", 1024*2, (void*) 0, tskIDLE_PRIORITY + 1, NULL);
    //xTaskCreate(&task3, "task3", 1024*2, (void*) 0, tskIDLE_PRIORITY + 2, NULL);

    //xTaskCreatePinnedToCore(&task1, "task1", 1024*1, (void*) 0, tskIDLE_PRIORITY + 0, NULL, 1);
    //xTaskCreatePinnedToCore(&task2, "task2", 1024*2, (void*) 0, tskIDLE_PRIORITY + 1, NULL, 1);
    //xTaskCreatePinnedToCore(&task3, "task3", 1024*2, (void*) 0, tskIDLE_PRIORITY + 2, NULL, 1);
