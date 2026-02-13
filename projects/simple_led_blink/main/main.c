
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

#include "driver/gpio.h"
#include "sdkconfig.h"


#define BLINK_LED 2
#define LED_ON 0
#define LED_OFF 1

void app_main(void)
{
    // Config GPIO pin
    gpio_reset_pin(BLINK_LED);
    gpio_set_direction(BLINK_LED, GPIO_MODE_OUTPUT);

    // testing logs functionalities
    char *ourTaskName = pcTaskGetName(NULL);
    printf("TASK [%s] : Hello, starting up!\n", ourTaskName);
    ESP_LOGI(ourTaskName, "test logs\n");
    while (1) {
        //LED LOGIC IS INVERTED
        ESP_LOGI(ourTaskName, "led on");
        gpio_set_level(BLINK_LED, LED_ON);
        vTaskDelay(1000 / portTICK_PERIOD_MS);


        ESP_LOGI(ourTaskName, "led off");
        gpio_set_level(BLINK_LED, LED_OFF);
        vTaskDelay(1000 / portTICK_PERIOD_MS);

    }
}
