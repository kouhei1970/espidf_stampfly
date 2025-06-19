#pragma once

#include <stdint.h>

class DistanceSensor {
public:
    // センサの初期化
    bool initialize();

    // センサの設定
    bool configure();

    // 距離測定
    bool measureDistance(float& distance);

    // 複数回の測定と平均値の取得
    bool measureAverageDistance(float& averageDistance, int numMeasurements);

    // 障害物検出
    bool detectObstacle(float threshold, bool& obstacleDetected);

    // センサのステータス確認
    bool checkStatus();

    // センサのリセット
    bool reset();

    // キャリブレーション
    bool calibrate();

private:
    // 内部で使用する変数や関数
    float maxRange = 3.0f;  // 最大測定距離（メートル）
    float minRange = 0.0f;  // 最小測定距離（メートル）
};
