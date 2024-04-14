# rogilinkFlex-esp32

現在開発中の汎用通信ライブラリrogiLinkFlexのESP32実装です。
動作未確認です。UART通信のみに対応しています。従来のrogilinkに比べて、送受信するデータ型を柔軟に設定できるようになっています。マイコン同士の通信、マイコンとPCの通信にも使えます。

## Other Environments

- [rogilinkFlex-f446](https://github.com/KeioRoboticsAssociation/rogilinkFlex-f446)
- [rogilinkFlex-ros2](https://github.com/KeioRoboticsAssociation/rogilinkFlex-esp32)

## 使い方(UART通信)


### インクルード
```cpp
#include "UartLink.hpp"
```

### インスタンスの生成
```cpp
UartLink uart(シリアル);
```
シリアル: `HardwareSerial`クラスのインスタンス

### データの送信
```cpp
UartLinkPublisher<データ型1, データ型2, ...> pub(uart, フレームID); // publisherの設定

pub.publish(データ1, データ2, ...);
```

`UartLinkPublisher<char*>`の場合は、`printf`を使うことができます。
```cpp
pub.printf("a: %d, b: %d, c: %d\n", a, b, c);
```

### データの受信
```cpp
UartLinkSubscriber<データ型1, データ型2, ...> sub(uart, フレームID); // subscriberの設定

void callback(データ型1, データ型2, ...) {
    // コールバック関数
}

sub.set_callback(callback); // コールバック関数の設定

void loop() {
    uart.loop(); // メインループ内でloop関数を呼び出す
    delay(1);
}
```

### 使用例
```cpp
#include <Arduino.h>
#include "UartLink.hpp"

UartLink uart(Serial); // UART通信の設定

UartLinkSubscriber<uint8_t, uint16_t, uint8_t> sub(uart, 1); // Subscriber(受信側)の設定
UartLinkPublisher<char*> pub(uart, 2); // Publisher(送信側)の設定

// Subscriberのコールバック関数
void sub_callback(uint8_t a, uint16_t b, uint8_t c) {
    pub.printf("a: %d, b: %d, c: %d\n", a, b, c);
}

// main関数
void setup() {
    sub.set_callback(sub_callback);
}

void loop() {
    uart.loop();
    delay(1);
}
```


