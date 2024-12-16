/*
 * D-M-005_7SEG.h
 *
 *  Created on: Dec 13, 2024
 *      Author: Suyam
 */

#ifndef INC_7SEG_H_
#define INC_7SEG_H_

#include "stm32f3xx_hal.h"
#include "stdbool.h"

//									pcdegfab
#define __7SEG_NULL_1Byte		~(0b00000000)
#define __7SEG_ONLY_A_1Byte 	~(0b00000010)
#define __7SEG_ONLY_B_1Byte 	~(0b00000001)
#define __7SEG_ONLY_C_1Byte 	~(0b01000000)
#define __7SEG_ONLY_D_1Byte 	~(0b00100000)
#define __7SEG_ONLY_E_1Byte 	~(0b00010000)
#define __7SEG_ONLY_F_1Byte 	~(0b00000100)
#define __7SEG_ONLY_G_1Byte 	~(0b00001000)
#define __7SEG_ONLY_DP_1Byte	~(0b10000000)

typedef enum{
	_SETUP_STEP_START_PROGRAM = 1,
	_SETUP_STEP_SETUP_MOTOR = 2,
	_SETUP_STEP_SETUP_AND_READ_SWICH = 3,
	_SETUP_STEP_NULL2 = 4,
	_SETUP_STEP_NULL3 = 5,
	_SETUP_STEP_NULL4 = 6,
	_SETUP_STEP_NULL5 = 7,
	_SETUP_STEP_NULL6 = 8,
	_SETUP_STEP_FINISH = 9
}_SETUP_STEP_FOR_7SEG;

typedef struct{
	GPIO_TypeDef* __7SegSi_GpioPort;
	uint16_t __7SegSi_Pin;
	GPIO_TypeDef* __7SegRck_GpioPort;
	uint16_t __7SegRck_Pin;
	GPIO_TypeDef* __7SegSck_GpioPort;
	uint16_t __7SegSck_Pin;
}_7SEG_SETTING;

void _7SegInit(_7SEG_SETTING *);
void _7SegDisplay(uint8_t , bool);
void _7SegReset();
void _7SegSetUpAnimation(_SETUP_STEP_FOR_7SEG);


#endif /* INC_7SEG_H_ */
