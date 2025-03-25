#pragma once
#include "led.h"

void WS281x_move_one_led_down(WS281x_data* led);
void WS281x_bright_up(WS281x_data* led, uint8_t bright, uint8_t led_num);
void WS281x_bright_down(WS281x_data* led, uint8_t bright, uint8_t led_num);
void WS281x_bright_all_up(WS281x_data* led, uint8_t bright);
void WS281x_bright_all_down(WS281x_data* led, uint8_t bright);
void WS281x_one_walking_led_up(WS281x_data* led, uint16_t delay, uint8_t start, uint8_t end);
void WS281x_one_walking_led_down(WS281x_data* led, uint16_t delay, uint8_t start, uint8_t end);
void WS281x_rainbow(WS281x_data* led, uint8_t start, uint8_t end, uint8_t huejump, uint8_t hueoffset);