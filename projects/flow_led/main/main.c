
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"


#define BUTTON_READ 13

int led_gpios[] = {15, 2, 0, 4, 5, 18, 19, 21, 22, 23};
int led_gpios_length = sizeof(led_gpios) / sizeof(led_gpios[0]);

void reset_leds(void)
{
    //Turn off leds
    for (int i = 0; i < led_gpios_length-1; i++)
    {
        gpio_set_level(led_gpios[led_gpios_length-i-1], 0);
        //vTaskDelay(20 / portTICK_PERIOD_MS);
    }
    //Then make a little flow animation
    for (int i = 1; i < led_gpios_length; i++)
    {
        gpio_set_level(led_gpios[i-1], 0);
        gpio_set_level(led_gpios[i], 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    for (int i = led_gpios_length-2; i >= 0; i--)
    {
        gpio_set_level(led_gpios[i+1], 0);
        gpio_set_level(led_gpios[i], 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    gpio_set_level(led_gpios[0], 0);
    
}

void app_main(void)
{
    // Config GPIO pin
    for (int i = 0; i < led_gpios_length; i++)
    {
        gpio_reset_pin(led_gpios[i]);
        gpio_set_direction(led_gpios[i], GPIO_MODE_OUTPUT);
    }
    
    gpio_reset_pin(BUTTON_READ);
    gpio_set_direction(BUTTON_READ, GPIO_MODE_INPUT);

    int b_presses=0;

    while (1) {
        //LED LOGIC IS INVERTED
        if (gpio_get_level(BUTTON_READ) == 0) {
            vTaskDelay(20/portTICK_PERIOD_MS);
            if (gpio_get_level(BUTTON_READ) == 0) {
                if (b_presses >= led_gpios_length){
                    b_presses = 0;
                    reset_leds();
                } else {
                    gpio_set_level(led_gpios[b_presses], 1);
                    b_presses += 1;
                }
            }
            while (gpio_get_level(BUTTON_READ) == 0);
            vTaskDelay(20/portTICK_PERIOD_MS);
            while (gpio_get_level(BUTTON_READ) == 0);
        }

        //if (gpio_get_level(BUTTON_READ) == 0) {
            //gpio_set_level(BLINK_LED, 1);
        //}else {
            //gpio_set_level(BLINK_LED, 0);
        //}
    }
}
