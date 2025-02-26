#pragma once
#include <stdio.h>
#include <stdint.h>
#include "tim.h"

#ifndef WS_CONFIG
    #include "sample_config.h"
#endif

#ifdef STM_FAMILY_F0
    #include "stm32f0xx_hal.h"
#elif defined STM_FAMILY_F1
    #include "stm32f1xx_hal.h"
#elif defined STM_FAMILY_F4
    #include "stm32f4xx_hal.h"
#elif defined STM_FAMILY_F7
    #include "stm32f7xx_hal.h"
#elif defined STM_FAMILY_G0
    #include "stm32g0xx_hal.h"
#elif defined STM_FAMILY_G1
    #include "stm32g1xx_hal.h"
#elif defined STM_FAMILY_G4
    #include "stm32g4xx_hal.h"
#elif defined STM_FAMILY_G7
    #include "stm32g7xx_hal.h"
#elif defined STM_FAMILY_L0
    #include "stm32l0xx_hal.h"
#elif defined STM_FAMILY_L1
    #include "stm32l1xx_hal.h"
#elif defined STM_FAMILY_L4
    #include "stm32l4xx_hal.h"
#elif defined STM_FAMILY_L7
    #include "stm32l7xx_hal.h"
#else
    #pragma message "Unsupported STM family"
#endif

#ifdef WS_TIM_1
	#define CP htim1.Init.Period
#elif defined WS_TIM_2
	#define CP htim2.Init.Period
#elif defined WS_TIM_3
	#define CP htim3.Init.Period
#elif defined WS_TIM_4
	#define CP htim4.Init.Period
#elif defined WS_TIM_15
	#define CP htim15.Init.Period
#elif defined WS_TIM_16
	#define CP htim16.Init.Period
#else
    #pragma message "NO TIMER CHOSEN"
#endif

#define pwm_zero (CP* 32 / 100)     // 32% time +-12%
#define pwm_one (CP * 64 / 100)     // 64% time +-12%
#define reset_signal 224

typedef struct 
{
	uint8_t LED_info[user_leds][4];
	uint16_t PWM_Data[reset_signal + (24 * user_leds)];
    TIM_HandleTypeDef* timer;
    uint32_t channel;
    uint8_t dataflag;
}WS281x_data;

void WS281x_init(WS281x_data* led, TIM_HandleTypeDef* htim, uint32_t t_channel);
void WS281x_set_leds(WS281x_data* led, uint8_t led_num, uint8_t red, uint8_t green, uint8_t blue);
void WS281x_set_gamma_leds(WS281x_data* led, uint8_t led_num, uint8_t red, uint8_t green, uint8_t blue);
void WS281x_set_gamma_bright_leds(WS281x_data* led, uint8_t led_num, uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness);
void WS281x_set_hsv_leds(WS281x_data* led, uint8_t led_num, uint8_t hue, uint8_t saturation, uint8_t value);
void WS281x_send_data(WS281x_data* led);
