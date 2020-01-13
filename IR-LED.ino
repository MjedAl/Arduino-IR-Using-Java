#include <Keypad.h>
#include "Keyboard.h"
#include <IRremote.h>

IRsend irsend;

int Sensor = 9;


#define R_LED_On 0x61D608F7
#define R_LED_OFF 0x61D648B7
#define R_LED_White 0x61D610EF
#define R_LED_R 0x61D620DF
#define R_LED_G 0x61D6A05F
#define R_LED_B 0x61D6609F
#define R_LED_Y 0x61D618E7
#define R_LED_P 0x61D658A7
#define R_LED_C 0x61D69867
#define D_LED_On 0xF7C03F
#define D_LED_OFF 0xF740BF
#define D_LED_Fade 0xF7C837
#define D_LED_Green 0xF720DF
#define D_UP 0xF700FF
#define D_DOWN 0xF7807F
#define D_LED_Blue 0xF7A05F
#define D_LED_Red 0xF7609F

boolean UP_stat = false;
boolean Down_stat = false;
boolean UP_DOWN = false;
boolean D_minMax = true;
boolean Here = true;


void setup() {
  Serial.begin(9600);
  pinMode(Sensor, INPUT);
  Keyboard.begin();

  irsend.sendNEC(D_LED_On, 32);
  delay(50);
  D_minMax = false;
  D_MinOrMax();
}

void home() {
  Here = true;
  Keyboard.press(KEY_BACKSPACE);
  Keyboard.releaseAll();
  delay(1000);
  irsend.sendNEC(R_LED_On, 32);
  delay(50);
  irsend.sendNEC(D_LED_On, 32);
  delay(50);
  irsend.sendNEC(D_LED_Green, 32);
  delay(50);
  D_minMax = false;
  D_MinOrMax();
  UP_DOWN = true;
  UP_stat = true;
  Down_stat = true;
}

void loop() {
  if (!Here) {// if i'm not here
    if (digitalRead(Sensor)) {
      home();
    }
  } else {
    if (Serial.available() > 0) {
      byte incomingByte;
      incomingByte = Serial.read();
      if (incomingByte != -1) {
        if (incomingByte == 1) {
          irsend.sendNEC(R_LED_OFF, 32);
        } else if (incomingByte == 2) {
          irsend.sendNEC(R_LED_On, 32);
        } else if (incomingByte == 3) {
          irsend.sendNEC(R_LED_White, 32);
        } else if (incomingByte == 4) {
          irsend.sendNEC(R_LED_R, 32);
        } else if (incomingByte == 5) {
          irsend.sendNEC(R_LED_G, 32);
        } else if (incomingByte == 6) {
          irsend.sendNEC(R_LED_B, 32);
        } else if (incomingByte == 7) {
          irsend.sendNEC(R_LED_Y, 32);
        } else if (incomingByte == 8) {
          irsend.sendNEC(R_LED_P, 32);
        } else if (incomingByte == 9) {
          irsend.sendNEC(R_LED_C, 32);
        } else if (incomingByte == 10) {
          irsend.sendNEC(D_LED_On, 32);
        } else if (incomingByte == 11) {
          irsend.sendNEC(D_LED_OFF, 32);
        } else if (incomingByte == 12) {
          irsend.sendNEC(D_LED_Red, 32);
        } else if (incomingByte == 13) {
          irsend.sendNEC(D_LED_Green, 32);
        } else if (incomingByte == 14) {
          irsend.sendNEC(D_LED_Blue, 32);
        } else if (incomingByte == 15) {
          D_minMax = true;
          D_MinOrMax();
        } else if (incomingByte == 16) {
          D_minMax = false;
          D_MinOrMax();
        } else if (incomingByte == 17) {
          irsend.sendNEC(D_LED_Fade, 32);
        } else if (incomingByte == 18) {
          leave();
        }
        incomingByte = -1;
      }
    }
  }
}

void leave() {
  // shortcut to the autohotkey script
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_F5);
  Keyboard.releaseAll();
  delay(500);
  
  //irsend.sendNEC(AC_OFF, 32);
  //delay(50);
  //delay(500);
  D_minMax = true;
  D_MinOrMax();
  irsend.sendNEC(D_LED_OFF, 32);
  delay(50);
  delay(5000);
  irsend.sendNEC(R_LED_OFF, 32);
  delay(50);
  irsend.sendNEC(R_LED_OFF, 32);

  Here = false;
  delay(20000);
  return;
}
void D_MinOrMax() {
  if (D_minMax) {
    for (int i = 0; i < 70; i++) {
      irsend.sendNEC(D_DOWN, 32);
      delay(50);
    }
    delay(50);
    D_minMax = false;
  } else {
    for (int i = 0; i < 70; i++) {
      irsend.sendNEC(D_UP, 32);
      delay(50);
    }
    delay(50);
    D_minMax = true;
  }
}
