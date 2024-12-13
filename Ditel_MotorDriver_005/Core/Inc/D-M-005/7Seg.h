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


#endif /* INC_7SEG_H_ */
