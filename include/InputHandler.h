#include <stdio.h>
#include <stdlib.h>
#include <FastLED.h>
#include <IRremote.hpp>
#include <Arduino.h>

enum REMOTE_INPUT
{
    LEFT_ARROW,
    RIGHT_ARROW,
    UP_ARROW,
    DOWN_ARROW,
    OK_BUTTON
};

int* ConvertTo1DArray(int **arr, int rowsCount, int colCount)
{
    int *singleDArr = (int *)malloc(rowsCount * colCount * sizeof(int));

    int singleDArrIndex = 0;

    for (int i = 0; i < rowsCount; i++)
    {
        if(i % 2 == 0)
        {
            for (int j = 0; j < colCount; j++)
            {
                singleDArr[singleDArrIndex] = arr[i][j];
                singleDArrIndex++;
            }
        }

        else
        {
            for (int j = (colCount - 1); j >= 0; j--)
            {
                singleDArr[singleDArrIndex] = arr[i][j];
                singleDArrIndex++;
            }
        }
    }
    return singleDArr;
}

int** create2DArray(int rowsCount, int colCount)
{
    int **arr = (int **)malloc(rowsCount * sizeof(int *));

    for (int i = 0; i < rowsCount; i++)
    {
        arr[i] = (int *)malloc(colCount * sizeof(int));
    }

    return arr;
}

void seed2DArray(int **arr, int rowsCount, int colCount)
{
    for (int i = 0; i < rowsCount; i++)
    {
        if(i < 2)
        {
            for (int j = 0; j < colCount; j++)
            {
                arr[i][j] = 0;
            }
        }

        else if(i > 1 && i < 6)
        {
            for (int j = 0; j < colCount; j++)
            {
                arr[i][j] = 2;
            }
        }

        else
        {
            for (int j = 0; j < colCount; j++)
            {
                arr[i][j] = 0;
            }
        }
    }
}

void free2DArray(int **arr, int rowsCount)
{
    for (int i = 0; i < rowsCount; i++)
    {
        free(arr[i]);
    }
    free(arr);
}

void SetCursor(int ledIndex, CRGB* leds)
{
    leds[ledIndex] = CRGB::White;
    FastLED.show();
}

void ChangeValue(int ledIndex, int **rbArr, REMOTE_INPUT remote)
{
    int* arr = ConvertTo1DArray(rbArr, 2, 8);

    switch (remote)
    {
        case REMOTE_INPUT::OK_BUTTON:
            arr[ledIndex] = 0;
            break;

        case REMOTE_INPUT::DOWN_ARROW:
            arr[ledIndex] = -1;
            break;

        case REMOTE_INPUT::UP_ARROW:
            arr[ledIndex] = 1;
            break;

        default:
            break;
    }

    int rbXIndex = ledIndex > 7 ? ledIndex - 8 : ledIndex;
    int rbYIndex = ledIndex > 7 ? 1 : 0;

    rbArr[rbYIndex][rbXIndex] = arr[ledIndex];
    free(arr);
}