/*
 * RotaryEncoders.c
 *
 *  Created on: Dec 28, 2024
 *      Author: Suyam
 */


#include "D-M-005/RotaryEncoder.h"

_ROTARY_ENCODER_SETTING _RotaryEncoderSetting;

void _RotaryEncoderInit(_ROTARY_ENCODER_SETTING *__RotaryEncoderSetting){
	_RotaryEncoderSetting.__RotaryEncoderA_GpioPort = __RotaryEncoderSetting->__RotaryEncoderA_GpioPort;
	_RotaryEncoderSetting.__RotaryEncoderA_Pin = __RotaryEncoderSetting->__RotaryEncoderA_Pin;
	_RotaryEncoderSetting.__RotaryEncoderB_GpioPort = __RotaryEncoderSetting->__RotaryEncoderB_GpioPort;
	_RotaryEncoderSetting.__RotaryEncoderB_Pin = __RotaryEncoderSetting->__RotaryEncoderB_Pin;
	_RotaryEncoderSetting.__RotaryEncoderZ_GpioPort = __RotaryEncoderSetting->__RotaryEncoderZ_GpioPort;
	_RotaryEncoderSetting.__RotaryEncoderZ_Pin = __RotaryEncoderSetting->__RotaryEncoderZ_Pin;

	_RotaryEncoderSetting.__MesureTime_TIM = __RotaryEncoderSetting->__MesureTime_TIM;
}

_ROTARY_ENCODER_RESULT _RotaryEncoder_Get1CyclePulse(){
	GPIO_PinState __RotaryEncoderGpioPinNowStauts, __RotaryEncoderGpioPinLastStauts;
	_ROTARY_ENCODER_RESULT __RotaryEncoderResult;
	__HAL_TIM_SET_COUNTER(_RotaryEncoderSetting.__MesureTime_TIM, 0);
	__RotaryEncoderResult._RotaryEncoder_PulseCount = 0;
	__RotaryEncoderResult._RotaryEncoder_SampleCount = 0;

	while(__HAL_TIM_GET_COUNTER(_RotaryEncoderSetting.__MesureTime_TIM) < __ROTARY_ENCODER_MESURE_1CYCLE_TIME){
		__RotaryEncoderGpioPinNowStauts = HAL_GPIO_ReadPin(_RotaryEncoderSetting.__RotaryEncoderZ_GpioPort, _RotaryEncoderSetting.__RotaryEncoderZ_Pin);

		if((__RotaryEncoderGpioPinNowStauts == GPIO_PIN_SET) && (__RotaryEncoderGpioPinLastStauts == GPIO_PIN_RESET))
			__RotaryEncoderResult._RotaryEncoder_PulseCount++;
		__RotaryEncoderGpioPinLastStauts = __RotaryEncoderGpioPinNowStauts;

		__RotaryEncoderResult._RotaryEncoder_SampleCount++;
	}

	return __RotaryEncoderResult;
}
