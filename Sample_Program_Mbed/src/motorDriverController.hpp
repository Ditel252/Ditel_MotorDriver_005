#include <mbed.h>

#define MOTOR_FORWARD   0xA0
#define MOTOR_REVERSAL  0xA1
#define MOTOR_NEUTRAL   0xA2
#define MOTOR_BRAKE     0xA3
#define NONE 0

CAN can(PA_11, PA_12);

void motorDriverSetup(){
    can.frequency(1000000);
}

bool motorDriverRotate(uint8_t _motorDriverAddress, uint8_t _mode, uint8_t _speed = NONE){
    uint8_t canSendData[2];

    canSendData[0] = _mode;
    canSendData[1] = _speed;

    if(can.write(CANMessage(_motorDriverAddress, canSendData, 2)))
        return true;
    else
        return false;
}