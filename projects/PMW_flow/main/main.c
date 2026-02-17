
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "driver/ledc.h"

#include "timer_cfg.h"
#include "channel_manager.h"


int channels[]   = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int used_gpios[] = {15, 2, 0, 4, 5, 18, 19, 21, 22, 23}; 
int used_gpios_length = sizeof(used_gpios) / sizeof(used_gpios[0]);
int timer = 0;

int delay_ms = 50 / portTICK_PERIOD_MS;
int duty_values[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                     1023, 512, 256, 128, 64, 32, 16, 8, 4, 2, 
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
                    };

void app_main(void)
{
    // Config timer specs
    timer_setup(timer, 1000, LEDC_TIMER_10_BIT);
    //config the channels
    for (size_t i = 0; i < used_gpios_length; i++)
    {
        channel_setup(channels[i], used_gpios[i], timer);
    }
    
    while (1) {
        for (size_t i = 0; i < 20; i++)
        {
            for (size_t j = 0; j < 10; j++)
            {
                change_duty(j, duty_values[i+j]);
            }
            vTaskDelay(delay_ms);
        }

        for (size_t i = 0; i < 20; i++)
        {
            for (size_t j = 0; j < 10; j++)
            {
                change_duty(9-j, duty_values[i+j]);
            }
            vTaskDelay(delay_ms);
        }
        
    }
}
