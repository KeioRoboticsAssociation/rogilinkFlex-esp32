#include <Arduino.h>
#include "RogiLinkFlex/UartLink.hpp"

HardwareSerial serial(1);
UartLink uart(serial);

UartLinkSubscriber<uint8_t, uint16_t, uint8_t> sub(uart, 1);
UartLinkPublisher<char*> pub(uart, 2);

void sub_callback(uint8_t a, uint16_t b, uint8_t c) {
    pub.printf("a: %d, b: %d, c: %d\n", a, b, c);
}

void setup() {
    serial.begin(115200);
    sub.set_callback(sub_callback);
}

void loop() {
    //uart.update();
}