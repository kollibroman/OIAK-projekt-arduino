#ifndef DECODER_H
#define DECODER_H

#include <stdio.h>
#include <stdlib.h>

// Struktura reprezentująca cyfrę RB
typedef struct 
{
    int S; // Sign bit
    int D; // Data bit
} RBDigit;

// Funkcja do konwersji pojedynczej cyfry RB na wartość {-1, 0, 1}
int rb_digit_to_value(RBDigit digit)
{
    if (digit.S == 0 && digit.D == 0)
        return 0; // (0,0) -> 0
    if (digit.S == 0 && digit.D == 1)
        return 1; // (0,1) -> 1
    if (digit.S == 1 && digit.D == 1)
        return -1; // (1,1) -> -1
    return 0;      // invalid case
}

// Funkcja do utworzenia cyfry RB z wartości {-1, 0, 1}
RBDigit value_to_rb_digit(int value)
{
    RBDigit digit;
    switch (value)
    {
    case 0:
        digit.S = 0;
        digit.D = 0;
        break; // 0 -> (0,0)
    case 1:
        digit.S = 0;
        digit.D = 1;
        break; // 1 -> (0,1)
    case -1:
        digit.S = 1;
        digit.D = 1;
        break; // -1 -> (1,1)
    default:
        digit.S = 0;
        digit.D = 0;
        break;
    }
    return digit;
}

// Implementacja algorytmu szeregowego z artykułu
int *rb_to_binary_serial(RBDigit *rb_number, int n, int *result_size)
{
    // Wynik będzie miał n+1 bitów (zgodnie z artykułem)
    *result_size = n + 1;
    int *binary_result = (int *)calloc(*result_size, sizeof(int));

    int C = 0; // Zmienna convert, inicjalnie C0 = 0

    // Przetwarzamy od najmłodszej cyfry (indeks 0) do najstarszej
    for (int i = 0; i < n; i++)
    {
        int S_i = rb_number[i].S;
        int D_i = rb_number[i].D;

        // Implementacja reguł konwersji z Tabeli I w artykule
        int B_i, C_next;

        if (S_i == 0 && D_i == 0)
        { // X_i = 0
            if (C == 0)
            {
                B_i = 0;
                C_next = 0;
            }
            else
            {
                B_i = 1;
                C_next = 1;
            }
        }
        else if (S_i == 0 && D_i == 1)
        { // X_i = 1
            if (C == 0)
            {
                B_i = 1;
                C_next = 0;
            }
            else
            {
                B_i = 0;
                C_next = 0;
            }
        }
        else if (S_i == 1 && D_i == 1)
        { // X_i = -1
            if (C == 0)
            {
                B_i = 1;
                C_next = 1;
            }
            else
            {
                B_i = 0;
                C_next = 1;
            }
        }
        else
        {
            // Nieprawidłowa kombinacja
            B_i = 0;
            C_next = C;
        }

        binary_result[i] = B_i;
        C = C_next;
    }

    // Najstarszy bit wyniku to ostatnia wartość C
    binary_result[n] = C;

    return binary_result;
}

#endif