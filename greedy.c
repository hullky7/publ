#include <stdio.h>
#include <cs50.h>
#include <math.h>
int main(void)
{
    float d;
    float coins;
    int counter = 0;
    do
    {
        printf ("O hai! How much change is owed?\n");
        d = get_float();
    }
    while (d < 0);
    d = d * 100;
    coins = round(d);
    while (coins - 25 >= 0)
    {
        counter = counter + 1;
        coins = coins - 25;
    }
    while (coins - 10 >= 0)
    {
        counter = counter + 1;
        coins = coins - 10;
    }
    while (coins - 5 >= 0)
    {
        counter = counter + 1;
        coins = coins - 5;
    }
    while (coins - 1 >= 0)
    {
        counter = counter + 1;
        coins = coins - 1;
    }
    printf("%i\n", counter);
}