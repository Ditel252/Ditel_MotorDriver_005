/*
 * RotaryEncoders.h
 *
 *  Created on: Dec 28, 2024
 *      Author: Suyam
 */

#ifndef INC_D_M_005_ROTARYENCODER_H_
#define INC_D_M_005_ROTARYENCODER_H_

#include "stm32f3xx_hal.h"
#include "stdbool.h"

#define __ROTARY_ENCODER_MESURE_1CYCLE_TIME (1 * 1000)	//[us]
#define __ROTARY_ENCODER_HARF_CYCLE_MAX_TIMER_COUNT 30000
#define __ROTARY_ENCODER_TIME_COUNT_MAX_TIME 5

typedef struct{
	GPIO_TypeDef* __RotaryEncoderA_GpioPort;
	uint16_t __RotaryEncoderA_Pin;
	GPIO_TypeDef* __RotaryEncoderB_GpioPort;
	uint16_t __RotaryEncoderB_Pin;
	GPIO_TypeDef* __RotaryEncoderZ_GpioPort;
	uint16_t __RotaryEncoderZ_Pin;

	TIM_HandleTypeDef *__MesureTime_TIM;
}_ROTARY_ENCODER_SETTING;

typedef struct{
	uint16_t _RotaryEncoder_1CycleTimePeriodCount;
	bool _isSuccessGet1CycleTimePerioCount;
}_ROTARY_ENCODER_RESULT;

void _RotaryEncoderInit(_ROTARY_ENCODER_SETTING *);

_ROTARY_ENCODER_RESULT _RotaryEncoder_Get1Cycle_TimePeriod();

#endif /* INC_D_M_005_ROTARYENCODER_H_ */
