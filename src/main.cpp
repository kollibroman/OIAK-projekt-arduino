#include <Arduino.h>

void setup() {
  // Setup here
  Serial.begin(115200);
  // Serial.println("Hello World!");
}

void loop() {
  int data[8][8] = {
      {0, 1, 1, -1, -1, 1, 1, 0},
      {0, 1, 1, -1, -1, 1, 1, 0},
      {0, 1, 1, -1, -1, 1, 1, 0},
      {0, 1, 1, -1, -1, 1, 1, 0},
      {0, 1, 1, -1, -1, 1, 1, 0},
      {0, 1, 1, -1, -1, 1, 1, 0},
      {0, 1, 1, -1, -1, 1, 1, 0},
      {0, 1, 1, -1, -1, 1, 1, 0}
    };

  int rbSize = 8;

  free(data);
}
