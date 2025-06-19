#ifndef STAMPFLY_TASK_SCHEDULER_H
#define STAMPFLY_TASK_SCHEDULER_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_log.h"
#include <cstdint>

namespace StampFly {
    // タスクの優先度 (数値が大きいほど優先度が高い)
    constexpr UBaseType_t TASK_PRIORITY_CONTROL = 5;
    constexpr UBaseType_t TASK_PRIORITY_IMU = 4;
    constexpr UBaseType_t TASK_PRIORITY_MEDIUM_SENSOR = 3;
    constexpr UBaseType_t TASK_PRIORITY_SLOW_SENSOR = 2;
    constexpr UBaseType_t TASK_PRIORITY_VERY_SLOW_SENSOR = 1;

    // タスクのスタックサイズ (必要に応じて調整)
    constexpr uint32_t TASK_STACK_SIZE = 4096;

    // タスクハンドル
    extern TaskHandle_t controlTaskHandle;
    extern TaskHandle_t imuTaskHandle;
    extern TaskHandle_t mediumSensorTaskHandle;
    extern TaskHandle_t slowSensorTaskHandle;
    extern TaskHandle_t verySlowSensorTaskHandle;

    // タスク関数のプロトタイプ
    void controlTask(void* pvParameters);
    void imuTask(void* pvParameters);
    void mediumSensorTask(void* pvParameters);
    void slowSensorTask(void* pvParameters);
    void verySlowSensorTask(void* pvParameters);

    // タスク初期化関数
    void initializeTasks();
}

#endif // STAMPFLY_TASK_SCHEDULER_H
