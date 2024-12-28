/*
 * RotaryEncoders.c
 *
 *  Created on: Dec 28, 2024
 *      Author: Suyam
 */


#include "D-M-005/RotaryEncoder.h"

_ROTARY_ENCODER_SETTING _RotaryEncoderSetting;

uint64_t __RotaryEncoderMesureTimeCounter = 0;

GPIO_PinState __RotaryEncoderGpioPinNowStauts, __RotaryEncoderGpioPinLastStauts;
bool __RotaryEncoderGpioPin_ThisIsFirstTime = true;
unsigned int __RotaryEncoder_AngularVelocity = 0;

void _RotaryEncoderInit(_ROTARY_ENCODER_SETTING *__RotaryEncoderSetting){
	_RotaryEncoderSetting.__RotaryEncoderA_GpioPort = __RotaryEncoderSetting->__RotaryEncoderA_GpioPort;
	_RotaryEncoderSetting.__RotaryEncoderA_Pin = __RotaryEncoderSetting->__RotaryEncoderA_Pin;
	_RotaryEncoderSetting.__RotaryEncoderB_GpioPort = __RotaryEncoderSetting->__RotaryEncoderB_GpioPort;
	_RotaryEncoderSetting.__RotaryEncoderB_Pin = __RotaryEncoderSetting->__RotaryEncoderB_Pin;
	_RotaryEncoderSetting.__RotaryEncoderZ_GpioPort = __RotaryEncoderSetting->__RotaryEncoderZ_GpioPort;
	_RotaryEncoderSetting.__RotaryEncoderZ_Pin = __RotaryEncoderSetting->__RotaryEncoderZ_Pin;

	_RotaryEncoderSetting.__MesureTime_TIM = __RotaryEncoderSetting->__MesureTime_TIM;
}

unsigned int _RotaryEncoder_MesureAngularVelocity(){
	if(__HAL_TIM_GET_COUNTER(_RotaryEncoderSetting.__MesureTime_TIM) > __ROTARY_ENCODER_MESURETIME_MAX_TIME){
		__RotaryEncoderMesureTimeCounter += __HAL_TIM_GET_COUNTER(_RotaryEncoderSetting.__MesureTime_TIM);
		__HAL_TIM_SET_COUNTER(_RotaryEncoderSetting.__MesureTime_TIM, 0);
	}

	__RotaryEncoderGpioPinNowStauts = HAL_GPIO_ReadPin(_RotaryEncoderSetting.__RotaryEncoderZ_GpioPort, _RotaryEncoderSetting.__RotaryEncoderZ_Pin);

	if((__RotaryEncoderGpioPinNowStauts == GPIO_PIN_SET) && (__RotaryEncoderGpioPinLastStauts == GPIO_PIN_RESET)){
		if(!__RotaryEncoderGpioPin_ThisIsFirstTime){
			__RotaryEncoderMesureTimeCounter += __HAL_TIM_GET_COUNTER(_RotaryEncoderSetting.__MesureTime_TIM);
			__HAL_TIM_SET_COUNTER(_RotaryEncoderSetting.__MesureTime_TIM, 0);
//			__RotaryEncoder_AngularVelocity = (double)(__ROTARY_ENCODER_TIME_COUNT_TO_ANGULAR_VELOCITY(__RotaryEncoderMesureTimeCounter));
			__RotaryEncoder_AngularVelocity = (__RotaryEncoderMesureTimeCounter);
			__RotaryEncoderMesureTimeCounter = 0;
		}else{
			__HAL_TIM_SET_COUNTER(_RotaryEncoderSetting.__MesureTime_TIM, 0);
			__RotaryEncoderMesureTimeCounter = 0;
			__RotaryEncoderGpioPin_ThisIsFirstTime = false;
		}
	}

	__RotaryEncoderGpioPinLastStauts = __RotaryEncoderGpioPinNowStauts;

	return __RotaryEncoder_AngularVelocity;
}
