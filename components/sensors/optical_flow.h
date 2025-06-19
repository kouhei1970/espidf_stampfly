#pragma once

#include <stdint.h>

class OpticalFlowSensor {
public:
    // センサの初期化
    bool initialize();

    // センサの設定
    bool configure();

    // 光学フロー（X軸）の読み取り
    bool readFlowX(float& flowX);

    // 光学フロー（Y軸）の読み取り
    bool readFlowY(float& flowY);

    // 光学フロー（X, Y軸）の同時読み取り
    bool readFlowXY(float& flowX, float& flowY);

    // 移動距離の推定
    bool estimateMovement(float& distanceX, float& distanceY);

    // センサのステータス確認
    bool checkStatus();

    // センサのリセット
    bool reset();

    // キャリブレーション
    bool calibrate();

private:
    // 内部で使用する変数や関数
    float pixelsPerMeter = 0.0f;  // ピクセルから実際の距離への変換係数
    float maxFlowRate = 0.0f;     // 最大光学フローレート
};
