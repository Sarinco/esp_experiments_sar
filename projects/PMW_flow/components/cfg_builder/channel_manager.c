#include "channel_manager.h"
#include <stdio.h>


#include "esp_log.h"



struct Channel_specs get_channel_specs(uint8_t channel){
    if (channel > 15){
        ESP_LOGE("error", "channel nr cannot exceed 16");
        struct Channel_specs default_ch = {0, 0};
        return default_ch;
    }

    int speed_mode;
    if (channel > 7) {
        speed_mode = LEDC_LOW_SPEED_MODE;
    } else {
        speed_mode = LEDC_HIGH_SPEED_MODE;
    }

    struct Channel_specs to_return;
    to_return.actual_channel = channel % 8;
    to_return.speed_mode = speed_mode;
    return to_return;
}

void channel_setup(uint8_t channel, uint8_t gpioPin, uint8_t timer)
{

    struct Channel_specs ch_specs = get_channel_specs(channel);

    ledc_channel_config_t channel_conf = {
        .gpio_num = gpioPin,
        .speed_mode = ch_specs.speed_mode,
        .channel = ch_specs.actual_channel,
        .duty = 0,
        .timer_sel = timer,
    }; 
    ledc_channel_config(&channel_conf);
}

void change_duty(uint8_t channel, int duty)
{
    struct Channel_specs ch_specs = get_channel_specs(channel);
    ledc_set_duty(ch_specs.speed_mode, ch_specs.actual_channel, duty);
    ledc_update_duty(ch_specs.speed_mode, ch_specs.actual_channel);
}