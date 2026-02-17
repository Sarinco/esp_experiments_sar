#include "driver/ledc.h"
/*
Timer set up for both high speed and low speed mode
*/
void timer_setup(int timerID, int freqHz, ledc_timer_bit_t dutyRes);