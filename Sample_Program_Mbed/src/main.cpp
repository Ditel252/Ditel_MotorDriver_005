/*サンプルプログラム*/
#include <mbed.h>
#include "motorDriverController.hpp"    //コントロール用ヘッダファイルのインクルード

/*
//ノーマルモードの例
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
*/

///*
//PIDモードの例
int main(void){
    motorDriverSetup(); //モータードライバのセットアップ

    ThisThread::sleep_for(1000ms);

    setPIDGain(0b0001, 2.0, 5.0, 0.05); //ゲイン設定
    
    ThisThread::sleep_for(3000ms);

    setPIDControlCondition(0b0001, true);   //PIDコントロール有効化


    while(true){
        //正転でだんだん速くしていく
        for(int i = 7000; i < 15000; i+=400){
            PIDMotorDriverRote(0b0001, MOTOR_FORWARD, i);
            ThisThread::sleep_for(100ms);
        }

        for(int i = 0; i < 10; i++){
            PIDMotorDriverRote(0b0001, MOTOR_FORWARD, 15000);
            ThisThread::sleep_for(100ms);
        }

        // //ニュートラルにする
        // for(int i = 0; i < 10; i++){
        //     PIDMotorDriverRote(0b0001, MOTOR_NEUTRAL);
        //     ThisThread::sleep_for(100ms);
        // }


        //反転でだんだん速くしていく
        for(int i = 7000; i < 15000; i+=400){
            PIDMotorDriverRote(0b0001, MOTOR_REVERSAL, i);
            ThisThread::sleep_for(100ms);
        }

        for(int i = 0; i < 10; i++){
            PIDMotorDriverRote(0b0001, MOTOR_REVERSAL, 15000);
            ThisThread::sleep_for(100ms);
        }


        //ブレーキをかける
        for(int i = 0; i < 10; i++){
            PIDMotorDriverRote(0b0001, MOTOR_BRAKE);
            ThisThread::sleep_for(100ms);
        }
    }
}
//*/