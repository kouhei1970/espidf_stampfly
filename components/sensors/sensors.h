#pragma once

#include "attitude.h"
#include "compass.h"
#include "barometer.h"
#include "range.h"
#include "optical_flow.h"
#include "power_monitor.h"

class Sensors {
public:
    // センサの初期化
    bool initializeAllSensors();

    // センサの設定
    bool configureAllSensors();

    // センサステータスの確認
    bool checkAllSensorStatus();

    // センサのリセット
    bool resetAllSensors();

    // センサオブジェクトへのアクセサ
    AttitudeSensor& getAttitude() { return attitude; }
    CompassSensor& getCompass() { return compass; }
    BarometerSensor& getBarometer() { return barometer; }
    RangeSensor& getRange() { return range; }
    OpticalFlowSensor& getOpticalFlow() { return opticalFlow; }
    PowerMonitorSensor& getPowerMonitor() { return powerMonitor; }

private:
    // センサインスタンス
    AttitudeSensor attitude;
    CompassSensor compass;
    BarometerSensor barometer;
    RangeSensor range;
    OpticalFlowSensor opticalFlow;
    PowerMonitorSensor powerMonitor;
};
