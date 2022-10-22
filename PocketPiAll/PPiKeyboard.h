byte row[10] = {13, A0, A1, A2, A3, 1, 0, 2, 3, 11};
//byte row[5] = {13, A0, A1, A2, A3};
byte col[7] = { 10, 9, 8, 6, 12, 4, 30};
//byte input[5][14];
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
bool caps = false;
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
  //Serial.println("--------");
}

void keyStrike(byte x, byte y) {
  //Serial.println("press key,x:" + String(x) +",y:"+String(y)+ ",stroke:" + (keyStroke[y][x])+",value:"+keyValue[y][x]);
  if (x == 0 & y == 2) {
    //Serial.println("press caps:" + String(caps) + ",stroke:" + (keyStroke[y][x]));
    if (keyStroke[y][x] == 0) {
      //caps = !caps;
      if (caps) caps = false;
      else caps = true;
      Serial.println("press caps:" + String(caps) + ",stroke:" + (keyStroke[y][x]));
      Keyboard.press(keyValue[y][x]);
      keyStroke[y][x] ++;
    }
    else {}
  }
  else if (keyStroke[y][x]++ >= 1) {
    Keyboard.press(caps ? keyValueAlt[y][x] : keyValue[y][x]);
    //keyStroke[y][x]++;
    //Serial.println("press key,x:" + String(x) + ",y:" + String(y) + ",stroke:" + (keyStroke[y][x]) + ",value:" + keyValue[y][x]);
    Keyboard.press(keyValue[y][x]);
  }
}

void keyRelease(byte x, byte y) {
  if (x == 0 & y == 2) {
    //Serial.println("release caps:" + String(caps) + ",stroke:" + (keyStroke[y][x]));
    if (keyStroke[y][x] == 1) {
      //caps = !caps;
      if (caps) caps = false;
      else caps = true;
      Serial.println("release caps:" + String(caps) + ",stroke:" + String(keyStroke[y][x]));
      Keyboard.release(keyValue[y][x]);
      keyStroke[y][x]=0;
    }
    else {}
  }
  else {
    //Serial.println("release key,x:" + String(x) + ",y:" + String(y) + ",stroke:" + (keyStroke[y][x]) + ",value:" + keyValue[y][x]);
    if ((keyStroke[y][x])-- <= 0) 
      Keyboard.release(caps ? keyValueAlt[y][x] : keyValue[y][x]);
      keyStroke[y][x] = 0;
      //Serial.println("release key,x:" + String(x) + ",y:" + String(y) + ",stroke:" + (keyStroke[y][x]) + ",value:" + keyValue[y][x]);
      //if (x == 0 & y == 2) caps = !caps;}
    
  }
}

void updateKeyboard() {
  int i = pinIndex / 10;
  int j = pinIndex % 10;
  //long t = millis();
  if (j <= 4) {
    x = i;
    y = j;
  }
  else {
    x = 13 - i;
    y = j - 5;
  }
  //x = j <= 4 ? i : (13 - i);
  //y = j <= 4 ? j : (j - 5);
  //Serial.println("pinIndex:"+String(pinIndex)+",i:" + String(i) + ",j:" + String(j) + ",x:"+String(x)+",y:"+String(y));
  digitalWrite(col[i], LOW);
  if (!digitalRead(row[j])) {
    digitalWrite(col[i], HIGH);
    if (digitalRead(row[j])) {
      //Serial.println("i:" + String(i) + ",j:" + String(j));
      //Serial.print("---" + String(x) + "," + String(y) + ":");
      //Serial.println(String(keyValue[y][x])+",i:"+String(i)+",j:"+String(j));
      //Keyboard.press(keyValue[y][x]);
      Serial.println("pinIndex:"+String(pinIndex)+",i:" + String(i) + ",j:" + String(j) + ",x:"+String(x)+",y:"+String(y));
      keyStrike(x, y);
    }
    else keyRelease(x, y);
  }
  else keyRelease(x, y);
  if (pinIndex++ > 69) {
    pinIndex = 0;
    //t = millis();
    }
  //Serial.println("interval:" + String(millis() - t));
  //long t1 = millis();
  //Serial.println("interval:" + String(t1 - t));
  //Serial.println(String(pinIndex) + ":" + String(millis() - t));
}
