#include <stdio.h>
#include <inttypes.h>
#include "task_scheduler.h"
#include "serial.hpp"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"

static const char* TAG = "STAMPFLY_MAIN";

extern "C" {
    void app_main(void);
}

void app_main(void)
{
    // シリアル通信を初期化
    if (!serial_init(115200)) {
        printf("Failed to initialize serial communication\n");
        return;
    }
    
    // ESP_LOGをUSBシリアルにリダイレクト
    serial_redirect_esp_log(true);
    
    // C++で実装されたStampFlyの制御ソフト
    ESP_LOGI(TAG, "=== StampFly Control Software (C++ Implementation) ===");
    ESP_LOGI(TAG, "System startup at %lld ms", esp_timer_get_time() / 1000);
    
    // システム情報を表示
    ESP_LOGI(TAG, "ESP-IDF Version: %s", esp_get_idf_version());
    ESP_LOGI(TAG, "Free heap size: %" PRIu32 " bytes", esp_get_free_heap_size());
    ESP_LOGI(TAG, "Minimum free heap size: %" PRIu32 " bytes", esp_get_minimum_free_heap_size());
    
    // シリアル通信の動作確認
    serial_printf("StampFly Serial Communication Test\n");
    serial_printf("System ready for operation\n");
    
    // FreeRTOSマルチタスクシステムを初期化・開始
    ESP_LOGI(TAG, "Initializing FreeRTOS multi-task system...");
    StampFly::initializeTasks();
    
    ESP_LOGI(TAG, "All tasks initialized successfully");
    ESP_LOGI(TAG, "System is now running in multi-task mode");
    
    // メインタスクは監視タスクとして動作
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xFrequency = pdMS_TO_TICKS(5000) > 0 ? pdMS_TO_TICKS(5000) : 1; // 5秒周期、最小1tick
    
    while (true) {
        // システム状態を定期的に報告
        ESP_LOGI(TAG, "=== System Status Report ===");
        ESP_LOGI(TAG, "Uptime: %lld ms", esp_timer_get_time() / 1000);
        ESP_LOGI(TAG, "Free heap: %" PRIu32 " bytes", esp_get_free_heap_size());
        ESP_LOGI(TAG, "Min free heap: %" PRIu32 " bytes", esp_get_minimum_free_heap_size());
        
        // タスク状態を確認
        UBaseType_t taskCount = uxTaskGetNumberOfTasks();
        ESP_LOGI(TAG, "Active tasks: %u", (unsigned int)taskCount);
        
        serial_printf("--- StampFly Status ---\n");
        serial_printf("Uptime: %lld ms\n", esp_timer_get_time() / 1000);
        serial_printf("Free heap: %" PRIu32 " bytes\n", esp_get_free_heap_size());
        serial_printf("Active tasks: %u\n", (unsigned int)taskCount);
        serial_printf("System running normally\n\n");
        
        // 5秒待機
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}
