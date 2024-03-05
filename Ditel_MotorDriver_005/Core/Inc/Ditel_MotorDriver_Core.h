#include "main.h"
#include "can.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include <stdio.h>

#include <stdbool.h>

#define NONE 0

//<Pin Relationshp Constants>
//LED
#define PIN_POWER_LED   GPIOA,GPIO_PIN_8
#define PIN_UART_LED    GPIOB,GPIO_PIN_7
//FET SIG
#define PIN_SIG_P1      GPIOB,GPIO_PIN_3
#define PIN_SIG_N1      GPIOA,GPIO_PIN_15
#define PIN_SIG_P2      GPIOB,GPIO_PIN_0
#define PIN_SIG_N2      GPIOB,GPIO_PIN_1
//7SEG Shift Resister
#define PIN_7SEG_SI     GPIOB,GPIO_PIN_6
#define PIN_7SEG_RCK    GPIOB,GPIO_PIN_5
#define PIN_7SEG_SCK    GPIOB,GPIO_PIN_4
//SW Shift Resister
#define PIN_SW_CLK      GPIOA,GPIO_PIN_4
#define PIN_SW_QH       GPIOA,GPIO_PIN_0
#define PIN_SW_SH_LD    GPIOA,GPIO_PIN_1
//ROTARY Encoder
#define PIN_ROTARY_A    GPIOA,GPIO_PIN_7
#define PIN_ROTARY_B    GPIOA,GPIO_PIN_6
#define PIN_ROTARY_Z    GPIOA,GPIO_PIN_5


//<Tim Relationshp Constants>
//FET SIG TIM
#define TIM_SIG_P1          htim2
#define TIM_CHANNEL_SIG_P1  TIM_CHANNEL_2
#define TIM_SIG_P2          htim3
#define TIM_CHANNEL_SIG_P2  TIM_CHANNEL_3


//<Control Constant>
//Motor Control
#define MOTOR_FORWARD   0xA0
#define MOTOR_REVERSAL  0xA1
#define MOTOR_NEUTRAL   0xA2
#define MOTOR_BRAKE     0xA3
//SW Control
#define SW_MODE_ROTATY_ENCODERS_SPEED       0xB0
#define SW_MODE_ROTATY_ENCODERS_DEGREE      0xB1
#define SW_BIT_MYADDRESS_1ST_DIGIT          3
#define SW_BIT_MYADDRESS_2ND_DIGIT          2
#define SW_BIT_MYADDRESS_3ND_DIGIT          1
#define SW_BIT_MYADDRESS_4TH_DIGIT          0
#define SW_BIT_ROTARY_ENCODERS_IS_ENABLED   6
#define SW_BIT_ROTARY_ENCODERS_MODE         7


//<CAN Constant>
#define CAN_READ_DATA_SIZE  2


//<ERROR Constant>
#define ERROR_CAN_READ_DATA         0xE0
#define ERROR_COMMUNICATION_TIMEOUT 0xE1


//<Other Information Constant>
#define OTHER_INFORMATION_MOTOR_MODE_IS_NEUTRAL 0xD0
#define OTHER_INFORMATION_MOTOR_MODE_IS_BREAK   0xD1


//<CAN Variable>
uint8_t myAddress;
uint8_t readData[CAN_READ_DATA_SIZE];


//<Motor Variable>
uint8_t nowMotorControl =   MOTOR_NEUTRAL;
uint16_t timeOutCount =     0;


//<Function Prototype Declaration>
void setupPin();
void setupPin_LED();
void setupPin_SIG();
void setupPin_7SEG();
void setupPin_SW();
void setupPin_ROTATY();
void setupCan();
void display7Seg(uint8_t _displayContent, bool isDisplayDp);
void reset7Seg();
void display7Seg_1byte(uint8_t _displayContent);
void motorSet(const uint8_t _direction, const uint8_t _speed);
uint8_t swRead();
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan);


//<Function Definition>
//setup
void setupPin(){
    setupPin_LED();
    setupPin_SIG();
    setupPin_7SEG();
    setupPin_SW();
    setupPin_ROTATY();
}
void setupPin_LED(){
    HAL_GPIO_WritePin(PIN_POWER_LED, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(PIN_UART_LED, GPIO_PIN_RESET);
}
void setupPin_SIG(){
    HAL_GPIO_WritePin(PIN_SIG_N1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(PIN_SIG_N2, GPIO_PIN_RESET);

    HAL_TIM_PWM_Start(&TIM_SIG_P1, TIM_CHANNEL_SIG_P1);
    HAL_TIM_PWM_Start(&TIM_SIG_P2, TIM_CHANNEL_SIG_P2);

    __HAL_TIM_SET_COMPARE(&TIM_SIG_P1, TIM_CHANNEL_SIG_P1, 0);
    __HAL_TIM_SET_COMPARE(&TIM_SIG_P2, TIM_CHANNEL_SIG_P2, 0);
}
void setupPin_7SEG(){
    HAL_GPIO_WritePin(PIN_7SEG_SI, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(PIN_7SEG_RCK, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(PIN_7SEG_SCK, GPIO_PIN_RESET);
}
void setupPin_SW(){
    HAL_GPIO_WritePin(PIN_SW_CLK, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(PIN_SW_QH, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(PIN_SW_SH_LD, GPIO_PIN_RESET);
}
void setupPin_ROTATY(){
    HAL_GPIO_WritePin(PIN_ROTARY_A, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(PIN_ROTARY_B, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(PIN_ROTARY_Z, GPIO_PIN_RESET);
}
void setupCan(){
    HAL_CAN_Start(&hcan);
    HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);
    uint32_t filterId = myAddress << 21;
    CAN_FilterTypeDef filter;
    filter.FilterIdHigh = filterId >> 16;
    filter.FilterIdLow = filterId;
    filter.FilterMaskIdHigh = 0;
    filter.FilterMaskIdLow = 0;
    filter.FilterScale = CAN_FILTERSCALE_32BIT;
    filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    filter.FilterBank = 0;
    filter.FilterMode = CAN_FILTERMODE_IDLIST;
    filter.SlaveStartFilterBank = 14;
    filter.FilterActivation = ENABLE;
    HAL_CAN_ConfigFilter(&hcan, &filter);
}


//<Function Control>
//7Seg Display
void display7Seg(uint8_t _displayContent, bool isDisplayDp){
    switch(_displayContent & 0x0F){
        case 0x00:
            display7Seg_1byte(~(0b01110111 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x01:
            display7Seg_1byte(~(0b01000001 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x02:
            display7Seg_1byte(~(0b00111011 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x03:
            display7Seg_1byte(~(0b01101011 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x04:
            display7Seg_1byte(~(0b01001101 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x05:
            display7Seg_1byte(~(0b01101110 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x06:
            display7Seg_1byte(~(0b01111110 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x07:
            display7Seg_1byte(~(0b01000111 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x08:
            display7Seg_1byte(~(0b01111111 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x09:
            display7Seg_1byte(~(0b01101111 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x0A:
            display7Seg_1byte(~(0b01011111 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x0B:
            display7Seg_1byte(~(0b01111100 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x0C:
            display7Seg_1byte(~(0b00110110 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x0D:
            display7Seg_1byte(~(0b01111001 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x0E:
            display7Seg_1byte(~(0b00111110 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x0F:
            display7Seg_1byte(~(0b00011110 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
    }

    switch(_displayContent & 0xF0){
        case 0x00:
            display7Seg_1byte(~(0b01110111 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x10:
            display7Seg_1byte(~(0b01000001 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x20:
            display7Seg_1byte(~(0b00111011 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x30:
            display7Seg_1byte(~(0b01101011 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x40:
            display7Seg_1byte(~(0b01001101 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x50:
            display7Seg_1byte(~(0b01101110 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x60:
            display7Seg_1byte(~(0b01111110 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x70:
            display7Seg_1byte(~(0b01000111 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x80:
            display7Seg_1byte(~(0b01111111 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x90:
            display7Seg_1byte(~(0b01101111 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0xA0:
            display7Seg_1byte(~(0b01011111 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0xB0:
            display7Seg_1byte(~(0b01111100 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0xC0:
            display7Seg_1byte(~(0b00110110 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0xD0:
            display7Seg_1byte(~(0b01111001 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0xE0:
            display7Seg_1byte(~(0b00111110 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0xF0:
            display7Seg_1byte(~(0b00011110 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
    }
}
void reset7Seg(){
    display7Seg_1byte(~(0b00000000));
    display7Seg_1byte(~(0b00000000));
}
void display7Seg_1byte(uint8_t _displayContent){
    HAL_GPIO_WritePin(PIN_7SEG_RCK, GPIO_PIN_RESET);
    for (int i = 0; i < 8; i++){
        HAL_GPIO_WritePin(PIN_7SEG_SI, (_displayContent & (1U << i)) ? GPIO_PIN_SET : GPIO_PIN_RESET);

        HAL_GPIO_WritePin(PIN_7SEG_SCK, GPIO_PIN_SET);
        HAL_GPIO_WritePin(PIN_7SEG_SCK, GPIO_PIN_RESET);
    }

    HAL_GPIO_WritePin(PIN_7SEG_RCK, GPIO_PIN_SET);
}
//Motor Control
uint8_t lastMotorSetDirection = 0;
void motorSet(const uint8_t _direction, const uint8_t _speed){
    if((lastMotorSetDirection != _direction) && (_direction != MOTOR_NEUTRAL)){
        motorSet(MOTOR_NEUTRAL, NONE);
        for(volatile int i = 0; i < 15000; i++)
            ;
    }

    switch(_direction){
        case MOTOR_FORWARD:
            __HAL_TIM_SET_COMPARE(&TIM_SIG_P2, TIM_CHANNEL_SIG_P2, 0);
            HAL_GPIO_WritePin(PIN_SIG_N1, GPIO_PIN_RESET);
            __HAL_TIM_SET_COMPARE(&TIM_SIG_P1, TIM_CHANNEL_SIG_P1, (uint16_t)((double)_speed * 5.025));
            HAL_GPIO_WritePin(PIN_SIG_N2, GPIO_PIN_SET);
            nowMotorControl = MOTOR_FORWARD;
            break;
        case MOTOR_REVERSAL:
            __HAL_TIM_SET_COMPARE(&TIM_SIG_P1, TIM_CHANNEL_SIG_P1, 0);
            HAL_GPIO_WritePin(PIN_SIG_N2, GPIO_PIN_RESET);
            __HAL_TIM_SET_COMPARE(&TIM_SIG_P2, TIM_CHANNEL_SIG_P2, (uint16_t)((double)_speed * 5.025));
            HAL_GPIO_WritePin(PIN_SIG_N1, GPIO_PIN_SET);
            nowMotorControl = MOTOR_REVERSAL;
            break;
        case MOTOR_NEUTRAL:
            __HAL_TIM_SET_COMPARE(&TIM_SIG_P1, TIM_CHANNEL_SIG_P1, 0);
            __HAL_TIM_SET_COMPARE(&TIM_SIG_P2, TIM_CHANNEL_SIG_P2, 0);
            HAL_GPIO_WritePin(PIN_SIG_N1, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(PIN_SIG_N2, GPIO_PIN_RESET);
            nowMotorControl = MOTOR_NEUTRAL;
            break;
        case MOTOR_BRAKE:
            __HAL_TIM_SET_COMPARE(&TIM_SIG_P1, TIM_CHANNEL_SIG_P1, 0);
            __HAL_TIM_SET_COMPARE(&TIM_SIG_P2, TIM_CHANNEL_SIG_P2, 0);
            HAL_GPIO_WritePin(PIN_SIG_N1, GPIO_PIN_SET);
            HAL_GPIO_WritePin(PIN_SIG_N2, GPIO_PIN_SET);
            nowMotorControl = MOTOR_BRAKE;
            break;
    }

    lastMotorSetDirection = _direction;
}
//SW Read
bool isRotaryEncoderModeEnabled = false;
uint8_t rotaryEncoderMode;
uint8_t swRead(){
    uint8_t readSwData = 0;

    HAL_GPIO_WritePin(PIN_SW_SH_LD, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(PIN_SW_CLK, GPIO_PIN_SET);
    HAL_GPIO_WritePin(PIN_SW_CLK, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(PIN_SW_SH_LD, GPIO_PIN_SET);

    readSwData = readSwData | (HAL_GPIO_ReadPin(PIN_SW_QH) << 7);
    for(int i = 6; i >= 0; i--){
        HAL_GPIO_WritePin(PIN_SW_CLK, GPIO_PIN_SET);
        HAL_GPIO_WritePin(PIN_SW_CLK, GPIO_PIN_RESET);

        readSwData = readSwData | (HAL_GPIO_ReadPin(PIN_SW_QH) << i);
    }

    myAddress = 0;
    myAddress |= (!!(readSwData & (1U << SW_BIT_MYADDRESS_4TH_DIGIT))) << 3;
    myAddress |= (!!(readSwData & (1U << SW_BIT_MYADDRESS_3ND_DIGIT))) << 2;
    myAddress |= (!!(readSwData & (1U << SW_BIT_MYADDRESS_2ND_DIGIT))) << 1;
    myAddress |= (!!(readSwData & (1U << SW_BIT_MYADDRESS_1ST_DIGIT))) << 0;

    isRotaryEncoderModeEnabled = !!(readSwData & (1U << SW_BIT_ROTARY_ENCODERS_IS_ENABLED));
    
    if(!!(readSwData & (1U << SW_BIT_ROTARY_ENCODERS_MODE)))
        rotaryEncoderMode = SW_MODE_ROTATY_ENCODERS_SPEED;
    else
        rotaryEncoderMode = SW_MODE_ROTATY_ENCODERS_DEGREE;

    return readSwData;
}
//CAN
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan){
  CAN_RxHeaderTypeDef rxHeader;
  uint8_t rxData[CAN_READ_DATA_SIZE];

  if(HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &rxHeader, rxData) == HAL_OK)
  {
    for(int i = 0; i < CAN_READ_DATA_SIZE; i++)
        readData[i] = rxData[i];

    switch(rxData[0]){
        case MOTOR_FORWARD:
            display7Seg(readData[1], false);
            motorSet(MOTOR_FORWARD, readData[1]);
            timeOutCount = 0;
            break;
        case MOTOR_REVERSAL:
            display7Seg(readData[1], true);
            motorSet(MOTOR_REVERSAL, readData[1]);
            timeOutCount = 0;
            break;
        case MOTOR_NEUTRAL:
            display7Seg(OTHER_INFORMATION_MOTOR_MODE_IS_NEUTRAL,false);
            motorSet(MOTOR_NEUTRAL, NONE);
            timeOutCount = 0;
            break;
        case MOTOR_BRAKE:
            display7Seg(OTHER_INFORMATION_MOTOR_MODE_IS_BREAK, false);
            motorSet(MOTOR_BRAKE, NONE);
            timeOutCount = 0;
            break;
        default:
            display7Seg(ERROR_CAN_READ_DATA, false);
            break;
    }
  }
}