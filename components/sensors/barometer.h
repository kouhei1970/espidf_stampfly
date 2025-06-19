#pragma once

#include <stdint.h>

class BarometerSensor {
public:
    // センサの初期化
    bool initialize();

    // センサの設定
    bool configure();

    // 気圧データの読み取り
    bool readPressure(float& pressure);

    // 温度データの読み取り
    bool readTemperature(float& temperature);

    // 高度の計算
    bool calculateAltitude(float& altitude);

    // センサのステータス確認
    bool checkStatus();

    // センサのリセット
    bool reset();

    // キャリブレーション
    bool calibrate();

private:
    // 内部で使用する変数や関数
    float seaLevelPressure = 1013.25f; // 標準海面気圧
};
