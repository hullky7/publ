

/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // Searching algorithm (BINARY)
    if (n < 0)
    {
        return false;
    }
    int L = 0 ;
    int R = n - 1;
    while (L <= R)
    {
        int Mid = (L + R) / 2;
        if (values[Mid] == value)
        {
            return true;
        }
        else if (value < values[Mid])
        {
            R = Mid - 1;
        }
        else if (value > values[Mid])
        {
            L = Mid + 1;
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */

void sort(int values[], int n)
{
    // Sorting algorithm (COUNTING)
    int max = 65536;
    int arr[max];
    for (int i = 0; i < max; i++)
    {
        arr[i] = 0;
    }

    for (int i = 0; i < n; i++)
    {
        arr[values[i]] = arr[values[i]] + 1;
    }
    int rah= 0;
    for (int j = 0; j < max; j++)
            for (int i = 0; i < arr[j]; i++)
            {
                values[rah] = j;
                rah = rah + 1;
            }
}