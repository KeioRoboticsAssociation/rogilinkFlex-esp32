#include <Arduino.h>
#include "RogiLinkFlex/UartLink.hpp"

TaskHandle_t thp[6];//マルチスレッドのタスクハンドル格納用

UartLink uart(Serial);

UartLinkSubscriber<uint8_t, uint16_t, uint8_t> sub(uart, 1);
UartLinkPublisher<char*> pub(uart, 2);

void sub_callback(uint8_t a, uint16_t b, uint8_t c) {
    pub.printf("a: %d, b: %d, c: %d\n", a, b, c);
}

void uart_loop_core(void* pvParameters) {
    while (true) {
        uart.loop();
        delay(1);
    }
}

void setup() {
    Serial.begin(115200);
    sub.set_callback(sub_callback);
    xTaskCreatePinnedToCore(uart_loop_core, "uart_loop_core", 4096, NULL, 4, &thp[0], 1);
}


void loop() {
    delay(100);
    pub.printf("Hello, World!\n");
}