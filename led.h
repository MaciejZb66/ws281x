#pragma once
#include <stdio.h>
#include <stdint.h>
#ifdef USING_TIMER
	#include "tim.h"
#endif
#ifdef USING_SPI
	#include "spi.h"
#endif

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

#define reset_signal 224

#define SPI_logic_zero 0b100 //boundrate 2.5Mbit/s, 0.4us high, 1.2us period
#define SPI_logic_one 0b110  //boundrate 2.5Mbit/s, 0.8us high, 1.2us period

typedef enum{
    send_by_TIMER,
    send_by_SPI
}send_type;

typedef struct
{
    TIM_HandleTypeDef* timer;
    uint16_t PWM_logic_zero;
    uint16_t PWM_logic_one;
    uint32_t channel;
    uint8_t dataflag;
    
}timer_data;

typedef struct 
{
    SPI_HandleTypeDef* hspi;
}spi_data;


typedef struct 
{
    send_type type;
    uint16_t number_of_leds;
	uint8_t LED_info[user_leds][4];
	uint16_t PWM_Data[reset_signal + (24 * user_leds)];    
    spi_data spi;
    timer_data tim;
}WS281x_data;

#ifdef USING_TIMER
	void WS281x_init_TIM(WS281x_data* led, TIM_HandleTypeDef* htim, uint32_t t_channel, uint16_t led_number);
#endif

#ifdef USING_SPI
	void WS281x_init_SPI(WS281x_data* led, SPI_HandleTypeDef* hspi);
#endif

void WS281x_set_leds(WS281x_data* led, uint8_t led_num, uint8_t red, uint8_t green, uint8_t blue);
void WS281x_set_gamma_leds(WS281x_data* led, uint8_t led_num, uint8_t red, uint8_t green, uint8_t blue);
void WS281x_set_gamma_bright_leds(WS281x_data* led, uint8_t led_num, uint8_t red, uint8_t green, uint8_t blue, uint8_t brightness);
void WS281x_set_hsv_leds(WS281x_data* led, uint8_t led_num, uint8_t hue, uint8_t saturation, uint8_t value);
void WS281x_send_data(WS281x_data* led);
