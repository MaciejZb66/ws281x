#include "led.h"

const uint8_t gamma8[] = {
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
	0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
	1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
	2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
	5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
	10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
	17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
	25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
	37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
	51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
	69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
	90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
	115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
	144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
	177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
	215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

const uint8_t reverse_max_gamma8[] = {
	 27,  40,  48,  55,  60,  64,  68,  72,  75,  78,  81,  84,  86,  89,  91,  93,
	 95,  97,  99, 101, 103, 105, 107, 108, 110, 112, 113, 115, 116, 118, 119, 120,
	122, 123, 124, 126, 127, 128, 129, 131, 132, 133, 134, 135, 136, 137, 138, 139,
	140, 141, 143, 144, 145, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155,
	156, 156, 157, 158, 159, 160, 161, 161, 162, 163, 164, 165, 165, 166, 167, 168,
	168, 169, 170, 171, 171, 172, 173, 174, 174, 175, 176, 176, 177, 178, 178, 179,
	180, 180, 181, 182, 182, 183, 184, 184, 185, 186, 186, 187, 187, 188, 189, 189,
	190, 190, 191, 192, 192, 193, 193, 194, 195, 195, 196, 196, 197, 197, 198, 199,
	199, 200, 200, 201, 201, 202, 202, 203, 203, 204, 205, 205, 206, 206, 207, 207,
	208, 208, 209, 209, 210, 210, 211, 211, 212, 212, 213, 213, 214, 214, 215, 215,
	216, 216, 217, 217, 218, 218, 218, 219, 219, 220, 220, 221, 221, 222, 222, 223,
	223, 224, 224, 224, 225, 225, 226, 226, 227, 227, 228, 228, 228, 229, 229, 230,
	230, 231, 231, 231, 232, 232, 233, 233, 234, 234, 234, 235, 235, 236, 236, 236,
	237, 237, 238, 238, 238, 239, 239, 240, 240, 240, 241, 241, 242, 242, 242, 243,
	243, 244, 244, 244, 245, 245, 245, 246, 246, 247, 247, 247, 248, 248, 248, 249,
	249, 250, 250, 250, 251, 251, 251, 252, 252, 253, 253, 253, 254, 254, 254, 255,
};

const uint8_t reverse_min_gamma8[] = {
	  0,  28,  41,  49,  56,  61,  65,  69,  73,  76,  79,  82,  85,  87,  90,  92,
	 94,  96,  98, 100, 102, 104, 106, 108, 109, 111, 113, 114, 116, 117, 119, 120,
	121, 123, 124, 125, 127, 128, 129, 130, 132, 133, 134, 135, 136, 137, 138, 139,
	140, 141, 142, 144, 145, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155,
	156, 156, 157, 158, 159, 160, 161, 161, 162, 163, 164, 165, 165, 166, 167, 168,
	168, 169, 170, 171, 171, 172, 173, 174, 174, 175, 176, 176, 177, 178, 178, 179,
	180, 180, 181, 182, 182, 183, 184, 184, 185, 186, 186, 187, 187, 188, 189, 189,
	190, 190, 191, 192, 192, 193, 193, 194, 195, 195, 196, 196, 197, 197, 198, 199,
	199, 200, 200, 201, 201, 202, 202, 203, 203, 204, 205, 205, 206, 206, 207, 207,
	208, 208, 209, 209, 210, 210, 211, 211, 212, 212, 213, 213, 214, 214, 215, 215,
	216, 216, 217, 217, 218, 218, 218, 219, 219, 220, 220, 221, 221, 222, 222, 223,
	223, 224, 224, 224, 225, 225, 226, 226, 227, 227, 228, 228, 228, 229, 229, 230,
	230, 231, 231, 231, 232, 232, 233, 233, 234, 234, 234, 235, 235, 236, 236, 236,
	237, 237, 238, 238, 238, 239, 239, 240, 240, 240, 241, 241, 242, 242, 242, 243,
	243, 244, 244, 244, 245, 245, 245, 246, 246, 247, 247, 247, 248, 248, 248, 249,
	249, 250, 250, 250, 251, 251, 251, 252, 252, 253, 253, 253, 254, 254, 254, 255,
};

WS281x_data LED[OUTPUTS]={0};

#ifdef USING_TIMER
void WS281x_init_TIM(WS281x_data* led, TIM_HandleTypeDef* htim, uint32_t t_channel, uint16_t led_number){
	led->type = send_by_TIMER;
	led->tim.timer = htim;
	led->tim.channel = t_channel;
	led->tim.PWM_logic_zero = htim->Init.Period * 32 / 100;	// 32% time +-12%, 400us
	led->tim.PWM_logic_one = htim->Init.Period * 65 / 100;	// 64% time +-12%, 800us
	led->number_of_leds = led_number;
}
#endif
#ifdef USING_SPI
void WS281x_init_SPI(WS281x_data* led, SPI_HandleTypeDef* hspi){
	led->type = send_by_SPI;
	led->spi.hspi = hspi;
}
#endif
void WS281x_set_leds(WS281x_data* led, uint8_t led_num, uint8_t red, uint8_t green, uint8_t blue){
	led->LED_info[led_num][0] = led_num;
	led->LED_info[led_num][1] = red;
	led->LED_info[led_num][2] = green;
	led->LED_info[led_num][3] = blue;
}

void WS281x_set_gamma_leds(WS281x_data* led, uint8_t led_num, uint8_t red, uint8_t green, uint8_t blue){
	led->LED_info[led_num][0] = led_num;
	led->LED_info[led_num][1] = gamma8[red];
	led->LED_info[led_num][2] = gamma8[green];
	led->LED_info[led_num][3] = gamma8[blue];
}

void WS281x_set_gamma_bright_leds(WS281x_data* led, uint8_t led_num, uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness){
	brightness %= 101;
	red = red * 100 / brightness;
	green = green * 100 / brightness;
	blue = blue * 100 / brightness;
	led->LED_info[led_num][0] = led_num;
	led->LED_info[led_num][1] = gamma8[red];
	led->LED_info[led_num][2] = gamma8[green];
	led->LED_info[led_num][3] = gamma8[blue];
}

void WS281x_set_hsv_leds(WS281x_data* led, uint8_t led_num, uint8_t hue, uint8_t saturation, uint8_t value){
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
	WS281x_set_leds(led, led_num, gamma8[red], gamma8[green], gamma8[blue]);
}

void WS281x_send_data(WS281x_data* led){
	uint32_t color;
	
	if(led->type == send_by_TIMER){
		uint32_t counter = 0;
		for(int i = 0; i < led->number_of_leds; i++){
			color = ((led->LED_info[i][1] << 8) | (led->LED_info[i][2]) | (led->LED_info[i][3] << 16));
			for(int j = 23; j >= 0; j--){
				if(color & (1 << j)){
					led->PWM_Data[counter] = led->tim.PWM_logic_one;
				}else{
					led->PWM_Data[counter] = led->tim.PWM_logic_zero;
				}
				counter++;
			}
		}
		for(int i = 0; i < reset_signal; i++){
			led->PWM_Data[counter] = 0;
			counter++;
		}
		HAL_TIM_PWM_Start_DMA(led->tim.timer, led->tim.channel, (uint32_t*)led->PWM_Data, counter);
		while(!(led->tim.dataflag)){};
		led->tim.dataflag = 0;
	}

	if(led->type == send_by_SPI){
		for (int i = 0; i < led->number_of_leds; i++)
		{
			color = led->LED_info[i][2]<<16 | led->LED_info[i][1]<<8 | led->LED_info[i][3]; //bgr
			uint8_t sendData[24];
			uint8_t counter = 0;
		
			for (int j=23; j>=0; j--)
			{
				if (((color>>j)&0x01) == 1) 
				{
					sendData[counter++] = SPI_logic_one;
				}else{
					sendData[counter++] = SPI_logic_zero;
				}
				  
			}		
			HAL_SPI_Transmit(led->spi.hspi, sendData, 24, 1000);
		}		
		
	}
	
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim){
	for(int i = 0; i < OUTPUTS; i++){
		if (htim == LED[i].tim.timer)
		{
			HAL_TIM_PWM_Stop_DMA(LED[i].tim.timer, LED[i].tim.channel);
    		LED[i].tim.dataflag = 1;
		}		
	}
    
}