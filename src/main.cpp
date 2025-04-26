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
int **rbArr = create2DArray(8, 8);

void setup() 
{
  // Setup here
  Serial.begin(115200);
  // Serial.println("Hello World!");
  // create 8x8 array

  FastLED.setBrightness(255);

  delay(3000);
  seed2DArray(rbArr, 8, 8);
  FastLED.addLeds<WS2812B, FAST_LED_PIN, GRB>(leds, 64);
}

uint8_t hue = 0;

void loop() 
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      switch(rbArr[i][j])
      {
        case 1:
          leds[j + (i * 8)] = CRGB::Blue;
          break;
        case 0:
          leds[j + (i * 8)] = CRGB::Red;
          break;
        case -1:
          leds[j + (i * 8)] = CRGB::Yellow;
          break;
        default:
          break;
      }
    }
  }

  FastLED.show();
}
