/*
 * D-M-005.c
 *
 *  Created on: Dec 13, 2024
 *      Author: Suyam
 */


#include <D-M-005/7Seg.h>

_7SEG_SETTING _7SegSetting;

void _7SegInit(_7SEG_SETTING *__7SegSetting){
	_7SegSetting.__7SegSi_GpioPort = __7SegSetting->__7SegSi_GpioPort;
	_7SegSetting.__7SegSi_Pin = __7SegSetting->__7SegSi_Pin;
	_7SegSetting.__7SegRck_GpioPort = __7SegSetting->__7SegRck_GpioPort;
	_7SegSetting.__7SegRck_Pin = __7SegSetting->__7SegRck_Pin;
	_7SegSetting.__7SegSck_GpioPort = __7SegSetting->__7SegSck_GpioPort;
	_7SegSetting.__7SegSck_Pin = __7SegSetting->__7SegSck_Pin;

	HAL_GPIO_WritePin(_7SegSetting.__7SegSi_GpioPort, _7SegSetting.__7SegSi_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(_7SegSetting.__7SegRck_GpioPort, _7SegSetting.__7SegRck_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(_7SegSetting.__7SegSck_GpioPort, _7SegSetting.__7SegSck_Pin, GPIO_PIN_RESET);
}

void _7SegDisplay(uint8_t _displayContent, bool isDisplayDp){
    switch(_displayContent & 0x0F){
        case 0x00:
            __7Seg1byteDisplay(~(0b01110111 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x01:
            __7Seg1byteDisplay(~(0b01000001 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x02:
            __7Seg1byteDisplay(~(0b00111011 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x03:
            __7Seg1byteDisplay(~(0b01101011 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x04:
            __7Seg1byteDisplay(~(0b01001101 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x05:
            __7Seg1byteDisplay(~(0b01101110 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x06:
            __7Seg1byteDisplay(~(0b01111110 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x07:
            __7Seg1byteDisplay(~(0b01000111 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x08:
            __7Seg1byteDisplay(~(0b01111111 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x09:
            __7Seg1byteDisplay(~(0b01101111 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x0A:
            __7Seg1byteDisplay(~(0b01011111 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x0B:
            __7Seg1byteDisplay(~(0b01111100 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x0C:
            __7Seg1byteDisplay(~(0b00110110 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x0D:
            __7Seg1byteDisplay(~(0b01111001 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x0E:
            __7Seg1byteDisplay(~(0b00111110 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x0F:
            __7Seg1byteDisplay(~(0b00011110 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
    }

    switch(_displayContent & 0xF0){
        case 0x00:
            __7Seg1byteDisplay(~(0b01110111 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x10:
            __7Seg1byteDisplay(~(0b01000001 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x20:
            __7Seg1byteDisplay(~(0b00111011 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x30:
            __7Seg1byteDisplay(~(0b01101011 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x40:
            __7Seg1byteDisplay(~(0b01001101 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x50:
            __7Seg1byteDisplay(~(0b01101110 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x60:
            __7Seg1byteDisplay(~(0b01111110 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x70:
            __7Seg1byteDisplay(~(0b01000111 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x80:
            __7Seg1byteDisplay(~(0b01111111 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0x90:
            __7Seg1byteDisplay(~(0b01101111 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0xA0:
            __7Seg1byteDisplay(~(0b01011111 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0xB0:
            __7Seg1byteDisplay(~(0b01111100 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0xC0:
            __7Seg1byteDisplay(~(0b00110110 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0xD0:
            __7Seg1byteDisplay(~(0b01111001 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0xE0:
            __7Seg1byteDisplay(~(0b00111110 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
        case 0xF0:
            __7Seg1byteDisplay(~(0b00011110 | (isDisplayDp ? 0b10000000 : 0b00000000)));
            break;
    }
}

void _7SegReset(){
    __7Seg1byteDisplay(~(0b00000000));
    __7Seg1byteDisplay(~(0b00000000));
}

void _7SegSetUpAnimation(_SETUP_STEP_FOR_7SEG __SetupStep){
	switch (__SetupStep) {
		case _SETUP_STEP_START_PROGRAM:
			__7Seg1byteDisplay(__7SEG_NULL_1Byte);
			__7Seg1byteDisplay(__7SEG_ONLY_A_1Byte);
			break;
		case _SETUP_STEP_SETUP_MOTOR:
			__7Seg1byteDisplay(__7SEG_ONLY_A_1Byte);
			__7Seg1byteDisplay(__7SEG_NULL_1Byte);
			break;
		case _SETUP_STEP_NULL1:
			__7Seg1byteDisplay(__7SEG_ONLY_B_1Byte);
			__7Seg1byteDisplay(__7SEG_NULL_1Byte);
			break;
		case _SETUP_STEP_NULL2:
			__7Seg1byteDisplay(__7SEG_ONLY_C_1Byte);
			__7Seg1byteDisplay(__7SEG_NULL_1Byte);
			break;
		case _SETUP_STEP_NULL3:
			__7Seg1byteDisplay(__7SEG_ONLY_D_1Byte);
			__7Seg1byteDisplay(__7SEG_NULL_1Byte);
			break;
		case _SETUP_STEP_NULL4:
			__7Seg1byteDisplay(__7SEG_NULL_1Byte);
			__7Seg1byteDisplay(__7SEG_ONLY_D_1Byte);
			break;
		case _SETUP_STEP_NULL5:
			__7Seg1byteDisplay(__7SEG_NULL_1Byte);
			__7Seg1byteDisplay(__7SEG_ONLY_E_1Byte);
			break;
		case _SETUP_STEP_NULL6:
			__7Seg1byteDisplay(__7SEG_NULL_1Byte);
			__7Seg1byteDisplay(__7SEG_ONLY_F_1Byte);
			break;
		case _SETUP_STEP_FINISH:
			__7Seg1byteDisplay(~__7SEG_ONLY_G_1Byte | ~__7SEG_ONLY_DP_1Byte);
			__7Seg1byteDisplay(~__7SEG_ONLY_G_1Byte | ~__7SEG_ONLY_DP_1Byte);
			break;
	}
}

void __7Seg1byteDisplay(uint8_t _displayContent){
    HAL_GPIO_WritePin(_7SegSetting.__7SegRck_GpioPort, _7SegSetting.__7SegRck_Pin, GPIO_PIN_RESET);
    for (int i = 0; i < 8; i++){
        HAL_GPIO_WritePin(_7SegSetting.__7SegSi_GpioPort, _7SegSetting.__7SegSi_Pin, (_displayContent & (1U << i)) ? GPIO_PIN_SET : GPIO_PIN_RESET);

        HAL_GPIO_WritePin(_7SegSetting.__7SegSck_GpioPort, _7SegSetting.__7SegSck_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(_7SegSetting.__7SegSck_GpioPort, _7SegSetting.__7SegSck_Pin, GPIO_PIN_RESET);
    }

    HAL_GPIO_WritePin(_7SegSetting.__7SegRck_GpioPort, _7SegSetting.__7SegRck_Pin, GPIO_PIN_SET);
}
