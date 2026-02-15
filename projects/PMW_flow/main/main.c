
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "driver/ledc.h"



int channels[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
int used_gpios = 2; 

void app_main(void)
{
    // Config timer specs
    ledc_timer_config_t timer_conf = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = LEDC_TIMER_0,
        .freq_hz = 1000,
        .duty_resolution = LEDC_TIMER_8_BIT, 
        .clk_cfg = LEDC_APB_CLK
    };
    //int best_duty = ledc_find_suitable_duty_resolution(80000000, 5000);
    ledc_timer_config(&timer_conf);

    //config the channel
    ledc_channel_config_t channel_conf = {
        .gpio_num = 2,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .channel = LEDC_CHANNEL_0,
        .duty = 0,
        .timer_sel = LEDC_TIMER_0,
    }; 
    ledc_channel_config(&channel_conf);
    // ledc_timer_config();
    while (1) {
        int duty = 0;
        int max_duty = (1 << 13) - 1;
        while ( duty < max_duty ){
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
            vTaskDelay(10 / portTICK_PERIOD_MS);
            duty += max_duty / 100;
        }
        duty = max_duty - 1;
        while ( duty >= 0 ){
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
            vTaskDelay(10 / portTICK_PERIOD_MS);
            duty -= max_duty / 100;
        }
        duty = 0;
    }
}
