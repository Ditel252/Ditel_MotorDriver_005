/*
 * Console.c
 *
 *  Created on: Dec 17, 2024
 *      Author: Suyam
 */


#include "D-M-005/Console/Console.h"

_CONSOLE_SETTING _ConsoleSetting;

_CONSOLE_COMMAND_RESULT _ConsoleCommandResult;

char _ConsoleReadString[__CONSOLE_STRING_LENGTH];

void _ConsoleInit(_CONSOLE_SETTING *__ConsoleSetting){
	_ConsoleSetting.__PcUart = __ConsoleSetting->__PcUart;

	DprintfInit(_ConsoleSetting.__PcUart);
	_CommandInit();
}

void _ConsoleStartLogo(){
	Dprintf("============================================================================================================\r\n");
	Dprintf("============================================================================================================\r\n");
	Dprintf("              _____                    _____                   _______                   _____          \r\n");
	Dprintf("             /\\    \\                  /\\    \\                 /::\\    \\                 /\\    \\         \r\n");
	Dprintf("            /::\\    \\                /::\\____\\               /::::\\    \\               /::\\    \\        \r\n");
	Dprintf("           /::::\\    \\              /::::|   |              /::::::\\    \\             /::::\\    \\       \r\n");
	Dprintf("          /::::::\\    \\            /:::::|   |             /::::::::\\    \\           /::::::\\    \\      \r\n");
	Dprintf("         /:::/\\:::\\    \\          /::::::|   |            /:::/~~\\:::\\    \\         /:::/\\:::\\    \\     \r\n");
	Dprintf("        /:::/  \\:::\\    \\        /:::/|::|   |           /:::/    \\:::\\    \\       /:::/__\\:::\\    \\    \r\n");
	Dprintf("       /:::/    \\:::\\    \\      /:::/ |::|   |          /:::/    / \\:::\\    \\      \\:::\\   \\:::\\    \\   \r\n");
	Dprintf("      /:::/    / \\:::\\    \\    /:::/  |::|___|______   /:::/____/   \\:::\\____\\   ___\\:::\\   \\:::\\    \\  \r\n");
	Dprintf("     /:::/    /   \\:::\\ ___\\  /:::/   |::::::::\\    \\ |:::|    |     |:::|    | /\\   \\:::\\   \\:::\\    \\ \r\n");
	Dprintf("    /:::/____/     \\:::|    |/:::/    |:::::::::\\____\\|:::|____|     |:::|    |/::\\   \\:::\\   \\:::\\____\\\r\n");
	Dprintf("    \\:::\\    \\     /:::|____|\\::/    / ~~~~~/:::/    / \\:::\\    \\   /:::/    / \\:::\\   \\:::\\   \\::/    /\r\n");
	Dprintf("     \\:::\\    \\   /:::/    /  \\/____/      /:::/    /   \\:::\\    \\ /:::/    /   \\:::\\   \\:::\\   \\/____/ \r\n");
	Dprintf("      \\:::\\    \\ /:::/    /               /:::/    /     \\:::\\    /:::/    /     \\:::\\   \\:::\\    \\     \r\n");
	Dprintf("       \\:::\\    /:::/    /               /:::/    /       \\:::\\__/:::/    /       \\:::\\   \\:::\\____\\    \r\n");
	Dprintf("        \\:::\\  /:::/    /               /:::/    /         \\::::::::/    /         \\:::\\  /:::/    /    \r\n");
	Dprintf("         \\:::\\/:::/    /               /:::/    /           \\::::::/    /           \\:::\\/:::/    /     \r\n");
	Dprintf("          \\::::::/    /               /:::/    /             \\::::/    /             \\::::::/    /      \r\n");
	Dprintf("           \\::::/    /               /:::/    /               \\::/____/               \\::::/    /       \r\n");
	Dprintf("            \\::/____/                \\::/    /                 ~~                      \\::/    /        \r\n");
	Dprintf("             ~~                       \\/____/                                           \\/____/         \r\n");
	Dprintf("============================================================================================================\r\n");

	Dprintf("Welcom to Ditel Motor-Driver Operating System\r\n");
	Dprintf("Version: beta\r\n");
	Dprintf("\r\n");

	Dprintf("<Commands>\r\n");
	Dprintf(">motor [neutral] [brake] [forward <power(0~59999)>] [backward <power(0~59999)>] [check]\r\n");
	Dprintf(">pid [set] [check]\r\n");


	Dprintf("============================================================================================================\r\n");
}

void _ConsoleCommandRead(){
	uint8_t _reciveData, _consoleReadStringCount;

	while(1){
		_consoleReadStringCount = 0;

		Dprintf("D-M-005>");
		while(1){
			while(HAL_UART_Receive(_ConsoleSetting.__PcUart, &_reciveData, 1, 300) != HAL_OK);

			if(_reciveData == 13){
				break;
			}else if(_reciveData == 8 && _consoleReadStringCount > 0){
				HAL_UART_Transmit(_ConsoleSetting.__PcUart, (uint8_t *)"\b \b", 3, 300);
				_consoleReadStringCount--;
			}else{
				HAL_UART_Transmit(_ConsoleSetting.__PcUart, &_reciveData, 1, 300);
				_ConsoleReadString[_consoleReadStringCount] = _reciveData;
				_consoleReadStringCount++;
			}
		}
		HAL_UART_Transmit(_ConsoleSetting.__PcUart, (uint8_t *)"\n\r", 2, 300);
		_ConsoleReadString[_consoleReadStringCount] = '\0';

		if(_CommandCollation(_ConsoleReadString, &_ConsoleCommandResult))
			break;
	}
}
