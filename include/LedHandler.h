#include <Arduino.h>
#include <FastLED.h>

void PrintCurrentLEDStateColors(int **arr, CRGB* leds, int rowsCount, int colCount)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            switch (arr[i][j])
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

void ResetLEDStateColors(int **arr, CRGB *leds, int rowsCount, int colCount)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            switch (arr[i][j])
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
}
