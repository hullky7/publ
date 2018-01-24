import sys
import os
import itertools as it
import crypt

if len(sys.argv) is not 2:    # checking for existence of 2 arguments
    print("Usage: python crack.py hash")
    exit(1)

crypt_1 = sys.argv[1]
str1 = []
rez = 1
# Cracking passwords from 1 to 4 characters of it
for i in range(1, 5):  # promt for array size
    str1.append("")
    for m in it.chain(range(65, 91), range(97, 123)):
        str1[0] = (chr(m))    # for password consisting of 1 characters
        str2 = ''.join(map(str, str1))
        if (crypt.crypt(str2, '50') == crypt_1):
            rez = 0
            print("{}" .format(str2))  # PASSWORD
            exit(0)
        elif (i > 1):  # for password consisting of 2 characters
            for l in it.chain(range(65, 91), range(97, 123)):
                str1[1] = (chr(l))
                str2 = ''.join(map(str, str1))
                if (crypt.crypt(str2, '50') == crypt_1):
                    rez = 0
                    print("" .join(str2))  # PASSWORD
                    exit(0)
                elif (i > 2):         # for password consisting of 3 characters
                    for k in it.chain(range(65, 91), range(97, 123)):
                        str1[2] = (chr(k))
                        str2 = ''.join(map(str, str1))
                        if (crypt.crypt(str2, '50') == crypt_1):
                            rez = 0
                            print("" .join(str2))  # PASSWORD
                            exit(0)
                        elif (i > 3):  # for password consisting of 4 characters
                            for j in it.chain(range(65, 91), range(97, 123)):
                                str1[3] = (chr(j))
                                str2 = ''.join(map(str, str1))
                                if (crypt.crypt(str2, '50') == crypt_1):
                                    rez = 0
                                    print("" .join(str2))  # PASSWORD
                                    exit(0)
exit(0)