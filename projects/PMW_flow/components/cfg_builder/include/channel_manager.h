#include "driver/ledc.h"

struct Channel_specs {
    uint8_t actual_channel;
    uint8_t speed_mode;
};

struct Channel_specs get_channel_specs(uint8_t channel);

void channel_setup(uint8_t channel, uint8_t gpioPin, uint8_t timer);

void change_duty(uint8_t channel, int duty);