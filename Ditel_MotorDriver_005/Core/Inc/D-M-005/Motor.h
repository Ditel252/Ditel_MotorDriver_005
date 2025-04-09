/*
 * Motor.h
 *
 *  Created on: Dec 14, 2024
 *      Author: Suyam
 */

#ifndef INC_D_M_005_MOTOR_H_
#define INC_D_M_005_MOTOR_H_

#include "stm32f3xx_hal.h"

typedef enum{
	_MOTOR_MODE_NEUTRAL = 0x00,
	_MOTOR_MODE_BREAK	= 0x01,
	_MOTOR_MODE_FORWARD	= 0x02,
	_MOTOR_MODE_REVARCE	= 0x03
}__MOTOR_MODE;

//#define __MOTOR_DEAD_TIME ((uint16_t)((float)800 * 1.5))	//[us]
#define __MOTOR_DEAD_TIME 10	//[ms]

#define __MOTOR_MAX_SPEED	60000

typedef struct{
	TIM_HandleTypeDef *__MotorP1_Tim;
	uint32_t __MotorP1_TimChannel;
	TIM_HandleTypeDef *__MotorP2_Tim;
	uint32_t __MotorP2_TimChannel;

	GPIO_TypeDef* __MotorN1_GpioPort;
	uint16_t __MotorN1_Pin;
	GPIO_TypeDef* __MotorN2_GpioPort;
	uint16_t __MotorN2_Pin;

	TIM_HandleTypeDef *__DeadTime_TIM;
}_MOTOR_SETTING;

void _MotorInit(_MOTOR_SETTING *);

void _MotorSetSpeed(__MOTOR_MODE, uint16_t);

void __Delay_Microseconds(uint16_t);

#endif /* INC_D_M_005_MOTOR_H_ */
