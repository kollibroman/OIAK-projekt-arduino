#include<stdio.h>
#include<stdlib.h>

int *DecodeRbToNb(int *rbArr, int rbSize)
{
    int *nbArr = (int *)malloc(rbSize * sizeof(int));
    int carry = 0;

    // Process from LSD to MSD (right to left)
    for (int i = rbSize - 1; i >= 0; i--)
    {
        // Calculate binary digit and new carry
        int sum = rbArr[i] + carry;
        nbArr[i] = sum & 1; // Equivalent to sum mod 2

        // Calculate new carry
        if (sum == -1)
        {
            // When sum is -1, nbArr digit is 1 and carry is -1
            nbArr[i] = 1;
            carry = -1;
        }

        else if (sum == 2)
        {
            // When sum is 2, nbArr digit is 0 and carry is 1
            nbArr[i] = 0;
            carry = 1;
        }
        
        else
        {
            // Normal cases: sum could be 0, 1
            nbArr[i] = sum;
            carry = 0;

            // Handle negative case
            if (sum < 0)
            {
                nbArr[i] = 0;
                carry = -1;
            }
            else if (sum > 1)
            {
                nbArr[i] = sum % 2;
                carry = sum / 2;
            }
        }
    }

    // If there's a carry left, the output array was too small
    if (carry != 0)
    {
        // This can happen, but we'll just ignore the overflow for simplicity
        // In a real implementation, you might want to handle this differently
    }

    return nbArr;
}