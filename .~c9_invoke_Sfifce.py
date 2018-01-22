# Prompting the user for a credit card number

def Number():
    while True:
        number = int(input("Number: "))
        if number > 0:
            break
    return number

# Definition of LENGTH of the number (q)


def Length(n):
    q = 0
    while True:
        n /= 10
        if n >= 0:
            q += 1
        if n < 1:
            break
    return q

# Definition the sum of the second-to-last digit multiplied by 2


def Multiply(n):
    a = 0
    while True:
        b = 0
        n /= 10
        b = int(n % 10)
        b *= 2
        if b >= 10:
            b = 1 + (b % 10)
        a += b
        n /= 10
        if n <= 10:
            break
    return a

# Definition  the sum of the digits that weren’t multiplied by 2


def Non_multiply(n):
    c = 0
    while True:
        b = 0
        b = int(n % 10)
        c += b
        n /= 100
        if n < 1:
# перевірка на приналежність картки до AMEX, MASTERCARD або VISA
    return c

# Finding the starting two numbers


def Number_of_2(number):
    while True:
        number //= 10
        if number <= 100:
            break
    return number

# Checking and detecting typos of credit card (AMEX, MASTERCARD, VISA or invalid)


def Check(sum, q, number):
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


def main():
    number = Number()       # Card number
    q = Length(number)   # Lenght of card number
    sum = (Multiply(number)) + (Non_multiply(number))   # Control sum of digits
    number = Number_of_2(number)                        # Starting two-digits number
    Check(sum, q, number)  # CHECKING... and RESULTS


if __name__ == "__main__":
    main()