#pragma once

#include <stdint.h>

class CompassSensor {
public:
    // センサの初期化
    bool initialize();

    // センサの設定
    bool configure();

    // 磁力データの読み取り
    bool readMagnetometer(float& x, float& y, float& z);

    // センサのステータス確認
    bool checkStatus();

    // センサのリセット
    bool reset();

    // キャリブレーション
    bool calibrate();

private:
    // 内部で使用する変数や関数
};
