
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"


#define BLINK_LED 2
#define BUTTON_READ 13

void app_main(void)
{
    // Config GPIO pin
    gpio_reset_pin(BLINK_LED);
    gpio_reset_pin(BUTTON_READ);
    gpio_set_direction(BLINK_LED, GPIO_MODE_OUTPUT);
    gpio_set_direction(BUTTON_READ, GPIO_MODE_INPUT);

    int level=0;

    while (1) {
        //LED LOGIC IS INVERTED
        if (gpio_get_level(BUTTON_READ) == 0) {
            vTaskDelay(20/portTICK_PERIOD_MS);
            if (gpio_get_level(BUTTON_READ) == 0) {
                gpio_set_level(BLINK_LED, 1-level);
                level = 1-level;
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
