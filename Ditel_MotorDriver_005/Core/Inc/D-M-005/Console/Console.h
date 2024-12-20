/*
 * Console.h
 *
 *  Created on: Dec 17, 2024
 *      Author: Suyam
 */

#ifndef INC_D_M_005_CONSOLE_H_
#define INC_D_M_005_CONSOLE_H_

#include "stm32f3xx_hal.h"
#include "Ditel_Printf.h"

#define __CONSOLE_STRING_LENGTH 128
extern char _ConsoleReadString[__CONSOLE_STRING_LENGTH];

typedef struct{
	UART_HandleTypeDef *__PcUart;
}_CONSOLE_SETTING;

void _ConsoleInit(_CONSOLE_SETTING *);

void _ConsoleStartLogo();

void _ConsoleCommandRead();

#endif /* INC_D_M_005_CONSOLE_H_ */
