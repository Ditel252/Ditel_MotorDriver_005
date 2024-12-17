/*
 * Utility.c
 *
 *  Created on: Dec 17, 2024
 *      Author: Suyam
 */


#include "D-M-005/Utility.h"

uint32_t _AccurateDelay(uint32_t _ms, uint32_t _lastGetTick){
	uint32_t _nowTick = HAL_GetTick();

	while((_nowTick - _lastGetTick) <= _ms){
		_nowTick = HAL_GetTick();
	}

	return _nowTick;
}
