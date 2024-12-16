/*
 * Swtich.c
 *
 *  Created on: Dec 16, 2024
 *      Author: Suyam
 */


#include "D-M-005/Switch.h"

_SWITCH_SETTING _SwitchSetting;

void _SwitchInit(_SWITCH_SETTING *__SwitchSetting){
	_SwitchSetting.__ShiftRegisterClk_GpioPort = __SwitchSetting->__ShiftRegisterClk_GpioPort;
	_SwitchSetting.__ShiftRegisterClk_Pin = __SwitchSetting->__ShiftRegisterClk_Pin;
	_SwitchSetting.__ShiftRegisterQh_GpioPort = __SwitchSetting->__ShiftRegisterQh_GpioPort;
	_SwitchSetting.__ShiftRegisterQh_Pin = __SwitchSetting->__ShiftRegisterQh_Pin;
	_SwitchSetting.__ShiftRegisterShLd_GpioPort = __SwitchSetting->__ShiftRegisterShLd_GpioPort;
	_SwitchSetting.__ShiftRegisterShLd_Pin = __SwitchSetting->__ShiftRegisterShLd_Pin;

	HAL_GPIO_WritePin(_SwitchSetting.__ShiftRegisterClk_GpioPort, _SwitchSetting.__ShiftRegisterClk_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(_SwitchSetting.__ShiftRegisterShLd_GpioPort, _SwitchSetting.__ShiftRegisterShLd_Pin, GPIO_PIN_RESET);
}

void _SwitchRead(_SWITCH_READ_DATA *__SwitchReadData){
	uint8_t _readSwData = 0;

	HAL_GPIO_WritePin(_SwitchSetting.__ShiftRegisterShLd_GpioPort, _SwitchSetting.__ShiftRegisterShLd_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(_SwitchSetting.__ShiftRegisterClk_GpioPort, _SwitchSetting.__ShiftRegisterClk_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(_SwitchSetting.__ShiftRegisterClk_GpioPort, _SwitchSetting.__ShiftRegisterClk_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(_SwitchSetting.__ShiftRegisterShLd_GpioPort, _SwitchSetting.__ShiftRegisterShLd_Pin, GPIO_PIN_SET);

	_readSwData = _readSwData | (HAL_GPIO_ReadPin(_SwitchSetting.__ShiftRegisterQh_GpioPort, _SwitchSetting.__ShiftRegisterQh_Pin) << 7);
	for(int i = 6; i >= 0; i--){
		HAL_GPIO_WritePin(_SwitchSetting.__ShiftRegisterClk_GpioPort, _SwitchSetting.__ShiftRegisterClk_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(_SwitchSetting.__ShiftRegisterClk_GpioPort, _SwitchSetting.__ShiftRegisterClk_Pin, GPIO_PIN_RESET);

		_readSwData = _readSwData | (HAL_GPIO_ReadPin(_SwitchSetting.__ShiftRegisterQh_GpioPort, _SwitchSetting.__ShiftRegisterQh_Pin) << i);
	}

	__SwitchReadData->_Address = 0;
	__SwitchReadData->_Address |= (!!(_readSwData & (1U << __SWITCH_BIT_ADDRESS_4TH_DIGIT))) << 3;
	__SwitchReadData->_Address |= (!!(_readSwData & (1U << __SWITCH_BIT_ADDRESS_3ND_DIGIT))) << 2;
	__SwitchReadData->_Address |= (!!(_readSwData & (1U << __SWITCH_BIT_ADDRESS_2ND_DIGIT))) << 1;
	__SwitchReadData->_Address |= (!!(_readSwData & (1U << __SWITCH_BIT_ADDRESS_1ST_DIGIT))) << 0;

	if(!!!(_readSwData & (1U << __SWITCH_BIT_OPERATION_MODE)))
		__SwitchReadData->_OperatingMode = _SWITCH_OPERATION_MODE_NORMAL;
	else
		__SwitchReadData->_OperatingMode = _SWITCH_OPERATION_MODE_PC_CONSOLE;

	if(!!(_readSwData & (1U << __SWITCH_BIT_COMMUNICATION_MODE)))
		__SwitchReadData->_CommunicationMode = _SWITCH_COMMUNICATION_MODE_CAN;
	else
		__SwitchReadData->_CommunicationMode = _SWITCH_COMMUNICATION_MODE_UART;
}
