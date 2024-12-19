/*
 * Ditel_Printf.c
 *
 *  Created on: Sep 22, 2024
 *      Author: Suyam
 */

#include "D-M-005/Console/Ditel_Printf.h"

UART_HandleTypeDef *_DprintfUart;

void DprintfInit(UART_HandleTypeDef *hurat){
	_DprintfUart = hurat;
}

void Dprintf(char* str, ...)
{
    char resultString[128] = {0}, argString_In[32] = {0}, argString_Out[32] = {0};

    va_list ap;
    va_start(ap, str);

    unsigned short int count_In = 0, count_Out = 0, count_Arg = 0;

    while(str[count_In] != '\0'){
        if(str[count_In] == '%'){
            count_In++;
            count_Arg = 0;

            argString_In[count_Arg] = '%';
            count_Arg++;

            unsigned short int isArg = 1U;

            while(1){
                if(str[count_In] == 'd'| str[count_In] == 's'| str[count_In] == 'u' | str[count_In] == 'f'){
                    argString_In[count_Arg] = str[count_In];
                    break;
                }else if(str[count_In] == '%'){
                    resultString[count_Out] = '%';
                    count_Out++;
                    count_In++;
                    isArg = 0U;
                    break;
                }else if(str[count_In] == '\0'){
                    return;
                }else{
                    argString_In[count_Arg] = str[count_In];
                    count_Arg++;
                    count_In++;
                }
            }

            if(isArg){
                count_Arg++;
                argString_In[count_Arg] = '\0';

                switch(str[count_In]){
                case 'd':
                    sprintf(argString_Out, argString_In, va_arg(ap, int));
                    break;
                case 's':
                    sprintf(argString_Out, argString_In, va_arg(ap, char*));
                    break;
                case 'u':
                    sprintf(argString_Out, argString_In, va_arg(ap, unsigned int));
                    break;
                case 'f':
                    sprintf(argString_Out, argString_In, va_arg(ap, double));
                    break;
                }

                strcat(resultString, argString_Out);

                count_Out += strlen(argString_Out);
                count_In++;
            }
        }else{
            resultString[count_Out] = str[count_In];

            count_In++;
            count_Out++;
        }
    }

    va_end(ap);

    HAL_UART_Transmit(_DprintfUart, (uint8_t *)resultString, strlen(resultString), 300);
}
