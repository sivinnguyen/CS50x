from cs50 import get_int


def main():
    cctype = "INVALID"

    cc = get_int("Number: ")
    cc = [int(x) for x in str(cc)]  # Convert number to list of int https://www.geeksforgeeks.org/python-convert-number-to-list-of-integers/

    if checksum(cc) == True:
        cctype = checktype(cc)

    print(cctype)


def checksum(cc):  # Valid credit card
    isValid = False
    evens = 0
    odds = 0

    ccrev = cc.copy()
    ccrev.reverse()  # Reverse card number

    for i in range(len(ccrev)):
        if i % 2 != 0:
            n = ccrev[i] * 2
            if n > 9:
                evens += n // 10
                evens += n % 10
            else:
                evens += n
        else:
            odds += ccrev[i]

    checksum = evens + odds

    if checksum % 10 == 0:
        isValid = True

    return isValid


def checktype(cc):  # Check cc type
    firstDigit = cc[0]
    secondDigit = cc[1]
    cclen = len(cc)

    cctype = "INVALID"

    if firstDigit == 3 or firstDigit == 5:
        start = firstDigit * 10 + secondDigit
    else:
        start = firstDigit

    if cclen == 15 and (start == 34 or start == 37):  # check American Express
        cctype = "AMEX"

    if cclen == 16 and (start == 51 or start == 52 or start == 53 or start == 54 or start == 55):  # check MasterCard
        cctype = "MASTERCARD"

    if (cclen == 13 or cclen == 16) and start == 4:  # check Visa
        cctype = "VISA"

    return cctype


main()  # Call main