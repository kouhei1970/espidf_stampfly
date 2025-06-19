#include "task_scheduler.h"

namespace StampFly {
    // ログタグ
    static const char* TAG = "StampFly_Tasks";

    // タスクハンドル
    TaskHandle_t controlTaskHandle = nullptr;
    TaskHandle_t imuTaskHandle = nullptr;
    TaskHandle_t mediumSensorTaskHandle = nullptr;
    TaskHandle_t slowSensorTaskHandle = nullptr;
    TaskHandle_t verySlowSensorTaskHandle = nullptr;

    // 制御タスク (333Hz)
    void controlTask(void* pvParameters) {
        ESP_LOGI(TAG, "制御タスク開始 (333Hz)");
        
        TickType_t xLastWakeTime = xTaskGetTickCount();
        const TickType_t xFrequency = pdMS_TO_TICKS(3); // 333Hz = 3ms周期 (FreeRTOSで実現可能な400Hzに最も近い値)
        
        while (true) {
            // TODO: 制御ロジックを実装
            // 現在は空の実装
            
            // 正確な周期で実行するためにvTaskDelayUntilを使用
            vTaskDelayUntil(&xLastWakeTime, xFrequency);
        }
    }

    // IMUタスク (333Hz)
    void imuTask(void* pvParameters) {
        ESP_LOGI(TAG, "IMUタスク開始 (333Hz)");
        
        TickType_t xLastWakeTime = xTaskGetTickCount();
        const TickType_t xFrequency = pdMS_TO_TICKS(3); // 333Hz = 3ms周期 (FreeRTOSで実現可能な400Hzに最も近い値)
        
        while (true) {
            // TODO: IMUデータ処理を実装
            // 現在は空の実装
            
            // 正確な周期で実行するためにvTaskDelayUntilを使用
            vTaskDelayUntil(&xLastWakeTime, xFrequency);
        }
    }

    // 中速度センサタスク (100Hz)
    void mediumSensorTask(void* pvParameters) {
        ESP_LOGI(TAG, "中速度センサタスク開始 (100Hz)");
        
        TickType_t xLastWakeTime = xTaskGetTickCount();
        const TickType_t xFrequency = pdMS_TO_TICKS(10); // 100Hz = 10ms周期
        
        while (true) {
            // TODO: 中速度センサデータ取得を実装
            // 現在は空の実装
            
            // 正確な周期で実行するためにvTaskDelayUntilを使用
            vTaskDelayUntil(&xLastWakeTime, xFrequency);
        }
    }

    // 低速センサタスク (50Hz)
    void slowSensorTask(void* pvParameters) {
        ESP_LOGI(TAG, "低速センサタスク開始 (50Hz)");
        
        TickType_t xLastWakeTime = xTaskGetTickCount();
        const TickType_t xFrequency = pdMS_TO_TICKS(20); // 50Hz = 20ms周期
        
        while (true) {
            // TODO: 低速センサデータ取得を実装
            // 現在は空の実装
            
            // 正確な周期で実行するためにvTaskDelayUntilを使用
            vTaskDelayUntil(&xLastWakeTime, xFrequency);
        }
    }

    // 超低速センサタスク (30Hz)
    void verySlowSensorTask(void* pvParameters) {
        ESP_LOGI(TAG, "超低速センサタスク開始 (30Hz)");
        
        TickType_t xLastWakeTime = xTaskGetTickCount();
        const TickType_t xFrequency = pdMS_TO_TICKS(33); // 30Hz ≈ 33ms周期
        
        while (true) {
            // TODO: 超低速センサデータ取得を実装
            // 現在は空の実装
            
            // 正確な周期で実行するためにvTaskDelayUntilを使用
            vTaskDelayUntil(&xLastWakeTime, xFrequency);
        }
    }

    // タスク初期化関数
    void initializeTasks() {
        ESP_LOGI(TAG, "FreeRTOSマルチタスクシステム初期化開始");
        
        // 制御タスクを作成
        BaseType_t result = xTaskCreate(
            controlTask,           // タスク関数
            "Control Task",        // タスク名
            TASK_STACK_SIZE,       // スタックサイズ
            nullptr,               // パラメータ
            TASK_PRIORITY_CONTROL, // 優先度
            &controlTaskHandle     // タスクハンドル
        );
        if (result != pdPASS) {
            ESP_LOGE(TAG, "制御タスクの作成に失敗しました");
        }

        // IMUタスクを作成
        result = xTaskCreate(
            imuTask,               // タスク関数
            "IMU Task",            // タスク名
            TASK_STACK_SIZE,       // スタックサイズ
            nullptr,               // パラメータ
            TASK_PRIORITY_IMU,     // 優先度
            &imuTaskHandle         // タスクハンドル
        );
        if (result != pdPASS) {
            ESP_LOGE(TAG, "IMUタスクの作成に失敗しました");
        }

        // 中速度センサタスクを作成
        result = xTaskCreate(
            mediumSensorTask,      // タスク関数
            "Medium Sensor Task",  // タスク名
            TASK_STACK_SIZE,       // スタックサイズ
            nullptr,               // パラメータ
            TASK_PRIORITY_MEDIUM_SENSOR, // 優先度
            &mediumSensorTaskHandle // タスクハンドル
        );
        if (result != pdPASS) {
            ESP_LOGE(TAG, "中速度センサタスクの作成に失敗しました");
        }

        // 低速センサタスクを作成
        result = xTaskCreate(
            slowSensorTask,        // タスク関数
            "Slow Sensor Task",    // タスク名
            TASK_STACK_SIZE,       // スタックサイズ
            nullptr,               // パラメータ
            TASK_PRIORITY_SLOW_SENSOR, // 優先度
            &slowSensorTaskHandle  // タスクハンドル
        );
        if (result != pdPASS) {
            ESP_LOGE(TAG, "低速センサタスクの作成に失敗しました");
        }

        // 超低速センサタスクを作成
        result = xTaskCreate(
            verySlowSensorTask,    // タスク関数
            "Very Slow Sensor Task", // タスク名
            TASK_STACK_SIZE,       // スタックサイズ
            nullptr,               // パラメータ
            TASK_PRIORITY_VERY_SLOW_SENSOR, // 優先度
            &verySlowSensorTaskHandle // タスクハンドル
        );
        if (result != pdPASS) {
            ESP_LOGE(TAG, "超低速センサタスクの作成に失敗しました");
        }

        ESP_LOGI(TAG, "全タスクが作成されました");
    }
}
