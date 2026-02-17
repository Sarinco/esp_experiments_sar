#include <stdio.h>
#include "timer_cfg.h"

void timer_setup(int timerID, int freqHz, ledc_timer_bit_t dutyRes)
{
    ledc_timer_config_t ls_timer_conf = {
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .timer_num = timerID,
        .freq_hz = freqHz,
        .duty_resolution = dutyRes, 
        .clk_cfg = LEDC_APB_CLK
    };
    ledc_timer_config_t hs_timer_conf = {
        .speed_mode = LEDC_HIGH_SPEED_MODE,
        .timer_num = timerID,
        .freq_hz = freqHz,
        .duty_resolution = dutyRes, 
        .clk_cfg = LEDC_APB_CLK
    };
    ledc_timer_config(&ls_timer_conf);
    ledc_timer_config(&hs_timer_conf);
}
