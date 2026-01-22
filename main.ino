#include "Tone.h"

#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0])) - 1

#define DEBUG 

int lazer_pin_arr[8] = {31, 33, 35, 37, 39, 41, 43, 45};
int buzzer_pin_arr[8] = {2, 4, 3, 5, 6, 7, 8, 9};
int sensor_pin_arr[8] = {A7, A8, A9, A10, A11, A12, A13, A14};

int tones[8] = {NOTE_C6, NOTE_D6, NOTE_E6, NOTE_F6, NOTE_G6, NOTE_A7, NOTE_B7, NOTE_C7};

int analog_tresholds[8] = {115, 80, 90, 80, 115, 115, 120, 115};

void setup() {
  Serial.begin(19200);
  ADCSRA = (ADCSRA & 0b11111000) | 0x04;
  for(int i = 0; i <= ARRAY_SIZE(buzzer_pin_arr); i++) {
    pinMode(lazer_pin_arr[i], OUTPUT);
    digitalWrite(lazer_pin_arr[i], HIGH);
  }
  for(int i = 0; i <= ARRAY_SIZE(buzzer_pin_arr); i++) {
    pinMode(buzzer_pin_arr[i], OUTPUT);
  }
  for(int i = 0; i <= ARRAY_SIZE(sensor_pin_arr); i++) {
    pinMode(sensor_pin_arr[i], INPUT);
  } 
}

//dark → LOWER analogRead()
//When true (1), it is covered.
bool checkSensorState(int index) {
  int value = analogRead(sensor_pin_arr[index]);

  #ifdef DEBUG
    Serial.print("Index: ");
    Serial.print(index + 1);
    Serial.print(" Value: ");
    Serial.print(value);
    Serial.print(" <= threshold ");
    Serial.print(analog_tresholds[index]);
    Serial.print(" ? ");
    Serial.println(value <= analog_tresholds[index] ? "true" : "false");
  #endif

  return value <= analog_tresholds[index];
}

void loop() {
  for(int i = 0; i <= ARRAY_SIZE(buzzer_pin_arr); i++) {
    if(checkSensorState(i)){
      tone(buzzer_pin_arr[i], tones[i]);
      #ifdef DEBUG
        Serial.print("Playing note: ");
        Serial.print(i + 1);
        Serial.print(" tone: ");
        Serial.println(tones[i]);
      #endif
    }else{
      noTone(buzzer_pin_arr[i]);
    }
  }
}
