#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
int main (int argc, string argv[])
{
    if (argc == 2)
    {
        int k = atoi(argv[1]);
        printf ("plaintext:\t");
        string p = get_string();
        if (p != NULL)
        {
            printf ("ciphertext:\t");
            for (int i = 0, len = strlen(p); i < len; i++ )
            {
                if (p[i] >= 'A' && p[i] <= 'Z')
                {
                    int alfabet = 64;
                    p[i] = p[i] - alfabet;
                    p[i] = (p[i] + k) % 26;
                    p[i] = p[i] + alfabet;
                    printf ("%c", p[i]);
                }
                else if (p[i] >= 'a' && p[i] <= 'z')
                {
                    int alfabet = 96;
                    p[i] = p[i] - alfabet;
                    p[i] = (p[i] + k) % 26;
                    p[i] = p[i] + alfabet;
                    printf ("%c", p[i]);
                }
            }
            printf ("\n");
        }
    }
    else
    {
        printf ("Usage: ./caesar k\n");
        return 1;
    }
    return 0;
}