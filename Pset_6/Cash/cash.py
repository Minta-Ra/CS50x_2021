from cs50 import get_float

# Coins
quarter = 25
dime = 10
nickel = 5
penny = 1


# Empty list of coins
coins = 0


while True:

    try:
        # Get input from the user
        userInput = get_float("Change owed in dollars: ")
        if userInput >= 0:
            break

    except ValueError:
        # Ask again for an input - continue returns the control to the beginning of the while loop
        continue


# Round to cents
cents = round(userInput * 100)


# Calculation and deduction
while cents > 0:
    if cents >= quarter:
        cents -= quarter
        coins += 1
    elif cents >= dime:
        cents -= dime
        coins += 1
    elif cents >= nickel:
        cents -= nickel
        coins += 1
    elif cents >= penny:
        cents -= penny
        coins += 1


print(coins)