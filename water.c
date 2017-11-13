#include <stdio.h>
#include <cs50.h>
int main(void)
{
    int m;
    do
    {
        printf ("How many minutes are you spent in a shower?");
        m = get_int();
    }
    while (m < 0);
    int b = m * 12;
    printf ("Minutes: %i\nBottles: %i\n", m, b);
}