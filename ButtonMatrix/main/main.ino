// Класс для управления состоянием пинов
class PinManager {
private:
  int pin1;
  int pin2;

public:
  PinManager(int p1, int p2) : pin1(p1), pin2(p2) {
    pinMode(pin1, OUTPUT);
    pinMode(pin2, OUTPUT);
  }

  void setStates(int state1, int state2) {
    digitalWrite(pin1, state1);
    digitalWrite(pin2, state2);
  }
};

// Класс для обновления состояния клавиатуры
class KeyboardUpdater {
private:
  int keyPin1;
  int keyPin2;
  int prevKeyState[4] = {0};
  int keyState[4] = {0};

public:
  KeyboardUpdater(int k1, int k2) : keyPin1(k1), keyPin2(k2) {
    pinMode(keyPin1, INPUT_PULLUP);
    pinMode(keyPin2, INPUT_PULLUP);
  }

  void updateKeyboardState(int index) {
    keyState[index] = !digitalRead(keyPin1);
    keyState[index + 1] = !digitalRead(keyPin2);

    bool isEquals = true;
    for (int i = 0; i < 4; i++) {
      if (prevKeyState[i] != keyState[i]){
        isEquals = false;
      }
    }

    if (isEquals) return;

    for (int i = 0; i < 4; i++){
      prevKeyState[i] = keyState[i];
    }
    Serial.print(keyState[0]);
    Serial.println(keyState[1]);
    Serial.print(keyState[2]);
    Serial.println(keyState[3]);
    Serial.println();
  }
};

PinManager pinManager(8, 9);
KeyboardUpdater keyboardUpdater(10, 11);

void setup() {
  Serial.begin(9600);
}

int statesFirst[][2] = {
  { LOW, HIGH },
  { HIGH, LOW },
};

void loop() {
  for (int i = 0; i < 2; i++) {
    pinManager.setStates(statesFirst[i][0], statesFirst[i][1]);
    keyboardUpdater.updateKeyboardState(i * 2);
    delay(5);
  }
}
