import sys

if len(sys.argv) == 2:
    k = int(sys.argv[1])
    p = input("plaintext: ")
    p1 = list(p)  # transforming string to list
    if (p is not None):
        print("ciphertext: ", end="")
        for i in range(len(p1)):
            if p1[i].isupper():  # encrypting UP characters
                p1[i] = chr(((ord(p[i]) - 64 + k) % 26) + 64)
            elif p1[i].islower():  # encrypting LOW characters
                p1[i] = chr(((ord(p[i]) - 96 + k) % 26) + 96)
        print("".join(p1))  # join all characters and display a word
    exit(0)

else:
    print("Usage: ceasar.py k")
    exit(1)  # exit with 1 if number of arguments is not 2