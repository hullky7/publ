#include <stdio.h>
#include <cs50.h>
int main(void)
{
    int h;
    do
    {
        printf ("Height: ");
        h = get_int();
    }
    while (h < 0 || h > 23);
    for (int i = 1; i <= h; i++)
    {
        for (int s = h - 1 - i ; s >= 0; s = s - 1 )
        {
            printf(" ");
        }
        for (int p = 0; p <= i; p++)
        {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}