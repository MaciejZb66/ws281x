#include "led.h"

uint8_t LED_info[user_leds][4];
uint16_t pwm_Data[reset_signal + (24 * user_leds)];
uint8_t dataflag;

void set_leds(uint8_t led_num, uint8_t red, uint8_t green, uint8_t blue){
	LED_info[led_num][0] = led_num;
	LED_info[led_num][1] = red;
	LED_info[led_num][2] = green;
	LED_info[led_num][3] = blue;
}

void set_gamma_leds(uint8_t led_num, uint8_t red, uint8_t green, uint8_t blue){
	LED_info[led_num][0] = led_num;
	LED_info[led_num][1] = gamma8[red];
	LED_info[led_num][2] = gamma8[green];
	LED_info[led_num][3] = gamma8[blue];
}

void set_gamma_bright_leds(uint8_t led_num, uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness){
	brightness %= 101;
	red = red * 100 / brightness;
	green = green * 100 / brightness;
	blue = blue * 100 / brightness;
	LED_info[led_num][0] = led_num;
	LED_info[led_num][1] = gamma8[red];
	LED_info[led_num][2] = gamma8[green];
	LED_info[led_num][3] = gamma8[blue];
}
void set_hsv_leds(uint8_t led, uint8_t hue, uint8_t saturation, uint8_t value){
	float h, s, v, f, p, q, t;
	uint8_t red, green, blue;
	h = (float)hue / 255;
	s = (float)saturation / 255;
	v = (float)value / 255;
	uint8_t i = (uint8_t)((float)hue /42.67f);
	f = h * 6 - i;
	p = v * (1 - s);
	q = v * (1 - f * s);
	t = v * (1 - (1 - f) * s);
	switch(i % 6){
	case 0:
		red = (uint8_t)(v * 255);
		green = (uint8_t)(t * 255);
		blue = (uint8_t)(p * 255);
		break;
	case 1:
		red = (uint8_t)(q * 255);
		green = (uint8_t)(v * 255);
		blue = (uint8_t)(p * 255);
		break;
	case 2:
		red = (uint8_t)(p * 255);
		green = (uint8_t)(v * 255);
		blue = (uint8_t)(t * 255);
		break;
	case 3:
		red = (uint8_t)(p * 255);
		green = (uint8_t)(q * 255);
		blue = (uint8_t)(v * 255);
		break;
	case 4:
		red = (uint8_t)(t * 255);
		green = (uint8_t)(p * 255);
		blue = (uint8_t)(v * 255);
		break;
	case 5:
		red = (uint8_t)(v * 255);
		green = (uint8_t)(p * 255);
		blue = (uint8_t)(q * 255);
		break;
	}
	set_leds(led, gamma8[red], gamma8[green], gamma8[blue]);
}

void WS281x_send_data(void){
	uint32_t color;
	uint32_t counter = 0;
	for(int i = 0; i < user_leds; i++){
		color = ((LED_info[i][1] << 8) | (LED_info[i][2]) | (LED_info[i][3] << 16));
		for(int j = 23; j >= 0; j--){
			if(color & (1 << j)){
				pwm_Data[counter] = pwm_one;
			}else{
				pwm_Data[counter] = pwm_zero;
			}
			counter++;
		}
	}
	for(int i = 0; i < reset_signal; i++){
		pwm_Data[counter] = 0;
		counter++;
	}
	HAL_TIM_PWM_Start_DMA(WS_tim, TIM_CHANNEL_1, (uint32_t*)pwm_Data, counter);
	while(!dataflag){};
	dataflag = 0;
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim){
    HAL_TIM_PWM_Stop_DMA(WS_tim, TIM_CHANNEL_1);
    dataflag = 1;
}