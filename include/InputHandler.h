#include <stdio.h>
#include <stdlib.h>
#include <FastLED.h>
#include <IRremote.hpp>
#include <Arduino.h>

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
        for (int j = 0; j < colCount; j++)
        {
            arr[i][j] = random(-1, 2);
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
