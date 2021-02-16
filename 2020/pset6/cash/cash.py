from cs50 import get_float

cents = 0
amounts = 0


def main():
    global cents

    while True:  # Prompt user for change input
        dollars = get_float("Change owed: ")
        if dollars > 0:
            break

    cents = round(dollars * 100)  # Safely convert dollars to cents

    change(25)  # quarters
    change(10)  # dimes
    change(5)  # nickels
    change(1)  # pennies

    print(amounts)


def change(coin):  # get amount of quarters (25¢), dimes (10¢), nickels (5¢), and pennies (1¢).
    global cents, amounts

    n = cents // coin
    if n > 0:
        amounts += n
        cents %= coin


main()  # Call main