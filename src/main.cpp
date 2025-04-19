#include <Arduino.h>
/*
Hex values for remote buttons
Left arrow:BB44FF00
Right arrow:BC43FF00
Up arrow:B946FF00
Down arrow:EA15FF00
OK button:BF40FF00
Library link: https://github.com/Arduino-IRremote/Arduino-IRremote
*/
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
