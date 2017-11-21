#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <cs50.h>
#include <crypt.h>
#include <string.h>

int main (int argc, char *argv[])
{
	if (argc != 2)                      //checking for existence of 2 arguments
	{
		printf("Usage: ./crack hash\n");
		return 1;
	}
	char *crypt_1 = argv[1] ;
	char str[5];
    int rez = 1;
    //Cracking passwords from 1 to 4 characters of it
    for(int i = 2; rez != 0; i++)         //promt for array size
    {
        for(int m = 65; m < 122; m++)
        {
            str[i-1] = '\0';
            str[i-2] = m;               //for password consisting of 1 characters
            if (strcmp(crypt(str, "50"), crypt_1) == 0)
            {
                rez = 0;
                printf("%s\n", str); //PASSWORD
                break;
            }
            else if (i > 2)             //for password consisting of 2 characters
            {
                for(int l = 65; l < 122; l++)
                {
                    str[i-3] = l;
                    if (strcmp(crypt(str, "50"), crypt_1) == 0)
                    {
                        rez = 0;
                        printf("%s\n", str); //PASSWORD
                        break;
                    }
                    else if (i > 3)         //for password consisting of 3 characters
                    {
                        for(int k = 65; k < 122; k++)
                        {
                            str[i-4] = k;
                            if (strcmp(crypt(str, "50"), crypt_1) == 0)
                            {
                                rez = 0;
                                printf("%s\n", str); //PASSWORD
                                break;
                            }
                            else if (i > 4)         //for password consisting of 4 characters
                            {
                                for(int j = 65; j < 122; j++)
                                {
                                    str[i-5] = j;
                                    if (strcmp(crypt(str, "50"), crypt_1) == 0)
                                    {
                                        rez = 0;
                                        printf("%s\n", str); //PASSWORD
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
return 0;
}