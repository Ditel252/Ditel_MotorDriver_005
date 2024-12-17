/*
 * Console.h
 *
 *  Created on: Dec 17, 2024
 *      Author: Suyam
 */

#ifndef INC_D_M_005_CONSOLE_H_
#define INC_D_M_005_CONSOLE_H_

#include "stm32f3xx_hal.h"

#define __CONSOLE_STRING_LENGTH 128

typedef struct{
	UART_HandleTypeDef *__PcUart;
}_CONSOLE_SETTING;

typedef struct{
	char _strEnglish[__CONSOLE_STRING_LENGTH];
	char _strJapanese[__CONSOLE_STRING_LENGTH];
	bool _isJapaneseEnable;
}_consoleString;

enum __CONSOLE_STRING_LANGUAGE{
	_CONSOLE_STRING_LANGUAGE_ENGLISH = 0,
	_CONSOLE_STRING_LANGUAGE_JAPANESE = 1
};

void _ConsoleInit(_CONSOLE_SETTING *);

void _ConsolePrint(_consoleString, __CONSOLE_STRING_LANGUAGE);

#endif /* INC_D_M_005_CONSOLE_H_ */
