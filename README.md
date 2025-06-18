# StampFly

ESP32S3をターゲットとしたStampFlyの制御ソフトウェアプロジェクト。C++で実装されています。

## 概要

このプロジェクトは、StampFlyの制御ソフトウェアをESP32S3マイクロコントローラー上で実行するためのものです。将来の拡張性を考慮してC++で実装されています。

## 機能

- ESP32S3マイクロコントローラーを使用
- C++で実装された制御ソフトウェア
- ESP-IDFフレームワークを使用

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
