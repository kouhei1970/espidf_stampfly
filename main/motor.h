#ifndef STAMPFLY_MOTOR_H
#define STAMPFLY_MOTOR_H

#include <stdint.h>

namespace StampFly {
    namespace Motor {
        // モーター制御の初期化
        void initialize();
        
        // モーター出力設定 (0-1000の範囲)
        void setMotorOutput(uint8_t motorIndex, uint16_t output);
        
        // 全モーター停止
        void stopAllMotors();
        
        // モーター数
        constexpr uint8_t MOTOR_COUNT = 4;
        
        // 最大出力値
        constexpr uint16_t MAX_OUTPUT = 1000;
    }
}

#endif // STAMPFLY_MOTOR_H
