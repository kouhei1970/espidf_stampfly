# StampFly

M5Stack社のStampFly（クアッドコプター）向け制御ソフトウェアプロジェクト。ESP32S3をターゲットとしたC++実装です。

## 概要

このプロジェクトは、M5Stack社のStampFlyの制御ソフトウェアをESP32S3マイクロコントローラー上で実行するためのものです。将来の拡張性を考慮してC++で実装されています。

## StampFlyハードウェア仕様

StampFlyは、M5Stack社が開発したプログラム可能なオープンソースのクアッドコプターキットです。

### 主要コンポーネント
- **メインコントローラー**: M5StampS3（ESP32-S3@Xtensa LX7、8M-FLASH、WiFi、OTG/CDC機能）
- **モーター**: 716-17600kv ブラシレスモーター x 4
- **センサー**:
  - BMI270 6軸姿勢センサー（ジャイロスコープ）
  - BMM150 3軸磁力計（方向検出用、I2Cアドレス: 0x10）
  - BMP280気圧センサー（0-76）@300-1100hPa
  - VL53L3CXV0DH/1 距離センサー x 2（高度維持と障害物回避用、0-2m、最大3m）
  - PMW3901MB-TXQT 光学フローセンサー（位置検出用）
- **電源管理**:
  - 300mAh高電圧リチウムバッテリー（4.35V出力）
  - INA3221AIRGVR 電流/電圧検出（I2Cアドレス: 0x40）
- **インターフェース**:
  - I2C+UARTのGroveインターフェース（拡張用）
  - ESP-NOWプロトコルによるリモートコントロール
- **その他**:
  - WS2812 RGB LED（インタラクションとステータス表示用）
  - パッシブオンボードブザー@5020
  - リセットボタン

### ESP32S3ピン接続情報

#### I2Cインターフェース
| デバイス | SDAピン | SCLピン | I2Cアドレス |
|---------|--------|--------|------------|
| INA3221AIRGVG | G3 | G4 | 0x40 |
| BMM150 | G3 | G4 | 0x10 |
| BMP280 | G3 | G4 | - |
| VL53L3 | G3 | G4 | - |

#### SPIインターフェース
| デバイス | MOSIピン | SCKピン | MISOピン | CSピン |
|---------|---------|--------|---------|-------|
| BMI270 | G14 | G44 | G43 | G46 |
| PMW3901MB-TXQT | G14 | G44 | G43 | CS2 |

#### Groveインターフェース
| インターフェース | SDAピン | SCLピン | その他 |
|----------------|--------|--------|-------|
| Grove (RED) | G13 | G15 | - |
| Grove (BLACK) | - | - | G1 (GROVE I), G2 (GROVE O) |

#### その他のGPIO接続
| デバイス | GPIOピン | 機能 |
|---------|---------|------|
| ブザー | G12 | BEEP |
| WS2812 RGB LED | G14 | RGB制御 |

#### モーターPWM制御用FET接続
| モーター位置 | GPIOピン |
|------------|---------|
| 右前 | G42 |
| 左前 | G5 |
| 右後 | G41 |
| 左後 | G10 |

### 物理仕様
- **サイズ**: 81.5 x 81.5 x 31mm
- **重量**: 36.8g
- **飛行時間**: 約4分
- **動作温度**: 0-40℃

## ソフトウェア機能

- ESP32S3マイクロコントローラーを使用
- C++で実装された制御ソフトウェア
- ESP-IDFフレームワークを使用
- 以下のセンサーとのインターフェース:
  - BMI270（SPI、G14/G44/G43/G46、姿勢制御用）
  - BMM150（I2C、G3/G4、アドレス0x10、方向検出用）
  - BMP280（I2C、G3/G4、高度制御用）
  - VL53L3（I2C、G3/G4、障害物検出用）
  - PMW3901（SPI、G14/G44/G43/CS2、位置制御用）
- モーター制御（PWM、右前:G42、左前:G5、右後:G41、左後:G10）
- バッテリー監視（INA3221経由、I2C、G3/G4、アドレス0x40）
- LED制御（WS2812、G14）
- ブザー制御（G12）
- ESP-NOWプロトコルによる通信
- Groveインターフェース（I2C+UART、G13/G15、G1/G2）を使用した拡張機能

## 必要条件

- ESP-IDF v5.4以上
- C++コンパイラ
- ESP32S3開発ボード

## ビルド方法

```bash
# プロジェクトをクローン
git clone https://github.com/kouhei1970/espidf_stampfly.git
cd espidf_stampfly

# ESP-IDF環境変数を設定
. $IDF_PATH/export.sh

# ビルド
idf.py build

# フラッシュ
idf.py flash
```

## ライセンス

MIT

## 作者

kouhei1970
