#include "motor.h"
#include "driver/ledc.h"
#include "esp_log.h"

namespace StampFly {
    namespace Motor {
        static const char* TAG = "StampFly_Motor";
        
        // PWMチャンネル設定
        static const ledc_channel_t MOTOR_CHANNELS[MOTOR_COUNT] = {
            LEDC_CHANNEL_0,
            LEDC_CHANNEL_1,
            LEDC_CHANNEL_2,
            LEDC_CHANNEL_3
        };
        
        // GPIOピン設定（StampFlyハードウェア仕様に基づく）
        static const int MOTOR_PINS[MOTOR_COUNT] = {
            42, // 右前モーター
            5,  // 左前モーター
            41, // 右後モーター
            10  // 左後モーター
        };
        
        void initialize() {
            ESP_LOGI(TAG, "モーター制御初期化開始");
            
            // LEDCタイマー設定
            ledc_timer_config_t timer_config = {
                .speed_mode = LEDC_LOW_SPEED_MODE,
                .duty_resolution = LEDC_TIMER_10_BIT,
                .timer_num = LEDC_TIMER_0,
                .freq_hz = 1000, // 1kHz PWM周波数
                .clk_cfg = LEDC_AUTO_CLK
            };
            ledc_timer_config(&timer_config);
            
            // 各モーターのPWMチャンネル設定
            for (int i = 0; i < MOTOR_COUNT; i++) {
                ledc_channel_config_t channel_config = {
                    .gpio_num = MOTOR_PINS[i],
                    .speed_mode = LEDC_LOW_SPEED_MODE,
                    .channel = MOTOR_CHANNELS[i],
                    .intr_type = LEDC_INTR_DISABLE,
                    .timer_sel = LEDC_TIMER_0,
                    .duty = 0,
                    .hpoint = 0
                };
                ledc_channel_config(&channel_config);
            }
            
            ESP_LOGI(TAG, "モーター制御初期化完了");
        }
        
        void setMotorOutput(uint8_t motorIndex, uint16_t output) {
            if (motorIndex >= MOTOR_COUNT) {
                ESP_LOGE(TAG, "無効なモーターインデックス: %d", motorIndex);
                return;
            }
            
            if (output > MAX_OUTPUT) {
                output = MAX_OUTPUT;
            }
            
            // 0-1000を0-1023（10bit）に変換
            uint32_t duty = (output * 1023) / MAX_OUTPUT;
            
            ledc_set_duty(LEDC_LOW_SPEED_MODE, MOTOR_CHANNELS[motorIndex], duty);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, MOTOR_CHANNELS[motorIndex]);
        }
        
        void stopAllMotors() {
            ESP_LOGI(TAG, "全モーター停止");
            for (int i = 0; i < MOTOR_COUNT; i++) {
                setMotorOutput(i, 0);
            }
        }
    }
}
