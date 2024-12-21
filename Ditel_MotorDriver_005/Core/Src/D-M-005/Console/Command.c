/*
 * Command.c
 *
 *  Created on: Dec 20, 2024
 *      Author: Suyam
 */


#include "D-M-005/Console/Command.h"

_CONSOLE_COMMAND _consoleCommand_motor;
_CONSOLE_COMMAND _consoleCommand_pid;

char testCommandStr[_CONSOLE_COMMAND_AND_MODE_STRING_MAX_LENGTH];
char testModeStr[_CONSOLE_COMMAND_AND_MODE_STRING_MAX_LENGTH];

void _CommandInit(){
	_consoleCommand_motor._command = _CONSOLE_COMMAND_MOTOR;
	strcpy(_consoleCommand_motor._commandString, "motor");
	strcpy(_consoleCommand_motor._modeString[_CONSOLE_MOTOR_MODE_NEUTRAL], "neutral");
	strcpy(_consoleCommand_motor._modeString[_CONSOLE_MOTOR_MODE_BRAKE], "brake");
	strcpy(_consoleCommand_motor._modeString[_CONSOLE_MOTOR_MODE_FORWARD], "forward");
	strcpy(_consoleCommand_motor._modeString[_CONSOLE_MOTOR_MODE_BACKWARD], "backward");
	strcpy(_consoleCommand_motor._modeString[_CONSOLE_MOTOR_MODE_CHECK], "check");

	_consoleCommand_motor._command = _CONSOLE_COMMAND_PID;
	strcpy(_consoleCommand_pid._commandString, "pid");
	strcpy(_consoleCommand_pid._modeString[_CONSOLE_PID_MODE_SET], "set");
	strcpy(_consoleCommand_pid._modeString[_CONSOLE_PID_MODE_CHECK], "check");
}

bool _CommandCollation(char _str[], _CONSOLE_COMMAND_RESULT *_commandResult){
	char _commandString[_CONSOLE_COMMAND_AND_MODE_STRING_MAX_LENGTH];
	char _modeString[_CONSOLE_COMMAND_AND_MODE_STRING_MAX_LENGTH];

	uint8_t _strCount = 0;

	while(1){
		if(_str[_strCount] == ' ' || _str[_strCount] == '\0'){
			_commandString[_strCount] = '\0';
			break;
		}

		_commandString[_strCount] = _str[_strCount];
		_strCount++;
	}

	if(strcmp(_commandString, _consoleCommand_motor._commandString) == 0)
		_commandResult->_command = _CONSOLE_COMMAND_MOTOR;
	else if(strcmp(_commandString, _consoleCommand_pid._commandString) == 0)
		_commandResult->_command = _CONSOLE_COMMAND_PID;
	else
		return false;

	uint8_t _modeStringCount = 0;
	if(_str[_strCount] != '\0'){
		_strCount++;

		while(1){
			if(_str[_strCount] == ' ' || _str[_strCount] == '\0'){
				_modeString[_modeStringCount] = '\0';
				break;
			}

			_modeString[_modeStringCount] = _str[_strCount];
			_modeStringCount++;
			_strCount++;
		}

		if(_commandResult->_command == _CONSOLE_COMMAND_MOTOR){
			__CONSOLE_MODE _consoleModeCount = _CONSOLE_MOTOR_MODE_CHECK;

			while(1){
				if(strcmp(_modeString, _consoleCommand_motor._modeString[_consoleModeCount]) == 0)
					break;

				if(_consoleModeCount <= _CONSOLE_MOTOR_MODE_NEUTRAL)
					return false;
				_consoleModeCount--;
			}

			_commandResult->_mode = _consoleModeCount;

			return true;
		}else if(_commandResult->_command == _CONSOLE_COMMAND_PID){
			__CONSOLE_MODE _consoleModeCount = _CONSOLE_PID_MODE_CHECK;

			while(1){
				if(strcmp(_modeString, _consoleCommand_pid._modeString[_consoleModeCount]) == 0)
					break;

				if(_consoleModeCount <= _CONSOLE_PID_MODE_SET)
					return false;
				_consoleModeCount--;
			}

			_commandResult->_mode = _consoleModeCount;

			return true;
		}else{
			return false;
		}
	}else{
		if(_commandResult->_command == _CONSOLE_COMMAND_MOTOR)
			return false;
		else
			return true;
	}
}
