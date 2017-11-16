#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
int main (void)
{
    string s = get_string();        //Вводимо імена
    int length = strlen (s);        //Визначаємо кількість символів в стрічці

    for (int i = 0; i < length; i++)
    {
    if (s[i] != ' ')
    printf ("%c", toupper (s[i]));  // Перший символ стрічки виводимо на екран великою буквою
    break;
    }

    // При наявності у стрічці пробілу та за умови, що після пробілу йде не пробіл та не кінець строки -
    // виводимо на екран символ після пробілу з великої літери
    for (int i = 0; i < length; i++)
    {
        if ((s[i] == ' ') && (s[i+1] != ' ') && (s[i+1] != '\0'))
        printf ("%c", toupper (s[i+1]));
    }
    printf ("\n");
    return 0;
}