#include <Arduino.h>

class MotorController {
 private:
  int pin1;
  int pin2;

 public:
  MotorController(int pin1, int pin2) : pin1(pin1), pin2(pin2) {
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
    stop();
  }

  void control(const char* direction, int speed) {
    if (strcmp(direction, "r") == 0) {
      analogWrite(pin1, speed);
      analogWrite(pin2, 0);
    } else if (strcmp(direction, "l") == 0) {
      analogWrite(pin1, 0);
      analogWrite(pin2, speed);
    } else if (strcmp(direction, "s") == 0) {
      stop();
    } else {
      Serial.println("Invalid direction");
      return;
    }
  }

  void stop() {
    analogWrite(pin1, 0);
    analogWrite(pin2, 0);
  }
};

MotorController motorController(11, 10);

void setup() {
  Serial.begin(9600);
  Serial.println(
      "l <speed> - change the direction of movement to the left (speed 0-255)");
  Serial.println(
      "r <speed> - change the direction of movement to the right (speed "
      "0-255)");
  Serial.println("s - to stop");
}

void loop() {
  if (Serial.available() > 0) {
    char input[20];
    int index = 0;
    while (Serial.available() > 0) {
      char character = Serial.read();
      if (character == '\n') {
        break;
      }
      input[index++] = character;
      delay(2);
    }
    input[index] = '\0';

    char* direction = strtok(input, " ");
    char* speedStr = strtok(NULL, " ");

    if (strcmp(direction, "s") == 0) {
      motorController.control(direction, 0);
      delay(2000);
    } else {
      if (speedStr == NULL) {
        Serial.println("Speed not provided");
        return;
      }

      int speed = atoi(speedStr);
      if (speed < 0 || speed > 255) {
        Serial.println("Speed out of range (0-255)");
        return;
      }

      motorController.control(direction, speed);
      delay(2000);
    }
  }
}
