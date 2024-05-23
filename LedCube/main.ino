int delay_duration = 500;
const int layers_idxs[] = {A0, A1};

const int columns_idxs[] = {2, 3, 4, 5};

int layers_count = sizeof(layers_idxs) / sizeof(layers_idxs[0]);
int columns_count = sizeof(columns_idxs) / sizeof(columns_idxs[0]);

void setup() {
  for (int i = 0; i < layers_count; i++) {
    pinMode(layers_idxs[i], OUTPUT);
  }
  for (int i = 0; i < columns_count; i++) {
    pinMode(columns_idxs[i], OUTPUT);
  }
}

void show_cube(int layers_count, int columns_count, int delay_duration) {
  for (int l = 0; l < layers_count; l++) {
    for (int c2 = 0; c2 < columns_count; c2++) {
      for (int i = 0; i < layers_count; i++) {
        digitalWrite(layers_idxs[i], l == i ? HIGH : LOW);
      }
      for (int j = 0; j < columns_count; j++) {
        digitalWrite(columns_idxs[j], c2 == j ? HIGH : LOW);
      }
      delay(delay_duration);
      for (int j = 0; j < columns_count; j++) {
        digitalWrite(columns_idxs[j], LOW);
      }
    }
  }
}

void loop() {
  show_cube(layers_count, columns_count, delay_duration);
}
