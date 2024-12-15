/*
 * Motor.h
 *
 *  Created on: Dec 14, 2024
 *      Author: Suyam
 */

#ifndef INC_D_M_005_MOTOR_H_
#define INC_D_M_005_MOTOR_H_

#include "stm32f3xx_hal.h"

#define _MOTOR_MODE_NEUTRAL 0x00
#define _MOTOR_MODE_BREAK	0x01
#define _MOTOR_MODE_FORWARD	0x02
#define _MOTOR_MODE_REVARCE	0x03

#define __MOTOR_DEAD_TIME

#define __MOTOR_MAX_SPEED	60000

typedef struct{
	TIM_HandleTypeDef *__MotorN1_Tim;
	uint32_t __MotorN1_TimChannel;
	TIM_HandleTypeDef *__MotorN2_Tim;
	uint32_t __MotorN2_TimChannel;

	GPIO_TypeDef* __MotorP1_GpioPort;
	uint16_t __MotorP1_Pin;
	GPIO_TypeDef* __MotorP2_GpioPort;
	uint16_t __MotorP2_Pin;

	TIM_HandleTypeDef *__DeadTime_TIM;
}_MOTOR_SETTING;

void _MotorInit(_MOTOR_SETTING *);

void _MotorSetSpeed(uint8_t, uint16_t);

#endif /* INC_D_M_005_MOTOR_H_ */
