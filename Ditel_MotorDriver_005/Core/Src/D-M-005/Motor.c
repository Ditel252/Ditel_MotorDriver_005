/*
 * Motor.c
 *
 *  Created on: Dec 14, 2024
 *      Author: Suyam
 */


#include "D-M-005/Motor.h"

_MOTOR_SETTING _MotorSetting;

void _MotorInit(_MOTOR_SETTING *__MotorSetting){
	_MotorSetting.__MotorP1_Tim = __MotorSetting->__MotorP1_Tim;
	_MotorSetting.__MotorP1_TimChannel = __MotorSetting->__MotorP1_TimChannel;
	_MotorSetting.__MotorP2_Tim = __MotorSetting->__MotorP2_Tim;
	_MotorSetting.__MotorP2_TimChannel = __MotorSetting->__MotorP2_TimChannel;

	_MotorSetting.__MotorN1_GpioPort = __MotorSetting->__MotorN1_GpioPort;
	_MotorSetting.__MotorN1_Pin = __MotorSetting->__MotorN1_Pin;
	_MotorSetting.__MotorN2_GpioPort = __MotorSetting->__MotorN2_GpioPort;
	_MotorSetting.__MotorN2_Pin = __MotorSetting->__MotorN2_Pin;

	_MotorSetting.__DeadTime_TIM = __MotorSetting->__DeadTime_TIM;

	HAL_GPIO_WritePin(_MotorSetting.__MotorN1_GpioPort, _MotorSetting.__MotorN1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(_MotorSetting.__MotorN2_GpioPort, _MotorSetting.__MotorN2_Pin, GPIO_PIN_RESET);

	HAL_TIM_PWM_Start(_MotorSetting.__MotorP1_Tim, _MotorSetting.__MotorP1_TimChannel);
	HAL_TIM_PWM_Start(_MotorSetting.__MotorP2_Tim, _MotorSetting.__MotorP2_TimChannel);

	HAL_TIM_Base_Start(_MotorSetting.__DeadTime_TIM);

	__HAL_TIM_SET_COMPARE(_MotorSetting.__MotorP1_Tim, _MotorSetting.__MotorP1_TimChannel, 0);
	__HAL_TIM_SET_COMPARE(_MotorSetting.__MotorP2_Tim, _MotorSetting.__MotorP2_TimChannel, 0);
}

uint8_t _lastMode;
void _MotorSetSpeed(__MOTOR_MODE _mode, uint16_t _speed){
	if((_mode != _MOTOR_MODE_NEUTRAL) && (_mode != _lastMode)){
		//NEUTRAL
		__HAL_TIM_SET_COMPARE(_MotorSetting.__MotorP1_Tim, _MotorSetting.__MotorP1_TimChannel, 0);
		HAL_GPIO_WritePin(_MotorSetting.__MotorN2_GpioPort, _MotorSetting.__MotorN2_Pin, GPIO_PIN_RESET);
		__HAL_TIM_SET_COMPARE(_MotorSetting.__MotorP2_Tim, _MotorSetting.__MotorP2_TimChannel, 0);
		HAL_GPIO_WritePin(_MotorSetting.__MotorN1_GpioPort, _MotorSetting.__MotorN1_Pin, GPIO_PIN_RESET);

//		__Delay_Microseconds(__MOTOR_DEAD_TIME);
		HAL_Delay(__MOTOR_DEAD_TIME);
	}

	switch(_mode){
	case _MOTOR_MODE_NEUTRAL:
		__HAL_TIM_SET_COMPARE(_MotorSetting.__MotorP1_Tim, _MotorSetting.__MotorP1_TimChannel, 0);
		HAL_GPIO_WritePin(_MotorSetting.__MotorN2_GpioPort, _MotorSetting.__MotorN2_Pin, GPIO_PIN_RESET);

		__HAL_TIM_SET_COMPARE(_MotorSetting.__MotorP2_Tim, _MotorSetting.__MotorP2_TimChannel, 0);
		HAL_GPIO_WritePin(_MotorSetting.__MotorN1_GpioPort, _MotorSetting.__MotorN1_Pin, GPIO_PIN_RESET);
		break;
	case _MOTOR_MODE_BREAK:
		__HAL_TIM_SET_COMPARE(_MotorSetting.__MotorP1_Tim, _MotorSetting.__MotorP1_TimChannel, 0);
		HAL_GPIO_WritePin(_MotorSetting.__MotorN2_GpioPort, _MotorSetting.__MotorN2_Pin, GPIO_PIN_SET);

		__HAL_TIM_SET_COMPARE(_MotorSetting.__MotorP2_Tim, _MotorSetting.__MotorP2_TimChannel, 0);
		HAL_GPIO_WritePin(_MotorSetting.__MotorN1_GpioPort, _MotorSetting.__MotorN1_Pin, GPIO_PIN_SET);
		break;
	case _MOTOR_MODE_FORWARD:
		__HAL_TIM_SET_COMPARE(_MotorSetting.__MotorP1_Tim, _MotorSetting.__MotorP1_TimChannel, _speed);
		HAL_GPIO_WritePin(_MotorSetting.__MotorN2_GpioPort, _MotorSetting.__MotorN2_Pin, GPIO_PIN_SET);

		__HAL_TIM_SET_COMPARE(_MotorSetting.__MotorP2_Tim, _MotorSetting.__MotorP2_TimChannel, 0);
		HAL_GPIO_WritePin(_MotorSetting.__MotorN1_GpioPort, _MotorSetting.__MotorN1_Pin, GPIO_PIN_RESET);
		break;
	case _MOTOR_MODE_REVARCE:
		__HAL_TIM_SET_COMPARE(_MotorSetting.__MotorP1_Tim, _MotorSetting.__MotorP1_TimChannel, 0);
		HAL_GPIO_WritePin(_MotorSetting.__MotorN2_GpioPort, _MotorSetting.__MotorN2_Pin, GPIO_PIN_RESET);

		__HAL_TIM_SET_COMPARE(_MotorSetting.__MotorP2_Tim, _MotorSetting.__MotorP2_TimChannel, _speed);
		HAL_GPIO_WritePin(_MotorSetting.__MotorN1_GpioPort, _MotorSetting.__MotorN1_Pin, GPIO_PIN_SET);
		break;
	}

	_lastMode = _mode;
}

void __Delay_Microseconds(uint16_t _us){
	__HAL_TIM_SET_COUNTER(_MotorSetting.__DeadTime_TIM, 0);

	while(__HAL_TIM_GET_COUNTER(_MotorSetting.__DeadTime_TIM) < _us)
			;
}
