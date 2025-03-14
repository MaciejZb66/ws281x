#pragma once
#include "effects.h"

extern WS281x_data LED[OUTPUTS];
extern const uint8_t gamma8[];
extern const uint8_t reverse_max_gamma8[];
extern const uint8_t reverse_min_gamma8[];

void move_one_led_down(WS281x_data* led){
	for(int i = 0; i <led->number_of_leds; i++)
	{
		if(i != 0){
			WS281x_set_leds(led, i, led->LED_info[i - 1][1], led->LED_info[i - 1][2], led->LED_info[i - 1][3]);
		}else{
			WS281x_set_leds(led, i, led->LED_info[user_leds - 1][1],led->LED_info[user_leds - 1][2],led->LED_info[user_leds - 1][3]);
		}
	}
}

void bright_up(WS281x_data* led, uint8_t bright, uint8_t led_num){
	bright %= 101;
	for(int i = 1; i <= 3; i++){
		if(led->LED_info[led_num][i] * (100 + bright)/ 100 < 255){
			led->LED_info[led_num][i] = gamma8[reverse_min_gamma8[led->LED_info[led_num][i]] * (100 + bright) / 100];
		}else{
			led->LED_info[led_num][i] = 255;
		}
	}

}

void bright_down(WS281x_data* led, uint8_t bright, uint8_t led_num){
	bright %= 101;
	for(int i = 1; i <= 3; i++){
		if(led->LED_info[led_num][i] * (100 - bright)/ 100 > 1){
			led->LED_info[led_num][i] = gamma8[reverse_max_gamma8[led->LED_info[led_num][i]] * (100 - bright) / 100];
		}else{
			led->LED_info[led_num][i] = 0;
		}
	}

}

void bright_all_up(WS281x_data* led, uint8_t bright){
	for(int i = 0; i < led->number_of_leds; i++){
		bright_up(led, bright, i);
	}
}

void bright_all_down(WS281x_data* led, uint8_t bright){
	for(int i = 0; i < led->number_of_leds; i++){
		bright_down(led, bright, i);
	}
}

void one_walking_led_up(WS281x_data* led, uint16_t delay, uint8_t start, uint8_t end){
	uint8_t colors[3];
	if(end > led->number_of_leds){
		end = led->number_of_leds;
	}
	for(int i = start; i < end - 1; i++){
		for(int j = 1; j <= 3; j++){
			colors[j - 1] = led->LED_info[i][j];
			led->LED_info[i][j] = led->LED_info[i + 1][j];
			led->LED_info[i + 1][j] = colors[j - 1];
		}
		WS281x_send_data(led);
        #ifdef FREERTOS
            osDelay(delay);
        #else
            HAL_Delay(delay);
        #endif		
	}
}

void one_walking_led_down(WS281x_data* led, uint16_t delay, uint8_t start, uint8_t end){
	uint8_t colors[3];
	if(start > led->number_of_leds){
			start = led->number_of_leds;
		}
	for(int i = start - 1; i > end; i--){
		for(int j = 1; j <= 3; j++){
			colors[j - 1] = led->LED_info[i][j];
			led->LED_info[i][j] = led->LED_info[i - 1][j];
			led->LED_info[i - 1][j] = colors[j - 1];
		}
		WS281x_send_data(led);
        #ifdef FREERTOS
            osDelay(delay);
        #else
            HAL_Delay(delay);
        #endif
	}

}

void rainbow(WS281x_data* led, uint8_t start, uint8_t end, uint8_t huejump, uint8_t hueoffset){
	uint16_t hueef;
	for(int j = start; j < end; j++){

		hueef =	(hueoffset + huejump * (j - start)) % 256;
		WS281x_set_hsv_leds(led, j, (uint8_t)hueef, 192, 128);
	}
	WS281x_send_data(led);
}

