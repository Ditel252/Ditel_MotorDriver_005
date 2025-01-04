/*
 * PID.h
 *
 *  Created on: Jan 4, 2025
 *      Author: Suyam
 */

#ifndef INC_D_M_005_PID_H_
#define INC_D_M_005_PID_H_

#include <stdint.h>

typedef struct{
	double _PID_Setting_Kp;
	double _PID_Setting_Ki;
	double _PID_Setting_Kd;

	uint32_t _PID_Setting_loopCycleTime;	//[ms]
}_PID_SETTING;

typedef struct{
	double _targetValue;
	double _mesuredValue;

	double _operationAmount;

	double __IntegralOfdeviation;
	double __LastDeviation;
}_PID_INFOMATION_AND_RESULT;

void _PidInit(_PID_SETTING *);
void _PID(_PID_INFOMATION_AND_RESULT *);

#endif /* INC_D_M_005_PID_H_ */
