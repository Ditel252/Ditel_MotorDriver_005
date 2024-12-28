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

#define __ROTARY_ENCODER_MESURETIME_MAX_TIME ((uint8_t)((float)(0xFFFF - 1) * 0.8))
#define __ROTARY_ENCODER_TIME_COUNT_TO_ANGULAR_VELOCITY(x) ((60 * 1000 * 1000) / (x))

typedef struct{
	GPIO_TypeDef* __RotaryEncoderA_GpioPort;
	uint16_t __RotaryEncoderA_Pin;
	GPIO_TypeDef* __RotaryEncoderB_GpioPort;
	uint16_t __RotaryEncoderB_Pin;
	GPIO_TypeDef* __RotaryEncoderZ_GpioPort;
	uint16_t __RotaryEncoderZ_Pin;

	TIM_HandleTypeDef *__MesureTime_TIM;
}_ROTARY_ENCODER_SETTING;

void _RotaryEncoderInit(_ROTARY_ENCODER_SETTING *);

unsigned int _RotaryEncoder_MesureAngularVelocity();

void _RotaryEncoder_ResetAngularVelocity();

#endif /* INC_D_M_005_ROTARYENCODER_H_ */
