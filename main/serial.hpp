#ifndef SERIAL_HPP
#define SERIAL_HPP

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief シリアル通信の初期化
 * 
 * @param baud_rate ボーレート (デフォルト: 115200)
 * @return true 初期化成功
 * @return false 初期化失敗
 */
bool serial_init(uint32_t baud_rate = 115200);

/**
 * @brief シリアル通信の終了処理
 */
void serial_deinit(void);

/**
 * @brief 文字列をシリアルポートに送信
 * 
 * @param str 送信する文字列
 * @return int 送信したバイト数、エラーの場合は-1
 */
int serial_write(const char* str);

/**
 * @brief バイナリデータをシリアルポートに送信
 * 
 * @param data 送信するデータ
 * @param length データ長
 * @return int 送信したバイト数、エラーの場合は-1
 */
int serial_write_bytes(const uint8_t* data, size_t length);

/**
 * @brief printf形式でシリアルポートに送信
 * 
 * @param format フォーマット文字列
 * @param ... 可変引数
 * @return int 送信したバイト数、エラーの場合は-1
 */
int serial_printf(const char* format, ...);

/**
 * @brief シリアルポートからデータを読み取り
 * 
 * @param buffer 読み取りバッファ
 * @param length バッファサイズ
 * @param timeout_ms タイムアウト時間（ミリ秒）
 * @return int 読み取ったバイト数、エラーまたはタイムアウトの場合は-1
 */
int serial_read(uint8_t* buffer, size_t length, uint32_t timeout_ms = 1000);

/**
 * @brief シリアルポートから1行読み取り（改行文字まで）
 * 
 * @param buffer 読み取りバッファ
 * @param buffer_size バッファサイズ
 * @param timeout_ms タイムアウト時間（ミリ秒）
 * @return int 読み取ったバイト数、エラーまたはタイムアウトの場合は-1
 */
int serial_read_line(char* buffer, size_t buffer_size, uint32_t timeout_ms = 1000);

/**
 * @brief 受信可能なデータ数を取得
 * 
 * @return int 受信可能なバイト数
 */
int serial_available(void);

/**
 * @brief 送信バッファをフラッシュ
 */
void serial_flush(void);

/**
 * @brief シリアルポートが初期化されているかチェック
 * 
 * @return true 初期化済み
 * @return false 未初期化
 */
bool serial_is_initialized(void);

/**
 * @brief ESP_LOGをUSBシリアルにリダイレクト
 * 
 * @param enable true: USBシリアルにリダイレクト, false: デフォルトに戻す
 */
void serial_redirect_esp_log(bool enable);

/**
 * @brief カスタムログ出力関数（内部使用）
 * 
 * @param str ログ文字列
 * @return int 出力したバイト数
 */
int serial_log_write(const char* str);

#ifdef __cplusplus
}
#endif

#endif // SERIAL_HPP
