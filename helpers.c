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
    // Sorting algorithm (SELECTION)
    for (int i = 0; i <= n-2; i++)
    {
        int min = values[i];
        int position = i;
        for (int j = i + 1; j <= n-1; j++ )
        {
            if (values[j] < min)
            {
                min = values[j];
                position = j;
            }
        }
        int temp = values[i];
        values[i] = min;
        values[position] = temp;
    }
}