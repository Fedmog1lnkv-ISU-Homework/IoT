#include <SoftwareSerial.h>
#include <EEPROM.h>
#include "states.h"
#include "values.h"
#include "moving.h"

SoftwareSerial out_serial(10, 11);

void setup() {
  Serial.begin(9600);
  last_tick = millis();

  for(int i = 4; i <= 7; i++){
    pinMode(i, OUTPUT);
  }
  Serial.println("Goodnight PC!");

  out_serial.begin(9600);
  out_serial.println("Hello, Phone?");
  
  calibrationState = EEPROM.read(0);
}

int action_counter = 0;

void loop() {
  prevState = state;

  if (out_serial.available()) {
    char c = out_serial.read();
    Serial.write(c);
    if (c == 'C') {
      calibrationState = (calibrationState + 1) % 4;
      EEPROM.put(0, calibrationState);
    }
    if (c == 'T') {
      drivingMode = !drivingMode;
      if (!drivingMode) {
        action_counter = 0;
      }
    }
    if (c == '0') {
      action_counter -= 1;
      if (!drivingMode) {
        set_new_state(State::Stop);
      }
    } else {
      action_counter += 1;
    }
    if (action_counter <= 0) {
      if (drivingMode) {
        set_new_state(State::Stop);
      }
    }
    if (c == 'F') {
      set_new_state(State::Drive);
    }
    if (c == 'R') {
      
      if (!drivingMode) {
        set_new_state(State::RotateToRight);
      } else {
        set_new_state(State::TurnToRight);
      }
    }
    if (c == 'L') {
      if (!drivingMode) {
        set_new_state(State::RotateToLeft);
      } else {
        set_new_state(State::TurnToLeft);
      }
    }
    if (c == 'B') {
      set_new_state(State::Reverse);
    }
  }

  process(); 
}