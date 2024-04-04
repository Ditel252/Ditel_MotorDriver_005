/*
<環境説明>
対応モータードライバ: Ditel Motor Driver 005
言語: Mbed (C++)
対応マイコン: Nucleo F303K8
*/

/*
<使用方法>
本モータードライバは2つの関数を使用することで制御することができる

・プログラム開始時
    "motorDriverSetup()"を必ず実行する

・モータードライバを制御する時
    "motorDriverRotate()"を使用する
    この関数は2つ~3つの引数を入れる必要があり内容は下のとおりである
    motorDriverRotate(`モータードライバーのアドレス`, `モータードライバのモード`, `モーターのスピード`)

    それぞれの引数の説明は以下のとおりである
    ・`モータードライバーのアドレス` (第1引数)
        制御したいモータードライバのアドレスを入力する.
        モータードライバのアドレスは, モータードライバに搭載されているADDRスイッチで設定できる

    ・`モータードライバのモード` (第2引数)
        モーターを正転, 反転, ニュートラル, ブレーキのいずれにするのかを入力する
        以下の4つの定数のいずれかで, モーターのモードを選択できる
        MOTOR_FORWARD   … 正転
        MOTOR_REVERSAL  … 反転
        MOTOR_NEUTRAL   … ニュートラル
        MOTOR_BRAKE     … ブレーキ

    ・`モーターのスピード` (第3引数)
        モーターの回転のスピードを入力する
        0~199の範囲で入力することができ, 数値が大きいほどスピードが速い
        ※第2引数のモードが"MOTOR_NEUTRAL", "MOTOR_BRAKE"のどちらかならば入力する必要はない
*/

/*
<注意事項>
本モータードライバは安全対策としてタイムアウト機能が搭載されている
そのため, 0.5秒間指示がなかった場合は, 強制的にニュートラルになる
故に, 回転させ続けるためには0.5秒より短い間隔で"motorDriverRotate()"を実行し, モータードライバに指示を送る必要がある
*/


/*サンプルプログラム*/
#include <mbed.h>
#include "ThisThread.h"
#include "motorDriverController.h"    //コントロール用ヘッダファイルのインクルード


void delay(uint32_t _ms){
    wait_us(_ms * 1000);
}


int main(void){
    motorDriverSetup(); //モータードライバのセットアップ
    
    while(true){
        //正転でだんだん速くしていく
        for(int i = 0; i < 200; i++){
            motorDriverRotate(0b1010, MOTOR_NORMAL_FORWARD, i);
            ThisThread::sleep_for(200ms);
        }

        motorDriverRotate(0b1010, MOTOR_NEUTRAL, NONE);
        ThisThread::sleep_for(2500ms);


        for(int i = 0; i < 200; i++){
            motorDriverRotate(0b1010, MOTOR_LOW_PRECISION_FORWARD, i);
            ThisThread::sleep_for(200ms);
        }

        motorDriverRotate(0b1010, MOTOR_NEUTRAL, NONE);
        ThisThread::sleep_for(2500ms);
    }
}