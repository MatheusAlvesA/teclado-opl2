#include "teclado_read.h"

#define MAX_KEYS_BUFFER_SIZE 30
key_t bufferKeysPressed[MAX_KEYS_BUFFER_SIZE] = {};
uint8_t sizeBufferKeysPressed = 0;

void initTecladoPins() {
  pinMode(EF0, INPUT_PULLUP);
  pinMode(EF1, INPUT_PULLUP);
  pinMode(EF2, INPUT_PULLUP);
  pinMode(EF3, INPUT_PULLUP);
  pinMode(EF4, INPUT_PULLUP);
  pinMode(EF5, INPUT_PULLUP);
  pinMode(EF6, INPUT_PULLUP);
  pinMode(EF7, INPUT_PULLUP);

  pinMode(AB0, OUTPUT);
  pinMode(AB1, OUTPUT);
  pinMode(AB2, OUTPUT);
  pinMode(AB3, OUTPUT);
  pinMode(AB4, OUTPUT);
  pinMode(AB5, OUTPUT);
  pinMode(AB6, OUTPUT);
  pinMode(AB7, OUTPUT);

  digitalWrite(AB0, HIGH);
  digitalWrite(AB1, HIGH);
  digitalWrite(AB2, HIGH);
  digitalWrite(AB3, HIGH);
  digitalWrite(AB4, HIGH);
  digitalWrite(AB5, HIGH);
  digitalWrite(AB6, HIGH);
  digitalWrite(AB7, HIGH);
}

bool isKeyPressed(key_t key) {
  Key keyData = key_list[key];
  digitalWrite(AB0+keyData.AB, LOW);
  int value = 0;
  if(keyData.EF > 1) {
    value = analogRead(EF2+keyData.EF-2);
  } else {
    value = digitalRead(EF0+keyData.EF);
    digitalWrite(AB0+keyData.AB, HIGH);
    return value == LOW;
  }
  digitalWrite(AB0+keyData.AB, HIGH);

  if(value >= keyData.minVal && value <= keyData.minVal+20) {
    return true;
  }
  return false;
}

void updateKeysPressed() {
  uint8_t bufferPointer = 0;
  for(uint8_t i = 0; i < N_KEYS; i++) {
    if(isKeyPressed((key_t)i)) {
      delay(10);
      if(isKeyPressed((key_t)i)) {
        bufferKeysPressed[bufferPointer++] = (key_t)i;
        if(bufferPointer >= MAX_KEYS_BUFFER_SIZE) {
          break;
        }
      }
    }
  }
  sizeBufferKeysPressed = bufferPointer;
}
