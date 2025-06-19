#pragma once

#include <stdint.h>

class AttitudeSensor {
public:
    // センサの初期化
    bool initialize();

    // センサの設定
    bool configure();

    // 加速度データの読み取り
    bool readAccelerometer(float& x, float& y, float& z);

    // ジャイロスコープデータの読み取り
    bool readGyroscope(float& x, float& y, float& z);

    // センサのステータス確認
    bool checkStatus();

    // センサのリセット
    bool reset();

private:
    // 内部で使用する変数や関数
};
