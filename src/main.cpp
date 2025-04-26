#include <Arduino.h>
#include <FastLED.h>
#include "InputHandler.h"

#define FAST_LED_PIN 11 

FASTLED_USING_NAMESPACE
/*
Hex values for remote buttons
Left arrow:BB44FF00
Right arrow:BC43FF00
Up arrow:B946FF00
Down arrow:EA15FF00
OK button:BF40FF00
Library link: https://github.com/Arduino-IRremote/Arduino-IRremote
*/

CRGB leds[64];

void setup() 
{
  // Setup here
  Serial.begin(115200);
  // Serial.println("Hello World!");
  // create 8x8 array

  // int** rbArr = create2DArray(8, 8);

  FastLED.setBrightness(255);

  delay(3000);
  FastLED.addLeds<WS2812B, FAST_LED_PIN, GRB>(leds, 64);
}

uint8_t hue = 0;

void loop() 
{
  fill_rainbow(leds, 64, hue, 7);
  FastLED.show();
}
