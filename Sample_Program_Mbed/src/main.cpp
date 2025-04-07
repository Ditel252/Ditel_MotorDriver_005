/*サンプルプログラム*/
#include <mbed.h>
#include "motorDriverController.hpp"    //コントロール用ヘッダファイルのインクルード

int main(void){
    motorDriverSetup(); //モータードライバのセットアップ

    while(true){
        //正転でだんだん速くしていく
        for(int i = 0; i < 50000; i+=250){
            normalMotorDriverRotate(0b0001, MOTOR_FORWARD, i);
            ThisThread::sleep_for(2000ms);
        }

        ThisThread::sleep_for(1000ms);

        //ニュートラルにする
        normalMotorDriverRotate(0b0001, MOTOR_NEUTRAL);
        ThisThread::sleep_for(1000ms);


        //反転でだんだん速くしていく
        for(int i = 0; i < 50000; i+=250){
            normalMotorDriverRotate(0b0001, MOTOR_REVERSAL, i);
            ThisThread::sleep_for(2000ms);
        }

        ThisThread::sleep_for(1000ms);


        //ブレーキをかける
        normalMotorDriverRotate(0b0001, MOTOR_BRAKE);
        ThisThread::sleep_for(1000ms);
    }
}