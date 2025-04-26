#include <Arduino.h>
#include <FastLED.h>
#include <decoder.h>

void PrintCurrentLEDStateColors(int **arr, CRGB* leds, int rowsCount, int colCount)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            switch (arr[i][j])
            {
                case 1:
                    leds[j + (i * 8)] = CRGB::Red;
                    break;
                case 0:
                    leds[j + (i * 8)] = CRGB::Green;
                    break;
                case -1:
                    leds[j + (i * 8)] = CRGB::Blue;
                    break;
                case 2:
                    leds[j + (i * 8)] = CRGB::Purple;
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
                leds[j + (i * 8)] = CRGB::Red;
                break;
            case 0:
                leds[j + (i * 8)] = CRGB::Black;
                break;
            case -1:
                leds[j + (i * 8)] = CRGB::Blue;
                break;
            case 2:
                leds[j + (i * 8)] = CRGB::Purple;
                break;
            default:
                break;
            }
        }
    }
}

void DecodeAndPrint(int **arr, int rbSize, CRGB *leds)
{
    int* rbArr = ConvertTo1DArray(arr, 2, 8);

    int* nbArr = DecodeRbToNb(rbArr, 16);

    for (int i = 6; i < 8; i++)
    {
        if(i == 6)
        {
            for (int j = 0; j < 8; j++)
            {
                arr[i][j] = nbArr[j];
            }
        }

        else
        {
            for (int j = 7; j >= 0; j--)
            {
                arr[i][j] = nbArr[15-j];
            }
        }
    }

    PrintCurrentLEDStateColors(arr, leds, 8, 8);

    //Wycieką pamienci muwimy nie!!!
    free(rbArr);
    free(nbArr);
}
