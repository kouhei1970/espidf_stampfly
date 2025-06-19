#include "serial.hpp"
#include "driver/uart.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_log_buffer.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <inttypes.h>

static const char* TAG = "SERIAL";

// UART設定
#define UART_NUM UART_NUM_0
#define UART_TX_PIN GPIO_NUM_43
#define UART_RX_PIN GPIO_NUM_44
#define UART_RTS_PIN UART_PIN_NO_CHANGE
#define UART_CTS_PIN UART_PIN_NO_CHANGE

#define BUF_SIZE (1024)
#define UART_QUEUE_SIZE (20)

static bool is_initialized = false;
static QueueHandle_t uart_queue;
static bool log_redirected = false;
static vprintf_like_t original_log_func = NULL;

bool serial_init(uint32_t baud_rate)
{
    if (is_initialized) {
        ESP_LOGW(TAG, "Serial already initialized");
        return true;
    }

    // UART設定
    uart_config_t uart_config = {
        .baud_rate = (int)baud_rate,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .rx_flow_ctrl_thresh = 122,
        .source_clk = UART_SCLK_DEFAULT,
        .flags = 0,
    };

    // UARTパラメータ設定
    esp_err_t ret = uart_param_config(UART_NUM, &uart_config);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to configure UART parameters: %s", esp_err_to_name(ret));
        return false;
    }

    // UARTピン設定
    ret = uart_set_pin(UART_NUM, UART_TX_PIN, UART_RX_PIN, UART_RTS_PIN, UART_CTS_PIN);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to set UART pins: %s", esp_err_to_name(ret));
        return false;
    }

    // UARTドライバーインストール
    ret = uart_driver_install(UART_NUM, BUF_SIZE * 2, BUF_SIZE * 2, UART_QUEUE_SIZE, &uart_queue, 0);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to install UART driver: %s", esp_err_to_name(ret));
        return false;
    }

    is_initialized = true;
    ESP_LOGI(TAG, "Serial initialized successfully at %" PRIu32 " baud", baud_rate);
    return true;
}

void serial_deinit(void)
{
    if (!is_initialized) {
        return;
    }

    uart_driver_delete(UART_NUM);
    is_initialized = false;
    ESP_LOGI(TAG, "Serial deinitialized");
}

int serial_write(const char* str)
{
    if (!is_initialized) {
        ESP_LOGE(TAG, "Serial not initialized");
        return -1;
    }

    if (str == NULL) {
        return -1;
    }

    size_t len = strlen(str);
    int bytes_written = uart_write_bytes(UART_NUM, str, len);
    
    if (bytes_written < 0) {
        ESP_LOGE(TAG, "Failed to write to UART");
        return -1;
    }

    return bytes_written;
}

int serial_write_bytes(const uint8_t* data, size_t length)
{
    if (!is_initialized) {
        ESP_LOGE(TAG, "Serial not initialized");
        return -1;
    }

    if (data == NULL || length == 0) {
        return -1;
    }

    int bytes_written = uart_write_bytes(UART_NUM, data, length);
    
    if (bytes_written < 0) {
        ESP_LOGE(TAG, "Failed to write bytes to UART");
        return -1;
    }

    return bytes_written;
}

int serial_printf(const char* format, ...)
{
    if (!is_initialized) {
        ESP_LOGE(TAG, "Serial not initialized");
        return -1;
    }

    if (format == NULL) {
        return -1;
    }

    char buffer[512];
    va_list args;
    va_start(args, format);
    int len = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    if (len < 0) {
        ESP_LOGE(TAG, "Failed to format string");
        return -1;
    }

    if (len >= sizeof(buffer)) {
        ESP_LOGW(TAG, "String truncated in serial_printf");
        len = sizeof(buffer) - 1;
    }

    return serial_write(buffer);
}

int serial_read(uint8_t* buffer, size_t length, uint32_t timeout_ms)
{
    if (!is_initialized) {
        ESP_LOGE(TAG, "Serial not initialized");
        return -1;
    }

    if (buffer == NULL || length == 0) {
        return -1;
    }

    TickType_t timeout_ticks = pdMS_TO_TICKS(timeout_ms);
    int bytes_read = uart_read_bytes(UART_NUM, buffer, length, timeout_ticks);
    
    if (bytes_read < 0) {
        ESP_LOGE(TAG, "Failed to read from UART");
        return -1;
    }

    return bytes_read;
}

int serial_read_line(char* buffer, size_t buffer_size, uint32_t timeout_ms)
{
    if (!is_initialized) {
        ESP_LOGE(TAG, "Serial not initialized");
        return -1;
    }

    if (buffer == NULL || buffer_size == 0) {
        return -1;
    }

    size_t index = 0;
    uint8_t ch;
    TickType_t start_time = xTaskGetTickCount();
    TickType_t timeout_ticks = pdMS_TO_TICKS(timeout_ms);

    while (index < buffer_size - 1) {
        // タイムアウトチェック
        if ((xTaskGetTickCount() - start_time) >= timeout_ticks) {
            break;
        }

        // 1バイト読み取り
        int bytes_read = uart_read_bytes(UART_NUM, &ch, 1, pdMS_TO_TICKS(10));
        if (bytes_read == 1) {
            if (ch == '\n' || ch == '\r') {
                // 改行文字で終了
                break;
            }
            buffer[index++] = ch;
        }
    }

    buffer[index] = '\0';
    return index;
}

int serial_available(void)
{
    if (!is_initialized) {
        return 0;
    }

    size_t available_bytes = 0;
    esp_err_t ret = uart_get_buffered_data_len(UART_NUM, &available_bytes);
    
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Failed to get available data length");
        return 0;
    }

    return (int)available_bytes;
}

void serial_flush(void)
{
    if (!is_initialized) {
        return;
    }

    uart_flush(UART_NUM);
}

bool serial_is_initialized(void)
{
    return is_initialized;
}

int serial_log_write(const char* str)
{
    if (!is_initialized) {
        return -1;
    }

    if (str == NULL) {
        return -1;
    }

    size_t len = strlen(str);
    int bytes_written = uart_write_bytes(UART_NUM, str, len);
    
    if (bytes_written < 0) {
        return -1;
    }

    return bytes_written;
}

static int serial_vprintf_redirect(const char* format, va_list args)
{
    if (!is_initialized) {
        return -1;
    }

    char buffer[512];
    int len = vsnprintf(buffer, sizeof(buffer), format, args);
    
    if (len < 0) {
        return -1;
    }

    if (len >= sizeof(buffer)) {
        len = sizeof(buffer) - 1;
    }

    return serial_log_write(buffer);
}

void serial_redirect_esp_log(bool enable)
{
    if (enable) {
        if (!log_redirected && is_initialized) {
            // 元のログ関数を保存
            original_log_func = esp_log_set_vprintf(serial_vprintf_redirect);
            log_redirected = true;
            
            // リダイレクト開始メッセージ
            serial_write("\n=== ESP_LOG redirected to USB Serial ===\n");
        }
    } else {
        if (log_redirected && original_log_func != NULL) {
            // 元のログ関数に戻す
            esp_log_set_vprintf(original_log_func);
            log_redirected = false;
            original_log_func = NULL;
            
            // リダイレクト終了メッセージ
            serial_write("=== ESP_LOG redirect disabled ===\n\n");
        }
    }
}
