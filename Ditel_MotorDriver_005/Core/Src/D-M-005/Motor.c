/*
 * Motor.c
 *
 *  Created on: Dec 14, 2024
 *      Author: Suyam
 */


#include "D-M-005/Motor.h"

_MOTOR_SETTING _MotorSetting;


void _MotorInit(_MOTOR_SETTING *__MotorSetting){
	_MotorSetting.__MotorN1_Tim = __MotorSetting->__MotorN1_Tim;
	_MotorSetting.__MotorN1_TimChannel = __MotorSetting->__MotorN1_TimChannel;
	_MotorSetting.__MotorN2_Tim = __MotorSetting->__MotorN2_Tim;
	_MotorSetting.__MotorN2_TimChannel = __MotorSetting->__MotorN2_TimChannel;

	_MotorSetting.__MotorP1_GpioPort = __MotorSetting->__MotorP1_GpioPort;
	_MotorSetting.__MotorP1_Pin = __MotorSetting->__MotorP1_Pin;
	_MotorSetting.__MotorP2_GpioPort = __MotorSetting->__MotorP2_GpioPort;
	_MotorSetting.__MotorP2_Pin = __MotorSetting->__MotorP2_Pin;

	HAL_GPIO_WritePin(_MotorSetting.__MotorP1_GpioPort, _MotorSetting.__MotorP1_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(_MotorSetting.__MotorP2_GpioPort, _MotorSetting.__MotorP2_Pin, GPIO_PIN_RESET);

	HAL_TIM_PWM_Start(_MotorSetting.__MotorN1_Tim, _MotorSetting.__MotorN1_TimChannel);
	HAL_TIM_PWM_Start(_MotorSetting.__MotorN2_Tim, _MotorSetting.__MotorN2_TimChannel);

	__HAL_TIM_SET_COMPARE(_MotorSetting.__MotorN1_Tim, _MotorSetting.__MotorN1_TimChannel, 0);
	__HAL_TIM_SET_COMPARE(_MotorSetting.__MotorN2_Tim, _MotorSetting.__MotorN2_TimChannel, 0);
}
