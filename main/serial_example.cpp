#include "serial.hpp"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_timer.h"
#include <string.h>

static const char* TAG = "SERIAL_EXAMPLE";

/**
 * @brief シリアル通信のサンプル使用例
 */
void serial_example_task(void *pvParameters)
{
    // シリアル通信を初期化（115200 baud）
    if (!serial_init(115200)) {
        ESP_LOGE(TAG, "Failed to initialize serial");
        vTaskDelete(NULL);
        return;
    }

    ESP_LOGI(TAG, "Serial example started");

    // ESP_LOGをUSBシリアルにリダイレクト
    serial_redirect_esp_log(true);

    // 基本的な文字列送信
    serial_write("Hello, StampS3!\n");
    
    // printf形式での送信
    serial_printf("System started at %d ms\n", (int)(esp_timer_get_time() / 1000));
    
    // ESP_LOGのテスト（これらはUSBシリアルに出力される）
    ESP_LOGI(TAG, "This is an INFO log via USB Serial");
    ESP_LOGW(TAG, "This is a WARNING log via USB Serial");
    ESP_LOGE(TAG, "This is an ERROR log via USB Serial");
    
    int counter = 0;
    char read_buffer[128];
    
    while (1) {
        // カウンターを送信
        serial_printf("Counter: %d\n", counter);
        
        // ESP_LOGでもカウンターを出力
        ESP_LOGI(TAG, "ESP_LOG Counter: %d", counter);
        
        counter++;
        
        // 受信データがあるかチェック
        if (serial_available() > 0) {
            // 1行読み取り
            int bytes_read = serial_read_line(read_buffer, sizeof(read_buffer), 100);
            if (bytes_read > 0) {
                serial_printf("Received: %s (length: %d)\n", read_buffer, bytes_read);
                ESP_LOGI(TAG, "ESP_LOG Received: %s", read_buffer);
                
                // 特定のコマンドでログリダイレクトを切り替え
                if (strcmp(read_buffer, "log_off") == 0) {
                    serial_redirect_esp_log(false);
                    serial_write("ESP_LOG redirect disabled\n");
                } else if (strcmp(read_buffer, "log_on") == 0) {
                    serial_redirect_esp_log(true);
                    serial_write("ESP_LOG redirect enabled\n");
                }
            }
        }
        
        // 1秒待機
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/**
 * @brief シリアル通信例の開始
 */
void start_serial_example(void)
{
    xTaskCreate(serial_example_task, "serial_example", 4096, NULL, 5, NULL);
}
