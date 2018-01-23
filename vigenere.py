import sys

# if number of arguments is no 2 do...
if len(sys.argv) != 2:
    print("Usage: python vigenere.py k")
    exit(1)

k1 = sys.argv[1]     # присвоюємо змінній k(keyword) значення ключа.
len_k = len(k1)      # визначаємо довжину ключа (кількість символів у keyword)

# cheking for alphabetical keyword
for c in range(len_k):
    if str.isalpha(k1[c]) != True:
        print("Keyword must be only alphabetical")
        exit(1)

p = input("plaintext: ")
len_p = len(p)

if p != "":     # якщо початковий текст не пустий...
    p = list(p)
    k = list(k1)
    print("ciphertext: ", end="")
    for i, j in zip(range(len_p), range(len_p)):  # for i, j in enumerate(range(len_p))
        n = int(j % len_k)
        # перетворення кодів літер з таблиці ASCII у алфавітну систему від 0 до 26
        if k[n].isupper():
            k[n] = chr(ord(k[n]) - 65)
        elif k[n].islower():
            k[n] = chr(ord(k[n]) - 97)
        # 3 варіанти виведення зашифрованих символів: 1)великі літери 2)малі літери 3)усі інші знаки
        if str.isupper(p[i]):
            p[i] = chr(((ord(p[i]) - 65 + ord(k[n])) % 26) + 65)
        elif str.islower(p[i]):
            p[i] = chr(((ord(p[i]) - 97 + ord(k[n])) % 26) + 97)
        else:
            j = j - 1
    print("".join(p))
exit(0)