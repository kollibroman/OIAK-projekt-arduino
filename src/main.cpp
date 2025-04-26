#include <Arduino.h>
#include <FastLED.h>
#include <IRremote.hpp>
#include "InputHandler.h"
#include "LedHandler.h"

#define FAST_LED_PIN 11 
#define REMOTE_PIN 3

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
  Serial.begin(9600);
  pinMode(REMOTE_PIN, INPUT);

  IrReceiver.begin(REMOTE_PIN, ENABLE_LED_FEEDBACK);
  
  FastLED.setBrightness(10);

  delay(300);
  seed2DArray(rbArr, 8, 8);
  FastLED.addLeds<WS2812B, FAST_LED_PIN, GRB>(leds, 64);
  Serial.println("Setup done!");
  Serial.println("Press any button on the remote to see its hex value.");
}

uint8_t hue = 0;
int ledIndex = 0;

void loop() 
{
  if(IrReceiver.decode())
  {
    Serial.print("RawData: 0x");
    Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);

    Serial.print("Command: 0x");
    Serial.println(IrReceiver.decodedIRData.command, HEX);

    unsigned long key = IrReceiver.decodedIRData.command;
    Serial.println(key, HEX);

    switch(key)
    {
      case 0x44:
        Serial.println("Left Arrow");
        ledIndex > 0 ? ledIndex-- : ledIndex = 0;
        
        ResetLEDStateColors(rbArr, leds, 8, 8);
        SetCursor(ledIndex, leds);
        break;
      case 0x43:
        Serial.println("Right Arrow");
        delay(10);
        ledIndex > 14 ? ledIndex = 0 : ledIndex++;

        ResetLEDStateColors(rbArr, leds, 8, 8);
        delay(10);
        SetCursor(ledIndex, leds);
        break;
      case 0x46:
        Serial.println("Up Arrow");

        ChangeValue(ledIndex, rbArr, REMOTE_INPUT::UP_ARROW);
        DecodeAndPrint(rbArr, 8, leds);

        break;
      case 0x15:
        Serial.println("Down Arrow");

        ChangeValue(ledIndex, rbArr, REMOTE_INPUT::DOWN_ARROW);
        DecodeAndPrint(rbArr, 8, leds);

        break;
      case 0x40:
        Serial.println("OK Button");

        ChangeValue(ledIndex, rbArr, REMOTE_INPUT::OK_BUTTON);
        DecodeAndPrint(rbArr, 8, leds);

        break;
      default:
        Serial.println("Unknown Key");
    }

    IrReceiver.resume();


    PrintCurrentLEDStateColors(rbArr, leds, 8, 8);
    SetCursor(ledIndex, leds);
  }
  
}
