/*
 * SW.h
 *
 *  Created on: Dec 16, 2024
 *      Author: Suyam
 */

#ifndef INC_D_M_005_SWITCH_H_
#define INC_D_M_005_SWITCH_H_

#include "stm32f3xx_hal.h"

#define _SWITCH_OPERATION_MODE_NORMAL		0x00
#define _SWITCH_OPERATION_MODE_PC_CONSOLE	0x01
#define _SWITCH_COMMUNICATION_MODE_CAN		0x00
#define _SWITCH_COMMUNICATION_MODE_UART		0x01

#define __SWITCH_BIT_ADDRESS_1ST_DIGIT	3
#define __SWITCH_BIT_ADDRESS_2ND_DIGIT  	2
#define __SWITCH_BIT_ADDRESS_3ND_DIGIT  	1
#define __SWITCH_BIT_ADDRESS_4TH_DIGIT  	0
#define __SWITCH_BIT_OPERATION_MODE   	6
#define __SWITCH_BIT_COMMUNICATION_MODE	7


typedef struct{
	GPIO_TypeDef* __ShiftRegisterClk_GpioPort;
	uint16_t __ShiftRegisterClk_Pin;
	GPIO_TypeDef* __ShiftRegisterShLd_GpioPort;
	uint16_t __ShiftRegisterShLd_Pin;
	GPIO_TypeDef* __ShiftRegisterQh_GpioPort;
	uint16_t __ShiftRegisterQh_Pin;
}_SWITCH_SETTING;

typedef struct{
	uint8_t _Address;
	uint8_t _OperatingMode;
	uint8_t _CommunicationMode;
}_SWITCH_READ_DATA;

void _SwitchInit(_SWITCH_SETTING *);
void _SwitchRead(_SWITCH_READ_DATA *);

#endif /* INC_D_M_005_SWITCH_H_ */
