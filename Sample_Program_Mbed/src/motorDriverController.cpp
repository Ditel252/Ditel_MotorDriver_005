#include "motorDriverController.hpp"

#define NORMAL_FORWARD   0x10
#define NORMAL_REVERSAL  0x11
#define NORMAL_NEUTRAL   0x12
#define NORMAL_BRAKE     0x13

#define PID_FORWARD		    0x30
#define PID_REVERSAL	    0x31
#define PID_NEUTRAL		    0x32
#define PID_BRAKE		    0x33
#define PID_SET_GAIN	    0x3A
#define PID_SET_CONDITION   0x3B

uint8_t canSendData[SEND_DATA_SIZE];

extern void motorDriverSetup(){
    can.frequency(1000000);
}

extern bool normalMotorDriverRotate(uint8_t _motorDriverAddress, uint8_t _mode, uint16_t _speed){
    for(uint8_t _i = 0; _i < SEND_DATA_SIZE; _i++)
        canSendData[_i] = NONE;

    switch (_mode)
    {
    case MOTOR_FORWARD:
        canSendData[0] = NORMAL_FORWARD;
        break;
        
    case MOTOR_REVERSAL:
        canSendData[0] = NORMAL_REVERSAL;
        break;

    case MOTOR_NEUTRAL:
        canSendData[0] = NORMAL_NEUTRAL;
        break;

    case MOTOR_BRAKE:
        canSendData[0] = NORMAL_BRAKE;
        break;
    
    default:
        return false;
    }

    canSendData[1] = (_speed & 0xFF00) >> 8;
    canSendData[2] = (_speed & 0x00FF) >> 0;

    if(can.write(CANMessage(_motorDriverAddress, canSendData, 8)))
        return true;
    else
        return false;
}

extern bool PIDMotorDriverRote(uint8_t _motorDriverAddress, uint8_t _mode, uint16_t _speed){
    for(uint8_t _i = 0; _i < SEND_DATA_SIZE; _i++)
        canSendData[_i] = NONE;

    switch (_mode)
    {
    case MOTOR_FORWARD:
        canSendData[0] = PID_FORWARD;
        break;
        
    case MOTOR_REVERSAL:
        canSendData[0] = PID_REVERSAL;
        break;

    case MOTOR_NEUTRAL:
        canSendData[0] = PID_NEUTRAL;
        break;

    case MOTOR_BRAKE:
        canSendData[0] = PID_BRAKE;
        break;
    
    default:
        return false;
    }

    canSendData[1] = (_speed & 0xFF00) >> 8;
    canSendData[2] = (_speed & 0x00FF) >> 0;

    if(can.write(CANMessage(_motorDriverAddress, canSendData, 8)))
        return true;
    else
        return false;
}

extern bool setPIDGain(uint8_t _motorDriverAddress, double PGain, double IGain, double DGain){
    uint16_t sendKp, sendKi, sendKd;
    for(uint8_t _i = 0; _i < SEND_DATA_SIZE; _i++)
        canSendData[_i] = NONE;

    canSendData[0] = PID_SET_GAIN;

    sendKp = (uint16_t)(PGain * 100);
    sendKi = (uint16_t)(IGain * 100);
    sendKd = (uint16_t)(DGain * 100);

    canSendData[1] = (sendKp & 0xFF00) >> 8;
    canSendData[2] = (sendKp & 0x00FF) >> 0;
    
    canSendData[3] = (sendKi & 0xFF00) >> 8;
    canSendData[4] = (sendKi & 0x00FF) >> 0;
    
    canSendData[5] = (sendKd & 0xFF00) >> 8;
    canSendData[6] = (sendKd & 0x00FF) >> 0;

    if(can.write(CANMessage(_motorDriverAddress, canSendData, 8)))
        return true;
    else
        return false;
}

extern bool setPIDControlCondition(uint8_t _motorDriverAddress, bool isRequestEnable){
    for(uint8_t _i = 0; _i < SEND_DATA_SIZE; _i++)
        canSendData[_i] = NONE;

    canSendData[0] = PID_SET_CONDITION;

    if(isRequestEnable)
        canSendData[1] = 0x01;
    else
        canSendData[1] = 0x00;


    if(can.write(CANMessage(_motorDriverAddress, canSendData, 8)))
        return true;
    else
        return false;
}