/*サンプルプログラム*/
#include <mbed.h>
#include "motorDriverController.hpp"    //コントロール用ヘッダファイルのインクルード

int main(void){
    motorDriverSetup(); //モータードライバのセットアップ

    while(true){
        //正転でだんだん速くしていく
        for(int i = 0; i < 60000; i+=235){
            normalMotorDriverRotate(0b0001, MOTOR_FORWARD, i);
            ThisThread::sleep_for(100ms);
        }

        ThisThread::sleep_for(1000ms);

        //ニュートラルにする
        normalMotorDriverRotate(0b0001, MOTOR_NEUTRAL);
        ThisThread::sleep_for(1000ms);


        //反転でだんだん速くしていく
        for(int i = 0; i < 60000; i+=235){
            normalMotorDriverRotate(0b0001, MOTOR_REVERSAL, i);
            ThisThread::sleep_for(100ms);
        }

        ThisThread::sleep_for(400ms);


        //ブレーキをかける
        normalMotorDriverRotate(0b0001, MOTOR_BRAKE);
        ThisThread::sleep_for(1000ms);

        normalMotorDriverRotate(0b0001, MOTOR_REVERSAL, 60000);
        ThisThread::sleep_for(1000ms);
    }
}