from cs50 import get_float, get_int
# prompt for asking the user how much change is owed
while True:
    d = get_float("O hai! How much change is owed?\n")
    if d >= 0:
        break
# define a variables
coins = d * 100
counter = int(0)
# calculating a number of coins of 25,10,5 and 1
counter += coins // 25
coins = coins % 25

counter += coins // 10
coins = coins % 10

counter += coins // 5
coins = coins % 5

counter += coins // 1
coins = coins % 1
#
print("{}" .format(int(counter)))