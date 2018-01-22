import sys
# if number of arguments is 2 do...
if len(sys.argv) == 2:
    k = int(sys.argv[1])
    p = input("plaintext: ")
    # transforming string to list
    p1 = list(p)
    if (p is not None):
        print("ciphertext: ", end="")
        for i in range(len(p1)):
            # encrypting UP characters
            if p1[i].isupper():
                p1[i] = chr(((ord(p[i]) - 64 + k) % 26) + 64)
            # encrypting LOW characters
            elif p1[i].islower():
                p1[i] = chr(((ord(p[i]) - 96 + k) % 26) + 96)
        # join all characters and display a word
        print("".join(p1))
    exit(0)
# exit with 1 if number of arguments is not 2
else:
    print("Usage: ceasar.py k")
    exit(1)