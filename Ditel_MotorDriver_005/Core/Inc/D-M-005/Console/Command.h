/*
 * Command.h
 *
 *  Created on: Dec 20, 2024
 *      Author: Suyam
 */

#ifndef INC_D_M_005_CONSOLE_COMMAND_H_
#define INC_D_M_005_CONSOLE_COMMAND_H_

#include "stm32f3xx_hal.h"
#include "stdbool.h"
#include "stdlib.h"

#define _CONSOLE_COMMAND_AND_MODE_STRING_MAX_LENGTH 32
#define _CONSOLE_MODE_MAX_NUM 32
#define _CONSOLE_ARGUMENT_MAX_NUM 5

typedef enum{
	_CONSOLE_COMMAND_MOTOR = 0,
	_CONSOLE_COMMAND_PID
}__CONSOLE_COMMAND;

typedef enum{
	_CONSOLE_NONE_MODE = -1,

	_CONSOLE_MOTOR_MODE_NEUTRAL = 0,
	_CONSOLE_MOTOR_MODE_BRAKE,
	_CONSOLE_MOTOR_MODE_FORWARD,
	_CONSOLE_MOTOR_MODE_BACKWARD,
	_CONSOLE_MOTOR_MODE_CHECK,
	_CONSOLE_MOTOR_MODE_MAX_NUM,

	_CONSOLE_PID_MODE_SET = 0,
	_CONSOLE_PID_MODE_CHECK,
	_CONSOLE_PID_MODE_MAX_NUM
}__CONSOLE_MODE;

typedef struct{
	__CONSOLE_COMMAND _command;
	char _commandString[_CONSOLE_COMMAND_AND_MODE_STRING_MAX_LENGTH];

	char _modeString[_CONSOLE_MODE_MAX_NUM][_CONSOLE_COMMAND_AND_MODE_STRING_MAX_LENGTH];
}_CONSOLE_COMMAND;

typedef struct{
	__CONSOLE_COMMAND _command;
	__CONSOLE_MODE _mode;
	uint16_t _argument;
}_CONSOLE_COMMAND_RESULT;

void _CommandInit();
bool _CommandCollation(char *, _CONSOLE_COMMAND_RESULT *);

#endif /* INC_D_M_005_CONSOLE_COMMAND_H_ */
