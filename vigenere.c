#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
int main (int argc, string argv[])
{
    if (argc != 2)
    {
        printf ("Usage: ./caesar k\n");
        return 1;
    }
    string k = argv[1];     //присвоюємо змінній k(keyword) значення ключа.
    int len_k = strlen(k);  //визначаємо довжину ключа (кількість символів у keyword)
    for (int c = 0; c < len_k; c++)
    {
        if (!isalpha (k[c]))
        {
            printf ("Keyword must be only alphabetical\n");
            return 1;
        }
    }
    printf ("plaintext:\t");
    string p = get_string(); //визначаємо довжину початкового тексту (кількість символів)
    if (p != NULL)          //якщо початковий текст не пустий...
    {
        printf ("ciphertext:\t");
        for (int i = 0, j = 0, len_p = strlen(p); i < len_p && j < len_p; i++, j++ )
        {
            int n = (j % len_k);  //умова, якщо слово k < за слово p, то літери в k використ.знову по колу, скільки потрібно для шифр.
            if (isupper (k[n]))   //перетворення кодів великих літер з таблиці ASCII у алфавітну систему від 0 до 26.
            {
                k[n] = k[n] - 65;
            }
            else if (islower (k[n])) //перетворення кодів малих літер з таблиці ASCII у алфавітну систему від 0 до 26.
            {
                k[n] = k[n] - 97;
            }
            // Три умови на виведення зашифрованих символів: 1)великі літери 2)малі літери 3)усі інші знаки, крім літер
            if (isupper (p[i]))
            {
                p[i] = ((p[i] - 65 + k[n]) % 26) + 65;
                printf ("%c", p[i]);
            }
            else if (islower (p[i]))
            {
                p[i] = ((p[i] - 97 + k[n]) % 26) + 97;
                printf ("%c", p[i]);
            }
            else
            {
                printf ("%c", p[i]);
                j = j - 1;      //якщо символ у "p" не літера, то літеру з ключа "k" не застосовуємо.
            }
        }
        printf ("\n");
    }
    return 0;
}