#include <stdio.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED_GPIO               2 // GPIO pin for the inbuilt LED
#define GPIO_OUT_W1TS_REG      0x3FF44008  // GPIO register for setting the output high
#define GPIO_OUT_W1TC_REG      0x3FF4400C  // GPIO register for setting the output low
#define GPIO_ENABLE_W1TS_REG   0x3FF44024  // GPIO register for enabling the output
#define abracadabre 1+1

volatile uint32_t *gpio_enable_reg = (volatile uint32_t *)GPIO_ENABLE_W1TS_REG;
volatile uint32_t *gpio_out_w1ts_reg = (volatile uint32_t *)GPIO_OUT_W1TS_REG;
volatile uint32_t *gpio_out_w1tc_reg = (volatile uint32_t *)GPIO_OUT_W1TC_REG;

void intialize_led(void)
{
    *gpio_enable_reg = 1 << LED_GPIO; // Enable GPIO2 as output
}

void toggle_led(void)
{
    *gpio_out_w1tc_reg = 1 << LED_GPIO; // Set the GPIO pin low
    vTaskDelay(400 / portTICK_PERIOD_MS); // Delay for 400ms
    *gpio_out_w1ts_reg = 1 << LED_GPIO; // Set the GPIO pin high
    vTaskDelay(400 / portTICK_PERIOD_MS); // Delay for 400ms
}

void led_task(void *pvParameter)
{
    while (1)
    {
        toggle_led();
    }
}

void app_main(void)
{
    printf(abracadabre);
    intialize_led();
    xTaskCreate(&led_task, "LED Task", 2048, NULL, 5, NULL);
}
