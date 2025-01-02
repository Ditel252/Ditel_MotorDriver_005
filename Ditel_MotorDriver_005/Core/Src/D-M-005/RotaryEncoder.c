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

//Hard coding for faster processing
_ROTARY_ENCODER_RESULT _RotaryEncoder_Get1Cycle_TimePeriod(){
	_ROTARY_ENCODER_RESULT _result;

	__HAL_TIM_SET_COUNTER(_RotaryEncoderSetting.__MesureTime_TIM, 0);

	while((GPIOA -> IDR & 0b100000)){
		if(TIM1->CNT > __ROTARY_ENCODER_HARF_CYCLE_MAX_TIMER_COUNT){
			_result._isSuccessGet1CycleTimePerioCount = false;
			return _result;
		}
	}

	while(!(GPIOA -> IDR & 0b100000)){
		if(TIM1->CNT > __ROTARY_ENCODER_HARF_CYCLE_MAX_TIMER_COUNT){
			_result._isSuccessGet1CycleTimePerioCount = false;
			return _result;
		}
	}

	__HAL_TIM_SET_COUNTER(_RotaryEncoderSetting.__MesureTime_TIM, 0);

	while((GPIOA -> IDR & 0b100000)){
		if(TIM1->CNT > __ROTARY_ENCODER_HARF_CYCLE_MAX_TIMER_COUNT){
			_result._isSuccessGet1CycleTimePerioCount = false;
			return _result;
		}
	}

	while(!(GPIOA -> IDR & 0b100000)){
		if(TIM1->CNT > __ROTARY_ENCODER_HARF_CYCLE_MAX_TIMER_COUNT){
			_result._isSuccessGet1CycleTimePerioCount = false;
			return _result;
		}
	}

	_result._RotaryEncoder_1CycleTimePeriodCount = TIM1->CNT;
	_result._isSuccessGet1CycleTimePerioCount = true;

	return _result;
}
