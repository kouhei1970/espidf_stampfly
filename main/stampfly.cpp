#include <stdio.h>
#include "task_scheduler.h"

extern "C" {
    void app_main(void);
}

void app_main(void)
{
    // C++で実装されたStampFlyの制御ソフト
    printf("StampFly Control Software (C++ Implementation)\n");
    
    // FreeRTOSマルチタスクシステムを初期化・開始
    StampFly::initializeTasks();
    
    // FreeRTOSスケジューラが動作するため、ここで終了
    // 各タスクは独立して実行される
}
