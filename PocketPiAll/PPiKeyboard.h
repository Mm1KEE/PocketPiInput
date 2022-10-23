/*
 * @Author: Mm1KEE
 * @GitHub: https://github.com/Mm1KEE/PocketPiInput
 * @Date: 2022-10-23 17:59:22
 * @LastEditTime: 2022-10-23 18:31:25
 * @Description: PocketPi键盘驱动.使用Caps代替Shift和Fn.
 * 
 * Copyright (c) 2022 by Mm1KEE, All Rights Reserved. 
 */

byte row[10] = {13, A0, A1, A2, A3, 1, 0, 2, 3, 11};
byte col[7] = { 10, 9, 8, 6, 12, 4, 30};
byte pressMax = 3, releaseMax = -2;
char keyValue[5][14] =
{
  {'`', '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', 0xB2},
  { 0xB3, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', 0XD4 },
  { 0xC1, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '\\', 0xB0},
  { 0xB1, 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0xDA, 0x85, 0xD2},
  { 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, ' ', ' ', 0x86, 0x84, 0x87, 0xD8, 0xD9, 0xD7, 0xD5},
};
char keyValueAlt[5][14] =
{
  {'~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '_', '+', 0xB2},
  { 0xB3, 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '{', '}', 0XD4 },
  { 0xC1, 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ':', '\"', '|', 0xB0},
  { 0xB1, 'z', 'x', 'c', 'v', 'b', 'n', 'm', '<', '>', '?', 0xDA, 0x85, 0xD2},
  { 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, ' ', ' ', 0x86, 0x84, 0x87, 0xD8, 0xD9, 0xD7, 0xD5},
};
byte keyStroke[5][14] = {
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};
byte x, y;
long t;
bool caps = false,capsLock=false;
int pinIndex = 0;
int untouchedT = 0;

void initKeyboard() {
  for (int i = 0; i < 7 ; i++)
  {
    pinMode(col[i], OUTPUT);
    digitalWrite(col[i], HIGH);
  }
  for (int j = 0; j < 10; j++)
  {
    pinMode(row[j], INPUT);
    digitalWrite(row[j], HIGH);
  }
  pressMax=abs(pressMax);
  releaseMax=-abs(releaseMax);
  //Serial.println("--------");
}

void keyStrike(byte x, byte y) {
  //Serial.println("press key,x:" + String(x) + ",y:" + String(y) + ",stroke:" + (keyStroke[y][x]) + ",value:" + keyValue[y][x]);
  if (x == 0 & y == 2) {
    //Serial.println("press caps:" + String(caps) + ",stroke:" + (keyStroke[y][x]));
    if (keyStroke[y][x] == 0) {
      caps = !caps;
      capsLock=!capsLock;
      Serial.println("press caps:" + String(caps) + ",stroke:" + (keyStroke[y][x]));
      Keyboard.press(keyValue[y][x]);
      keyStroke[y][x] ++;
    }
    else {}
  }
  else {
    if (keyStroke[y][x] < pressMax) keyStroke[y][x]++;
    else if(keyStroke[y][x]==pressMax){
      Keyboard.press(caps ? keyValueAlt[y][x] : keyValue[y][x]);
      //Serial.println("press key,x:" + String(x) + ",y:" + String(y) + ",stroke:" + (keyStroke[y][x]) + ",value:" + keyValue[y][x]);
      //Keyboard.press(keyValue[y][x]);
      keyStroke[y][x]=pressMax+1;
    }
  }
}

void keyRelease(byte x, byte y) {
  if (x == 0 & y == 2) {
    //Serial.println("release caps:" + String(caps) + ",stroke:" + (keyStroke[y][x]));
    if (keyStroke[y][x] == 1) {
      caps = !caps;
      //Serial.println("release caps:" + String(caps) + ",stroke:" + String(keyStroke[y][x]));
      Keyboard.release(keyValue[y][x]);
      keyStroke[y][x] = 0;
    }
    else {}
  }
  else {
    //Serial.println("release key,x:" + String(x) + ",y:" + String(y) + ",stroke:" + (keyStroke[y][x]) + ",value:" + keyValue[y][x]);
    if (keyStroke[y][x] >releaseMax )keyStroke[y][x]--;
    else  if (keyStroke[y][x]== releaseMax) {
        Keyboard.release(caps ? keyValueAlt[y][x] : keyValue[y][x]);
        keyStroke[y][x] = releaseMax-1;
        //Serial.println("release key,x:" + String(x) + ",y:" + String(y) + ",stroke:" + (keyStroke[y][x]) + ",value:" + keyValue[y][x]);
      }
  }
}

void updateKeyboard() {
  int i = pinIndex / 10;
  int j = pinIndex % 10;
  x = j <= 4 ? i : (13 - i);
  y = j <= 4 ? j : (j - 5);
  //Serial.println("pinIndex:"+String(pinIndex)+",i:" + String(i) + ",j:" + String(j) + ",x:"+String(x)+",y:"+String(y));
  digitalWrite(col[i], LOW);
  if (!digitalRead(row[j])) {
    digitalWrite(col[i], HIGH);
    if (digitalRead(row[j])) {
      //Serial.println("i:" + String(i) + ",j:" + String(j));
      //Serial.print("---" + String(x) + "," + String(y) + ":");
      //Serial.println(String(keyValue[y][x])+",i:"+String(i)+",j:"+String(j));
      //Keyboard.press(keyValue[y][x]);
      //Serial.println("pinIndex:" + String(pinIndex) + ",i:" + String(i) + ",j:" + String(j) + ",x:" + String(x) + ",y:" + String(y));
      keyStrike(x, y);
    }
    else keyRelease(x, y);
  }
  else keyRelease(x, y);
  if (pinIndex++ >= 69) {
    pinIndex = 0;
  }
}
