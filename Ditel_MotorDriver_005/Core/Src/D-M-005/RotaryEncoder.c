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

_ROTARY_ENCODER_RESULT _RotaryEncoder_Get1Cycle_TimePeriod(){
	_ROTARY_ENCODER_RESULT _result;

	__HAL_TIM_SET_COUNTER(_RotaryEncoderSetting.__MesureTime_TIM, 0);

	while(HAL_GPIO_ReadPin(_RotaryEncoderSetting.__RotaryEncoderZ_GpioPort, _RotaryEncoderSetting.__RotaryEncoderZ_Pin) == GPIO_PIN_SET){
		if(__HAL_TIM_GET_COUNTER(_RotaryEncoderSetting.__MesureTime_TIM) > __ROTARY_ENCODER_HARF_CYCLE_MAX_TIMER_COUNT){
			_result._isSuccessGet1CycleTimePerioCount = false;
			return _result;
		}
	}

	while(HAL_GPIO_ReadPin(_RotaryEncoderSetting.__RotaryEncoderZ_GpioPort, _RotaryEncoderSetting.__RotaryEncoderZ_Pin) == GPIO_PIN_RESET){
		if(__HAL_TIM_GET_COUNTER(_RotaryEncoderSetting.__MesureTime_TIM) > __ROTARY_ENCODER_HARF_CYCLE_MAX_TIMER_COUNT){
			_result._isSuccessGet1CycleTimePerioCount = false;
			return _result;
		}
	}

	__HAL_TIM_SET_COUNTER(_RotaryEncoderSetting.__MesureTime_TIM, 0);

	while(HAL_GPIO_ReadPin(_RotaryEncoderSetting.__RotaryEncoderZ_GpioPort, _RotaryEncoderSetting.__RotaryEncoderZ_Pin) == GPIO_PIN_SET){
		if(__HAL_TIM_GET_COUNTER(_RotaryEncoderSetting.__MesureTime_TIM) > __ROTARY_ENCODER_HARF_CYCLE_MAX_TIMER_COUNT){
			_result._isSuccessGet1CycleTimePerioCount = false;
			return _result;
		}
	}

	while(HAL_GPIO_ReadPin(_RotaryEncoderSetting.__RotaryEncoderZ_GpioPort, _RotaryEncoderSetting.__RotaryEncoderZ_Pin) == GPIO_PIN_RESET){
		if(__HAL_TIM_GET_COUNTER(_RotaryEncoderSetting.__MesureTime_TIM) > __ROTARY_ENCODER_HARF_CYCLE_MAX_TIMER_COUNT){
			_result._isSuccessGet1CycleTimePerioCount = false;
			return _result;
		}
	}

	_result._RotaryEncoder_1CycleTimePeriodCount = __HAL_TIM_GET_COUNTER(_RotaryEncoderSetting.__MesureTime_TIM);
	_result._isSuccessGet1CycleTimePerioCount = true;

	return _result;
}
