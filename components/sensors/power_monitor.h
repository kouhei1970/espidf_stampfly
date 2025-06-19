#pragma once

#include <stdint.h>

class PowerMonitorSensor {
public:
    // センサの初期化
    bool initialize();

    // センサの設定
    bool configure();

    // チャンネル1の電圧読み取り
    bool readVoltageChannel1(float& voltage);

    // チャンネル2の電圧読み取り
    bool readVoltageChannel2(float& voltage);

    // チャンネル3の電圧読み取り
    bool readVoltageChannel3(float& voltage);

    // チャンネル1の電流読み取り
    bool readCurrentChannel1(float& current);

    // チャンネル2の電流読み取り
    bool readCurrentChannel2(float& current);

    // チャンネル3の電流読み取り
    bool readCurrentChannel3(float& current);

    // 電力消費の計算
    bool calculatePower(float& power, int channel);

    // バッテリー残量の推定
    bool estimateBatteryRemaining(float& percentage);

    // センサのステータス確認
    bool checkStatus();

    // センサのリセット
    bool reset();

private:
    // 内部で使用する変数や関数
    float shuntResistor = 0.1f;  // シャント抵抗値（オーム）
    float maxCurrent = 2.0f;     // 最大電流値（アンペア）
};
