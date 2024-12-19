/*
 * Ditel_Printf.h
 *
 *  Created on: Sep 22, 2024
 *      Author: Suyam
 */

#include "stdio.h"
#include "stdarg.h"
#include "string.h"
#include "stm32f3xx.h"

#ifndef INC_DITEL_PRINTF_H_
#define INC_DITEL_PRINTF_H_

void DprintfInit(UART_HandleTypeDef *);
void Dprintf(char* , ...);

#endif /* INC_DITEL_PRINTF_H_ */
