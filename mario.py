from cs50 import get_int
# prompt for input a numeric height in range [0, 23]
while True:
    h = get_int("Height: ")
    if h >= 0 and h <= 23:
        break
# building a pyramid line by line
for i in range(1, h + 1):
    print((h - i) * " " + (i) * "#" + "  " + (i) * "#")