#include <stdio.h>
#include "task_scheduler.h"
#include "motor.h"

extern "C" {
    void app_main(void);
}

void app_main(void)
{
    // C++で実装されたStampFlyの制御ソフト
    printf("StampFly Control Software (C++ Implementation)\n");
    
    // モーター制御初期化
    StampFly::Motor::initialize();
    
    // FreeRTOSマルチタスクシステムを初期化・開始
    StampFly::initializeTasks();
    
    // FreeRTOSスケジューラが動作するため、ここで終了
    // 各タスクは独立して実行される
}
