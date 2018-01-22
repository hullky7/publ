# Prompting the user for a credit card number
while True:
    number = int(input("Number: "))
    if number > 0:
        break

# Визначення кількості цифр в номері карти (q)
n0 = number
q = 0
while True:
    n0 /= 10
    if n0 >= 0:
        q += 1
    if n0 < 1:
        break

# Визначення суми усіх парних цифр в номері, пмножених на 2, починаючи з кінця
n1 = number
a = 0
while True:
    b = 0
    n1 /= 10
    b = int(n1 % 10)
    b *= 2
    if b >= 10:
        b = 1 + (b % 10)
    a += b
    n1 /= 10
    if n1 <= 10:
        break

# Визначення суми усіх непарних цифр у номері картки, починаючи з кінця
n2 = number
c = 0
while True:
    b = 0
    b = int(n2 % 10)
    c += b
    n2 /= 100
    if n2 < 1:
        break

# Контрольна сума цифр в номері
sum = a + c

# Pнаходження перших двох цифр в номері картки для визначення платіжної системи
while True:
    number //= 10
    if number <= 100:
        break

# перевірка на приналежність картки до AMEX, MASTERCARD або VISA
if int(sum % 10 == 0):
    if (q == 15) and (number == 34 or number == 37):
        print("AMEX")
    elif (q == 16) and (number >= 51 and number <= 55):
        print("MASTERCARD")
    elif (q == 13 or q == 16) and (number >= 40 and number <= 49):
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")