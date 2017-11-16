#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
int main (void)
{
    string s = get_string();                //Вводимо імена
    int length = strlen (s);                //Визначаємо кількість символів в стрічці
    printf ("%c", toupper (s[0]));          //Перший символ стрічки виводимо на екран великою буквою
    for (int i = 0; i < length; i++)
    {
        if (s[i] == ' ')                    //При наявності у стрічці пробілу...
        printf ("%c", toupper (s[i+1]));    //... виводимо на екран символ після пробілу з великої літери
    }
    printf ("\n");
    return 0;
}