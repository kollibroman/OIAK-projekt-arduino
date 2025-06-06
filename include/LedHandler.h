#include <Arduino.h>
#include <FastLED.h>
#include <decoder.h>

void PrintFranceFlag(CRGB *leds, int **arr)
{
    // Set the first 3 columns to blue, white, and red respectively
    for (int i = 0; i <= 8; i++)
    {
        for (int j = 1; j <= 6; j++)
        {
            if(arr[i][j] == 2)
            {
                if (j < 3)
                {
                    leds[j + (i * 8)] = CRGB::Blue; // Set blue for first column
                }
                else if (j >= 3 && j < 5)
                {
                    leds[j + (i * 8)] = CRGB::White; // Set white for second column
                }
                else
                {
                    leds[j + (i * 8)] = CRGB::Red; // Set red for third column
                }
            }
        }
    }
}

void PrintCurrentLEDStateColors(int **arr, CRGB* leds, int rowsCount, int colCount, bool showFrance = false)
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

    if(showFrance)
    {
        PrintFranceFlag(leds, arr);
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

bool checkForFrance(int *arr, int arr_length)
{
    // Fr = 01000110 01110010

    int fr[16] = {0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0};
    int index = 0;

    for (int i = 0; i < arr_length; i++)
    {
        index++;
        if (arr[i] != fr[i])
        {
            return false;
        }
    }

    if(index == 15)
    {
        return true;
    }

    return false;
}

void DecodeAndPrint(int **arr, int rbSize, CRGB *leds)
{
    RBDigit *rbArr = ConvertTo1DRBArray(arr, 2, 8);

    int* nbArr = rb_to_binary_serial(rbArr, 16, &rbSize);

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
            for (int j = 0; j < 8; j++)
            {
                arr[i][j] = nbArr[j+8];
            }
        }
    }
    
    PrintCurrentLEDStateColors(arr, leds, 8, 8, checkForFrance(nbArr, 16));

    //Wycieką pamienci muwimy nie!!!
    free(rbArr);
    free(nbArr);
}