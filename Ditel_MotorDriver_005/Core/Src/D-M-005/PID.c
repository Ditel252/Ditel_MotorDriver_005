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
	double _Deviation;

	_Deviation = __PidInfoAndResult->_targetValue - __PidInfoAndResult->_mesuredValue;

	__PidInfoAndResult->__IntegralOfdeviation = _Deviation * _PidSetting._PID_Setting_loopCycleTime / 1000.0 + __PidInfoAndResult->__IntegralOfdeviation;


	__PidInfoAndResult->_controlValue = \
			_PidSetting._PID_Setting_Kp * _Deviation + \
			_PidSetting._PID_Setting_Ki * __PidInfoAndResult->__IntegralOfdeviation\
			;
}
