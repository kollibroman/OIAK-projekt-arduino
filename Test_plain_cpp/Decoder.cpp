#include <stdio.h>
#include <stdlib.h>
#include "../include/decoder.h"

bool checkForFrance(int *arr, int arr_length)
{
    // Fr = 01000110 01110010

    int fr[16] = {0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0};

    for (int i = 0; i < arr_length; i++)
    {
        if (arr[i] != fr[i])
        {
            return false;
        }
    }

    return true;
}

void PrintArray(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
}
int main()
{
    //create 2d array with redundant numbers (one from article for test case)
    int rbSize = 16;
    int **rbArr = (int **)malloc(rbSize * sizeof(int *));
    for (int i = 0; i < rbSize; i++)
    {
        rbArr[i] = (int *)malloc(rbSize * sizeof(int));
    }

    // 100100-100-101
    rbArr[0][0] = 0;
    rbArr[0][1] = 1;
    rbArr[0][2] = 0;
    rbArr[0][3] = 0;
    rbArr[0][4] = 0;
    rbArr[0][5] = 1;
    rbArr[0][6] = 1;
    rbArr[0][7] = 0;
    rbArr[0][8] = 0;
    rbArr[0][9] = 1;
    rbArr[0][10] = 1;
    rbArr[0][11] = 1;
    rbArr[0][12] = 0;
    rbArr[0][13] = 0;
    rbArr[0][14] = 1;
    rbArr[0][15] = 0;

    //-100-100100101
    rbArr[1][0] = -1;
    rbArr[1][1] = 0;
    rbArr[1][2] = 0;
    rbArr[1][3] = -1;
    rbArr[1][4] = 0;
    rbArr[1][5] = 0;
    rbArr[1][6] = 1;
    rbArr[1][7] = 0;
    rbArr[1][8] = 0;
    rbArr[1][9] = 1;
    rbArr[1][10] = 0;
    rbArr[1][11] = 1;

    //-100100-100-10-1
    rbArr[2][0] = -1;
    rbArr[2][1] = 0;
    rbArr[2][2] = 0;
    rbArr[2][3] = 1;
    rbArr[2][4] = 0;
    rbArr[2][5] = 0;
    rbArr[2][6] = -1;
    rbArr[2][7] = 0;
    rbArr[2][8] = 0;
    rbArr[2][9] = -1;
    rbArr[2][10] = 0;
    rbArr[2][11] = -1;

    // Print the rbArr
    printf("Redundant Binary Arrays:\n");

    for (int i = 0; i < 3; i++)
    {
        PrintArray(rbArr[i], rbSize);
        printf("\n");
    }

    // Print the nbArr
    printf("Decoded Non-Redundant Binary Arrays:\n");
    for (int i = 0; i < 3; i++)
    {
        RBDigit* rbDigit = (RBDigit*)malloc(rbSize * sizeof(RBDigit));

        for (int j = 0; j < rbSize; j++)
        {
            rbDigit[j] = value_to_rb_digit(rbArr[i][j]);
        }

        int *nbArr = rb_to_binary_serial(rbDigit, rbSize, &rbSize);

        checkForFrance(nbArr, rbSize) ? printf("France Detected\n") : printf("France Not Detected\n");

        PrintArray(nbArr, rbSize);
        printf("\n");
        free(rbDigit); 
    }

        return 0;
}