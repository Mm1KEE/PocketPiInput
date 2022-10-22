/*
 * @Author: Mm1KEE
 * @GitHub: https://github.com/Mm1KEE/
 * @Date: 2022-09-18 00:57:54
 * @LastEditTime: 2022-10-23 02:04:47
 * @Description: 
 * 
 * Copyright (c) 2022 by Mm1KEE, All Rights Reserved. 
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
  st.setDebugInfo(0);
  st.setResolution(800, 400);
  st.begin(1, 0);
  //while (!Serial);
  initKeyboard();
}

void loop() {

  //updateRGB();
  //if (!st.isTouched())updateKeyboard();
  //Serial.println("keyboard:"+String(millis()-t));
  //t=millis();
  //for (int i = 0; i <= 27; i++) {
  //}
  //Serial.println("touch:"+String(millis()-t));
  while (1) {
    if (!st.update()) {
      if(untouchedT++>15) break;
    }
    else untouchedT = 0;
    //Serial.println("poll touch " + String(untouchedT));
  }
  //Serial.println("scan keyboard");
  updateKeyboard();
  //if (pinIndex++ >= 70) pinIndex = 0;
  //if(pinIndex==49)Serial.println("touch:"+String(millis()-t));
  /*t = millis();
    for (int i = 0; i <= 69; i++) {
    updateKeyboard(i);
    }
    Serial.println("touch:" + String(millis() - t));*/
}

/*void updateRGB() {
  if (caps) pixels.setPixelColor(0, 0, 0, 0);
  else pixels.setPixelColor(0, 0, 255, 0);
  pixels.show();
}*/