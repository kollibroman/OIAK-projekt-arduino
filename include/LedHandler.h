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

void PrintFranceFlag(CRGB *leds)
{
    // France flag colors
    CRGB blue = CRGB::Blue;
    CRGB white = CRGB::White;
    CRGB red = CRGB::Red;

    // Set the first 3 columns to blue, white, and red respectively
    for (int i = 2; i <= 5; i++)
    {
        for (int j = 2; j <= 6; j++)
        {
            if(j < 4)
            {
                leds[j + (i * 8)] = blue; // Set blue for first column
            }
            else if(j >=4 && j < 6)
            {
                leds[j + (i * 8)] = white; // Set white for second column
            }
            else
            {
                leds[j + (i * 8)] = red; // Set red for third column
            }
        }
    }

    FastLED.show();
}

bool checkForFrance(int *arr, int arr_length)
{
    // Fr = 01000110 01110010

    int fr[16] = {0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0};

    for (int i = 0; i < arr_length; i++)
    {
        if (arr[i] != fr[i])
        {
            return false;
        }
    }

    return true;
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

    if(checkForFrance(nbArr, 16))
    {
        PrintFranceFlag(leds);
    }
    else
    {
        PrintCurrentLEDStateColors(arr, leds, 8, 8);
    }

    //Wycieką pamienci muwimy nie!!!
    free(rbArr);
    free(nbArr);
}