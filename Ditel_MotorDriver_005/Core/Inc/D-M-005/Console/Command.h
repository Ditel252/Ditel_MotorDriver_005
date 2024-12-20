/*
 * Command.h
 *
 *  Created on: Dec 20, 2024
 *      Author: Suyam
 */

#ifndef INC_D_M_005_CONSOLE_COMMAND_H_
#define INC_D_M_005_CONSOLE_COMMAND_H_

#include "stm32f3xx_hal.h"

#define _CONSOLE_COMMAND_AND_MODE_STRING_MAX_LENGTH 32
#define _CONSOLE_MODE_MAX_NUM 32

typedef enum{
	_CONSOLE_COMMAND_MOTOR = 0,
	_CONSOLE_COMMAND_PID
}__CONSOLE_COMMAND;

typedef enum{
	_CONSOLE_MOTOR_MODE_NEUTRAL = 0,
	_CONSOLE_MOTOR_MODE_BRAKE,
	_CONSOLE_MOTOR_MODE_FORWARD,
	_CONSOLE_MOTOR_MODE_BACKWARD
}__CONSOLE_MOTOR_MODE;

typedef struct{
	_CONSOLE_COMMAND _command;
	char _commandString[_CONSOLE_COMMAND_AND_MODE_STRING_MAX_LENGTH];

	__CONSOLE_MOTOR_MODE _mode;
	char _modeString[_CONSOLE_MODE_MAX_NUM][_CONSOLE_COMMAND_AND_MODE_STRING_MAX_LENGTH];
}_CONSOLE_COMMAND;

#endif /* INC_D_M_005_CONSOLE_COMMAND_H_ */
