/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
CAN_HandleTypeDef hcan;

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
_7SEG_SETTING Setting_7Seg;
_MOTOR_SETTING Setting_Motor;
_SWITCH_SETTING Setting_Swich;
_CONSOLE_SETTING Setting_Console;
_ROTARY_ENCODER_SETTING Setting_RotaryEncoder;
_PID_SETTING Setting_PID;

_SWITCH_READ_DATA SwitchReadData;
_PID_INFOMATION_AND_RESULT PidInfoAndResult;

CAN_FilterTypeDef canFilter;

uint8_t myAddress;
uint8_t commandData[7];
uint32_t lastCommandGetTime;

CAN_RxHeaderTypeDef RxHeader;
uint8_t RxData[8];
uint8_t RxCanFlag = 0;

bool PID_ConsolDebug = true;
bool PID_isEnable = false;
__MOTOR_MODE PID_nowMotorMode = _MOTOR_MODE_NEUTRAL;
__MOTOR_MODE PID_lastMotorMode = _MOTOR_MODE_NEUTRAL;
uint16_t PID_MotorValue = 0;
_ROTARY_ENCODER_RESULT rotaryEncoderResult;
uint32_t _loopCheckCounter = 0;
uint32_t _readTimeForLoopCycle, _lastReadTimeForLoopCycle;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */
void Init(){
	uint32_t _lastReadTick;

	//Start Program
	_Init_7Seg();
	_7SegReset();

	_7SegSetUpAnimation(_SETUP_STEP_START_PROGRAM);
	_lastReadTick = HAL_GetTick();

	//Init Motor
	_Init_Motor();

	_lastReadTick = _AccurateDelay(200, _lastReadTick);
	_7SegSetUpAnimation(_SETUP_STEP_SETUP_MOTOR);

	//Init Switch And Read State
	_Init_Switch();

	_lastReadTick = _AccurateDelay(200, _lastReadTick);
	_7SegSetUpAnimation(_SETUP_STEP_SETUP_AND_READ_SWICH);

	myAddress = SwitchReadData._Address;	//get my Address

	//Init Console
	_Init_Console();

	_lastReadTick = _AccurateDelay(200, _lastReadTick);
	_7SegSetUpAnimation(_SETUP_STEP_SETUP_CONSOLE);

	//Init Rotary Encoder
	_Init_RotaryEncoder();

	_lastReadTick = _AccurateDelay(200, _lastReadTick);
	_7SegSetUpAnimation(_SETUP_STEP_SETUP_ROTARY_ENCODER);

	//Init PID
	_Init_PID();

	_lastReadTick = _AccurateDelay(200, _lastReadTick);
	_7SegSetUpAnimation(_SETUP_STEP_SETUP_PID);

	//Init CAN
	_Init_CAN();

	_lastReadTick = _AccurateDelay(200, _lastReadTick);
	_7SegSetUpAnimation(_SETUP_STEP_SETUO_CAN);

	_lastReadTick = _AccurateDelay(200, _lastReadTick);
	_7SegSetUpAnimation(_SETUP_STEP_NULL6);

	_lastReadTick = _AccurateDelay(200, _lastReadTick);
	_7SegSetUpAnimation(_SETUP_STEP_FINISH);

	_lastReadTick = _AccurateDelay(200, _lastReadTick);
	_7SegReset();


	_lastReadTick = _AccurateDelay(200, _lastReadTick);
}

void _Init_7Seg(){
	Setting_7Seg.__7SegSi_GpioPort = _7SEG_SI_GPIO_Port;
	Setting_7Seg.__7SegSi_Pin = _7SEG_SI_Pin;
	Setting_7Seg.__7SegRck_GpioPort = _7SEG_RCK_GPIO_Port;
	Setting_7Seg.__7SegRck_Pin = _7SEG_RCK_Pin;
	Setting_7Seg.__7SegSck_GpioPort = _7SEG_SCK_GPIO_Port;
	Setting_7Seg.__7SegSck_Pin = _7SEG_SCK_Pin;

	_7SegInit(&Setting_7Seg);
	_7SegReset();
}

void _Init_Motor(){
	Setting_Motor.__MotorP1_Tim = &htim2;
	Setting_Motor.__MotorP1_TimChannel = TIM_CHANNEL_1;
	Setting_Motor.__MotorP2_Tim = &htim3;
	Setting_Motor.__MotorP2_TimChannel = TIM_CHANNEL_4;

	Setting_Motor.__MotorN1_GpioPort = SIG_N1_GPIO_Port;
	Setting_Motor.__MotorN1_Pin = SIG_N1_Pin;
	Setting_Motor.__MotorN2_GpioPort = SIG_N2_GPIO_Port;
	Setting_Motor.__MotorN2_Pin = SIG_N2_Pin;

	Setting_Motor.__DeadTime_TIM = &htim1;

	_MotorInit(&Setting_Motor);
}

void _Init_Switch(){
	Setting_Swich.__ShiftRegisterClk_GpioPort = SW_CLK_GPIO_Port;
	Setting_Swich.__ShiftRegisterClk_Pin = SW_CLK_Pin;
	Setting_Swich.__ShiftRegisterQh_GpioPort = SW_QH_GPIO_Port;
	Setting_Swich.__ShiftRegisterQh_Pin = SW_QH_Pin;
	Setting_Swich.__ShiftRegisterShLd_GpioPort = SW_SH_LD_GPIO_Port;
	Setting_Swich.__ShiftRegisterShLd_Pin = SW_SH_LD_Pin;

	_SwitchInit(&Setting_Swich);
	_SwitchRead(&SwitchReadData);
}

void _Init_Console(){
	Setting_Console.__PcUart = &huart1;

	_ConsoleInit(&Setting_Console);
}

void _Init_RotaryEncoder(){
	Setting_RotaryEncoder.__RotaryEncoderA_GpioPort = ROTARY_ENCODER_A_GPIO_Port;
	Setting_RotaryEncoder.__RotaryEncoderA_Pin = ROTARY_ENCODER_A_Pin;
	Setting_RotaryEncoder.__RotaryEncoderB_GpioPort = ROTARY_ENCODER_B_GPIO_Port;
	Setting_RotaryEncoder.__RotaryEncoderB_Pin = ROTARY_ENCODER_B_Pin;
	Setting_RotaryEncoder.__RotaryEncoderZ_GpioPort = ROTARY_ENCODER_Z_GPIO_Port;
	Setting_RotaryEncoder.__RotaryEncoderZ_Pin = ROTARY_ENCODER_Z_Pin;

	Setting_RotaryEncoder.__MesureTime_TIM = &htim1;

	_RotaryEncoderInit(&Setting_RotaryEncoder);
}

void _Init_PID(){
	Setting_PID._PID_Setting_Kp = 2.0;
	Setting_PID._PID_Setting_Ki = 5.0;
	Setting_PID._PID_Setting_Kd = 0.05;

	Setting_PID._PID_Setting_loopCycleTime = _CONTROL_LOOP_CYCLE;

	_PidInit(&Setting_PID);
}

void _Init_CAN(){
	  uint32_t filterId = myAddress << 21;
	  canFilter.FilterIdHigh = filterId >> 16;
	  canFilter.FilterIdLow = filterId;
	  canFilter.FilterMaskIdHigh = 0;
	  canFilter.FilterMaskIdLow = 0;
	  canFilter.FilterScale = CAN_FILTERSCALE_32BIT;
	  canFilter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
	  canFilter.FilterBank = 0;
	  canFilter.FilterMode = CAN_FILTERMODE_IDLIST;
	  canFilter.SlaveStartFilterBank = 14;
	  canFilter.FilterActivation = ENABLE;
	  HAL_CAN_ConfigFilter(&hcan, &canFilter);

	  HAL_CAN_Start(&hcan);
	  HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
}

uint8_t DeriveUpper2digits(double _value){
	_value *= 100.0;

	uint16_t n = 0;

	while(true){
		if((int)(_value / pow(10.0, n)) == 0)
			break;
		n++;
	}

	if((_value / 100.0) >= 1.0)
		return (uint8_t)(_value / (pow(10.0, n - 2) <= 0.0 ? 1.0 : pow(10.0, n - 2)));
	else
		return (uint8_t)(_value / (pow(10.0, n - 2) <= 0.0 ? 1.0 : pow(10.0, n - 2))) / 10;
}

void CommandIdentification(_COMMAND _command, uint8_t _data[]){
	if(_command >= COMMAND_NORMAL_FORWARD && _command <= COMMAND_NORMAL_BRAKE){	//Normal Mode
		uint16_t _motorSpeed = (_data[0] << 8) | (_data[1] << 0);

		if(_motorSpeed >= __MOTOR_MAX_SPEED){
			_7SegDisplay(ERROR_INCORRECT_SPECIFIED_MOTOR_POWER, false);
			_MotorSetSpeed(_MOTOR_MODE_NEUTRAL, 0);
			return;
		}

		switch((uint8_t)_command){
		case COMMAND_NORMAL_FORWARD:
			_7SegDisplay((uint8_t)(_motorSpeed / __7SEG_MOTOR_POWER_NORMAL_MODE_RATIO), false);
			_MotorSetSpeed(_MOTOR_MODE_FORWARD, _motorSpeed);
			break;

		case COMMAND_NORMAL_REVERSAL:
			_7SegDisplay((uint8_t)(_motorSpeed / __7SEG_MOTOR_POWER_NORMAL_MODE_RATIO), true);
			_MotorSetSpeed(_MOTOR_MODE_REVARCE, _motorSpeed);
			break;

		case COMMAND_NORMAL_NEUTRAL:
			_7SegDisplay(__7SEG_MOTOR_MODE_NEUTRAL, false);
			_MotorSetSpeed(_MOTOR_MODE_NEUTRAL, 0);
			break;

		case COMMAND_NORMAL_BRAKE:
			_7SegDisplay(__7SEG_MOTOR_MODE_BREAK, false);
			_MotorSetSpeed(_MOTOR_MODE_BREAK, 0);
			break;
		}
	}else if(_command >= COMMAND_PID_FORWARD && _command <= COMMAND_PID_BRAKE){	//PID Mode
		PID_MotorValue = (_data[0] << 8) | (_data[1] << 0);

		if(PID_MotorValue >= __MOTOR_MAX_SPEED){
			_7SegDisplay(ERROR_INCORRECT_SPECIFIED_MOTOR_POWER, false);
			_MotorSetSpeed(_MOTOR_MODE_NEUTRAL, 0);
			return;
		}

		PID_lastMotorMode = PID_nowMotorMode;
		switch((uint8_t)_command){
		case COMMAND_PID_FORWARD:
			PID_nowMotorMode = _MOTOR_MODE_FORWARD;
			_7SegDisplay((uint8_t)(PID_MotorValue / __7SEG_MOTOR_POWER_NORMAL_MODE_RATIO), false);
			break;
		case COMMAND_PID_REVERSAL:
			PID_nowMotorMode = _MOTOR_MODE_REVARCE;
			_7SegDisplay((uint8_t)(PID_MotorValue / __7SEG_MOTOR_POWER_NORMAL_MODE_RATIO), true);
			break;
		case COMMAND_PID_NEUTRAL:
			PID_nowMotorMode = _MOTOR_MODE_NEUTRAL;
			_7SegDisplay(__7SEG_MOTOR_MODE_NEUTRAL, false);
			break;
		case COMMAND_PID_BRAKE:
			PID_nowMotorMode = _MOTOR_MODE_BREAK;
			_7SegDisplay(__7SEG_MOTOR_MODE_BREAK, false);
			break;
		}

		if(PID_lastMotorMode != PID_nowMotorMode){
			_lastReadTimeForLoopCycle = _readTimeForLoopCycle = HAL_GetTick();
			PidInfoAndResult.__IntegralOfdeviation = 0.0;
			PidInfoAndResult.__LastDeviation = 0.0;
		}
	}else if(_command == COMMAND_PID_SET_GAIN){
		uint32_t _displayBeginTime;
		double _Kp, _Ki, _Kd;
		_Kp = ((double)((uint16_t)(_data[0] << 8) | (_data[1] << 0))) / 100.0;
		_Ki = ((double)((uint16_t)(_data[2] << 8) | (_data[3] << 0))) / 100.0;
		_Kd = ((double)((uint16_t)(_data[4] << 8) | (_data[5] << 0))) / 100.0;

		if(_Kp < 0.0 || _Kp > PID_GAIN_MAX_VALUE){
			_7SegDisplay(ERROR_INCORRECT_PID_GAIN, false);
			return;
		}else if(_Ki < 0.0 || _Ki > PID_GAIN_MAX_VALUE){
			_7SegDisplay(ERROR_INCORRECT_PID_GAIN, false);
			return;
		}else if(_Kd < 0.0 || _Kd > PID_GAIN_MAX_VALUE){
			_7SegDisplay(ERROR_INCORRECT_PID_GAIN, false);
			return;
		}

		Setting_PID._PID_Setting_Kp = _Kp;
		Setting_PID._PID_Setting_Ki = _Ki;
		Setting_PID._PID_Setting_Kd = _Kd;

		_7SegDisplay1digit(DeriveUpper2digits(Setting_PID._PID_Setting_Kp) % 10, (Setting_PID._PID_Setting_Kp < 100.0 && Setting_PID._PID_Setting_Kp >= 10.0));
		_7SegDisplay1digit(DeriveUpper2digits(Setting_PID._PID_Setting_Kp) / 10, (Setting_PID._PID_Setting_Kp < 10.0 && Setting_PID._PID_Setting_Kp >= 0.1));
		_displayBeginTime = HAL_GetTick();

		while((HAL_GetTick() - _displayBeginTime) < 1000 && RxCanFlag == 0)
			;

		_7SegDisplay1digit(DeriveUpper2digits(Setting_PID._PID_Setting_Ki) % 10, (Setting_PID._PID_Setting_Ki < 100.0 && Setting_PID._PID_Setting_Ki >= 10));
		_7SegDisplay1digit(DeriveUpper2digits(Setting_PID._PID_Setting_Ki) / 10, (Setting_PID._PID_Setting_Ki < 10.0 && Setting_PID._PID_Setting_Ki >= 0.1));
		_displayBeginTime = HAL_GetTick();

		while((HAL_GetTick() - _displayBeginTime) < 1000 && RxCanFlag == 0)
			;

		_7SegDisplay1digit(DeriveUpper2digits(Setting_PID._PID_Setting_Kd) % 10, (Setting_PID._PID_Setting_Kd < 100.0 && Setting_PID._PID_Setting_Kd >= 10));
		_7SegDisplay1digit(DeriveUpper2digits(Setting_PID._PID_Setting_Kd) / 10, (Setting_PID._PID_Setting_Kd < 10.0 && Setting_PID._PID_Setting_Kd >= 0.1));
		_displayBeginTime = HAL_GetTick();

		while((HAL_GetTick() - _displayBeginTime) < 1000 && RxCanFlag == 0)
			;
	}else if(_command == COMMAND_PID_SET_CONDITION){
		if(_data[0] == 0x00){
			PID_isEnable = false;
			_7SegDisplay1digit(0x00, false);
			__7Seg1byteDisplay(~(0b00011111 | 0b00000000));
		}else{
			PID_isEnable = true;
			_7SegDisplay1digit(0x01, false);
			__7Seg1byteDisplay(~(0b00011111 | 0b00000000));

			PID_lastMotorMode = PID_nowMotorMode;
			_lastReadTimeForLoopCycle = _readTimeForLoopCycle = HAL_GetTick();
			PidInfoAndResult.__IntegralOfdeviation = 0.0;
			PidInfoAndResult.__LastDeviation = 0.0;
		}
	}else{
		_7SegDisplay(ERROR_INCORRECT_COMMAND, false);
		_MotorSetSpeed(_MOTOR_MODE_NEUTRAL, 0);
	}
}

void PID_MotorControl(__MOTOR_MODE _targetMode, uint16_t __targetValue){
	if(_targetMode == _MOTOR_MODE_NEUTRAL || _targetMode == _MOTOR_MODE_BREAK)
		__targetValue = 0;

	PidInfoAndResult._targetValue = __targetValue;

	rotaryEncoderResult = _RotaryEncoder_Get1Cycle_TimePeriod();

	if(PID_ConsolDebug)
		Dprintf(">Target Value:%u\n", (uint16_t)(PidInfoAndResult._targetValue));

	if(rotaryEncoderResult._isSuccessGet1CycleTimePerioCount){
		PidInfoAndResult._mesuredValue = (10000000.0 / (double)rotaryEncoderResult._RotaryEncoder_1CycleTimePeriodCount);

		if(PID_ConsolDebug)
			Dprintf(">Control Amount:%u\n", (uint16_t)(PidInfoAndResult._mesuredValue));
	}else{
		PidInfoAndResult._mesuredValue = 0;
		if(PID_ConsolDebug)
			Dprintf(">Control Amount:0\n");
	}

	_PID(&PidInfoAndResult);

	if(PidInfoAndResult._operationAmount > 60000.0){
		PidInfoAndResult._operationAmount = 60000.0;
	}else if(PidInfoAndResult._operationAmount < 0){
		PidInfoAndResult._operationAmount = 0.0;
	}

	if(PID_ConsolDebug)
		  Dprintf(">Operation Amount:%u\n", (uint16_t)PidInfoAndResult._operationAmount);

	_MotorSetSpeed(_targetMode, (uint16_t)PidInfoAndResult._operationAmount);

	_loopCheckCounter = 0;

	while((_readTimeForLoopCycle - _lastReadTimeForLoopCycle) < _CONTROL_LOOP_CYCLE){
		_readTimeForLoopCycle = HAL_GetTick();
		_loopCheckCounter++;
	}

	if(PID_ConsolDebug)
		Dprintf(">Loop Check Counter:%u\n", _loopCheckCounter);

	_lastReadTimeForLoopCycle = _readTimeForLoopCycle;
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan){
	if(HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData) == HAL_OK){
		HAL_GPIO_TogglePin(LED_UART_GPIO_Port, LED_UART_Pin);
		RxCanFlag = 1;
	}
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_CAN_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  HAL_GPIO_WritePin(LED_POWER_GPIO_Port, LED_POWER_Pin, GPIO_PIN_SET); //Power Led ON

  Init(); //Init

  _7SegDisplay(myAddress, false);	//Display my Address

  HAL_Delay(2000);

  lastCommandGetTime = HAL_GetTick();

  //Main Loop
//  while(true){
//	  PID_MotorControl(_MOTOR_MODE_FORWARD, 13000);
//  }

  while(true){
	  while(!(RxCanFlag == 1)){
		  if((HAL_GetTick() - lastCommandGetTime) > TIME_OUT_LENGTH){
			  _7SegDisplay(ERROR_TIMEOUT, false);
			  _MotorSetSpeed(_MOTOR_MODE_NEUTRAL, 0);
			  PID_isEnable = false;

			  while(!(RxCanFlag == 1))
				  ;
		  }

		  if(PID_isEnable){
			  PID_MotorControl(PID_nowMotorMode, PID_MotorValue);
		  }
	  }

	  lastCommandGetTime = HAL_GetTick();

	  for(uint8_t _i = 0; _i < COMMAND_DATA_SIZE; _i++)
		  commandData[_i] = 0;

	  if(RxCanFlag == 1){
		  RxCanFlag = 0;

		  if(RxHeader.DLC != CAN_DATA_SIZE){
		  	_7SegDisplay(ERROR_INCORRECT_DATA_SIZE, false);
		  	_MotorSetSpeed(_MOTOR_MODE_NEUTRAL, 0);
		  	continue;
		  }else{
			  for(uint8_t _i = 0; _i < COMMAND_DATA_SIZE; _i++)
				  commandData[_i] = RxData[_i + 1];
		  }
	  }

	  CommandIdentification(RxData[0], commandData);
  }

  //Can Test Start

  while(true){
	  for(int i = 0; i < 100; i++){
		  HAL_Delay(1);
		  if(RxCanFlag == 1)
			  break;
	  }

	  if(RxCanFlag == 1){
		  RxCanFlag = 0;
		  for(int i = 0; i < RxHeader.DLC; i++){
			  _7SegDisplay(RxData[i], false);
			  HAL_Delay(200);
		  }
	  }else{
//		  _7SegDisplay(0xEE, true);
	  }
  }

  //Can Test End
  _ROTARY_ENCODER_RESULT rotaryEncoderResult;
  uint32_t _loopCheckCounter = 0;

  uint16_t targetValue[10] = {13000, 12000, 14000, 15000, 12000, 16000, 15000, 17500, 14000, 0};

  _lastReadTimeForLoopCycle = _readTimeForLoopCycle = HAL_GetTick();
  PidInfoAndResult.__IntegralOfdeviation = 0.0;

  while(true){
	  for(int i = 0; i < 10; i++){
		  PidInfoAndResult._targetValue = targetValue[i];
		  PidInfoAndResult.__LastDeviation = 0.0;

		  for(int j = 0; j < 1000; j++){
			  rotaryEncoderResult = _RotaryEncoder_Get1Cycle_TimePeriod();
			  Dprintf(">Target Value:%u\n", (uint16_t)(PidInfoAndResult._targetValue));

			  if(rotaryEncoderResult._isSuccessGet1CycleTimePerioCount){
				  PidInfoAndResult._mesuredValue = (10000000.0 / (double)rotaryEncoderResult._RotaryEncoder_1CycleTimePeriodCount);
				  Dprintf(">Control Amount:%u\n", (uint16_t)(PidInfoAndResult._mesuredValue));
			  }else{
				  PidInfoAndResult._mesuredValue = 0;
			  	  Dprintf(">Control Amount:0\n");
			  }

			  _PID(&PidInfoAndResult);

			  if(PidInfoAndResult._operationAmount > 60000.0){
				  PidInfoAndResult._operationAmount = 60000.0;
			  }else if(PidInfoAndResult._operationAmount < 0){
				  PidInfoAndResult._operationAmount = 0.0;
			  }

			  Dprintf(">Operation Amount:%u\n", (uint16_t)PidInfoAndResult._operationAmount);

			  _MotorSetSpeed(_MOTOR_MODE_FORWARD, (uint16_t)PidInfoAndResult._operationAmount);

			  _loopCheckCounter = 0;

			  while((_readTimeForLoopCycle - _lastReadTimeForLoopCycle) < _CONTROL_LOOP_CYCLE){
				  _readTimeForLoopCycle = HAL_GetTick();
			  	  _loopCheckCounter++;
			  }


			  Dprintf(">Loop Check Counter:%u\n", _loopCheckCounter);

			  _lastReadTimeForLoopCycle = _readTimeForLoopCycle;
		  }
	  }
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  _ConsoleCommandRead();
	  Dprintf("Command : %d\r\n", _ConsoleCommandResult._command);
	  Dprintf("Mode    : %d\r\n", _ConsoleCommandResult._mode);
	  Dprintf("Argument: %u\r\n", _ConsoleCommandResult._argument);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL15;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_TIM1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  PeriphClkInit.Tim1ClockSelection = RCC_TIM1CLK_HCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */

  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */

  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN;
  hcan.Init.Prescaler = 3;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_7TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_2TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */

  /* USER CODE END CAN_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 6-1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 0xffff-1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 60000-1;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 0;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 60000-1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_MultiProcessor_Init(&huart1, 0, UART_WAKEUPMETHOD_IDLELINE) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 38400;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_MultiProcessor_Init(&huart2, 0, UART_WAKEUPMETHOD_IDLELINE) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, SW_SH_LD_Pin|SW_CLK_Pin|LED_POWER_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SIG_N2_Pin|SIG_N1_Pin|_7SEG_SCK_Pin|_7SEG_RCK_Pin
                          |_7SEG_SI_Pin|LED_UART_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : SW_QH_Pin ROTARY_ENCODER_Z_Pin ROTARY_ENCODER_B_Pin ROTARY_ENCODER_A_Pin */
  GPIO_InitStruct.Pin = SW_QH_Pin|ROTARY_ENCODER_Z_Pin|ROTARY_ENCODER_B_Pin|ROTARY_ENCODER_A_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SW_SH_LD_Pin SW_CLK_Pin LED_POWER_Pin */
  GPIO_InitStruct.Pin = SW_SH_LD_Pin|SW_CLK_Pin|LED_POWER_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SIG_N2_Pin SIG_N1_Pin _7SEG_SCK_Pin _7SEG_RCK_Pin
                           _7SEG_SI_Pin LED_UART_Pin */
  GPIO_InitStruct.Pin = SIG_N2_Pin|SIG_N1_Pin|_7SEG_SCK_Pin|_7SEG_RCK_Pin
                          |_7SEG_SI_Pin|LED_UART_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
