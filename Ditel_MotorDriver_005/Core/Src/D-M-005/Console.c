/*
 * Console.c
 *
 *  Created on: Dec 17, 2024
 *      Author: Suyam
 */


#include "D-M-005/Console.h"

_CONSOLE_SETTING _ConsoleSetting;

void _ConsoleInit(_CONSOLE_SETTING *__ConsoleSetting){
	_ConsoleSetting.__PcUart = __ConsoleSetting->__PcUart;
}
