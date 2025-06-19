# StampS3 シリアル通信ライブラリ

このライブラリは、StampS3でUSBケーブルを使用したシリアル通信を簡単に行うためのラッパー関数群です。

## ファイル構成

- `serial.hpp` - ヘッダーファイル（関数宣言）
- `serial.cpp` - 実装ファイル
- `serial_example.cpp` - 使用例

## 主な機能

### 初期化・終了処理
- `serial_init(baud_rate)` - シリアル通信の初期化
- `serial_deinit()` - シリアル通信の終了処理
- `serial_is_initialized()` - 初期化状態の確認

### データ送信
- `serial_write(str)` - 文字列の送信
- `serial_write_bytes(data, length)` - バイナリデータの送信
- `serial_printf(format, ...)` - printf形式での送信

### データ受信
- `serial_read(buffer, length, timeout_ms)` - データの読み取り
- `serial_read_line(buffer, buffer_size, timeout_ms)` - 1行の読み取り
- `serial_available()` - 受信可能なデータ数の取得

### その他
- `serial_flush()` - 送信バッファのフラッシュ

### ESP_LOGリダイレクト機能
- `serial_redirect_esp_log(enable)` - ESP_LOGをUSBシリアルにリダイレクト
- `serial_log_write(str)` - ログ専用の書き込み関数（内部使用）

## 使用例

### 基本的な使用例

```cpp
#include "serial.hpp"

void app_main()
{
    // シリアル通信を初期化（115200 baud）
    if (serial_init(115200)) {
        // 文字列を送信
        serial_write("Hello, World!\n");
        
        // printf形式で送信
        serial_printf("Value: %d\n", 42);
        
        // データ受信
        char buffer[128];
        int bytes_read = serial_read_line(buffer, sizeof(buffer), 1000);
        if (bytes_read > 0) {
            serial_printf("Received: %s\n", buffer);
        }
        
        // 終了処理
        serial_deinit();
    }
}
```

### ESP_LOGリダイレクト機能の使用例

```cpp
#include "serial.hpp"
#include "esp_log.h"

static const char* TAG = "MAIN";

void app_main()
{
    // シリアル通信を初期化
    serial_init(115200);
    
    // ESP_LOGをUSBシリアルにリダイレクト
    serial_redirect_esp_log(true);
    
    // 通常のESP_LOGがUSBシリアルに出力される
    ESP_LOGI(TAG, "System started");
    ESP_LOGW(TAG, "This is a warning");
    ESP_LOGE(TAG, "This is an error");
    
    // 通常のシリアル出力と混在可能
    serial_printf("Custom message: %d\n", 123);
    
    // ESP_LOGリダイレクトを無効化
    serial_redirect_esp_log(false);
    
    // この後のESP_LOGは通常の出力先に戻る
    ESP_LOGI(TAG, "Log redirect disabled");
}
```

### インタラクティブなコマンド例

シリアルモニタから以下のコマンドを送信できます：
- `log_on` - ESP_LOGリダイレクトを有効化
- `log_off` - ESP_LOGリダイレクトを無効化

## ハードウェア設定

- UART番号: UART_NUM_0
- TX Pin: GPIO_NUM_43
- RX Pin: GPIO_NUM_44
- デフォルトボーレート: 115200

## 注意事項

1. `serial_init()`を最初に呼び出してください
2. 使用後は`serial_deinit()`で終了処理を行ってください
3. 初期化前に他の関数を呼び出すとエラーが返されます
4. `serial_printf()`のバッファサイズは512バイトです
5. タイムアウト時間はミリ秒単位で指定します

## シリアルモニタでの確認方法

1. ESP-IDFプロジェクトをビルド・フラッシュ
2. シリアルモニタを開く：
   ```bash
   idf.py monitor
   ```
3. 送信されたデータがシリアルモニタに表示されます
4. キーボードから入力したデータがESP32で受信されます

## トラブルシューティング

### 通信ができない場合
- USBケーブルが正しく接続されているか確認
- ボーレートが一致しているか確認
- シリアルポートが他のアプリケーションで使用されていないか確認

### 文字化けする場合
- ボーレートの設定を確認
- シリアルモニタの文字エンコーディング設定を確認

### 受信データが取得できない場合
- タイムアウト時間を長めに設定
- `serial_available()`で受信データの有無を確認
