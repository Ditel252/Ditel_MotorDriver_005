/*
 * PID.c
 *
 *  Created on: Jan 4, 2025
 *      Author: Suyam
 */


#include "D-M-005/PID.h"

_PID_SETTING _PidSetting;

void _PidInit(_PID_SETTING *__PidSetting){
	_PidSetting._PID_Setting_Kp = __PidSetting->_PID_Setting_Kp;
	_PidSetting._PID_Setting_Ki = __PidSetting->_PID_Setting_Ki;
	_PidSetting._PID_Setting_Kd = __PidSetting->_PID_Setting_Kd;

	_PidSetting._PID_Setting_loopCycleTime = __PidSetting->_PID_Setting_loopCycleTime;
}

void _PID(_PID_INFOMATION_AND_RESULT *__PidInfoAndResult){
	__PidInfoAndResult->_controlValue = \
			_PidSetting._PID_Setting_Kp * (__PidInfoAndResult->_targetValue - __PidInfoAndResult->_mesuredValue)\
			;
}
