#include <mbed.h>

#define SEND_DATA_SIZE 8

#define MOTOR_FORWARD   0x0
#define MOTOR_REVERSAL  0x1
#define MOTOR_NEUTRAL   0x2
#define MOTOR_BRAKE     0x3

#define NONE 0x00

static CAN can(PA_11, PA_12);

void motorDriverSetup();    //通信開始(プログラム開始時に必ず実行)
bool normalMotorDriverRotate(uint8_t _motorDriverAddress, uint8_t _mode, uint16_t _speed = NONE);    //ノーマルモード