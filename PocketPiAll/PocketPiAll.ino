/*
   @Author: Mm1KEE
   @GitHub: https://github.com/Mm1KEE/PocketPiInput
   @Date: 2022-09-18 00:57:54
 * @LastEditTime: 2022-10-23 18:34:03
   @Description: PocketPi驱动，包含键盘、触摸、大写锁定灯、电量指示灯.详情见上方网址的READDME.

   Copyright (c) 2022 by Mm1KEE, All Rights Reserved.
*/
#include <Keyboard.h>
#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include <SmoothTouch.h>
#include "PPiKeyboard.h"

Adafruit_NeoPixel pixels(2, 7, NEO_GRB + NEO_KHZ800);
XPT2046_Touchscreen touch(PIN_SPI_SS, 255);
SmoothTouch st(touch, 2);

void setup() {
  Keyboard.begin();
  Serial.begin(115200);
  pixels.begin();
  pixels.clear();
  st.setDebugInfo(0);
  st.setResolution(800, 400);
  st.begin(1, 0);
  //while (!Serial && millis()<1000);
  initKeyboard();
}

void loop() {
  for (int i = 0; i <= 9; i++) {
    st.update();
  }
  updateKeyboard();
  updateRGB();
}

void updateRGB() {
  pixels.setPixelColor(0, 0, 5 * capsLock, 0);
  int v = readBattery();
  byte r = max(0, 26 - v);
  byte g = max(0, v - 24);
  //Serial.println(String(v) + "," + String(r) + "," + String(g));
  pixels.setPixelColor(1, r, g, 0);
  pixels.show();
}

unsigned int readBattery() {
  digitalWrite(PIN_SPI_SS, LOW);
  SPI.transfer(0xA5);
  uint16_t battery_voltage = SPI.transfer(0xA5);
  SPI.endTransaction();
  digitalWrite(PIN_SPI_SS, HIGH);
  return battery_voltage;
}
