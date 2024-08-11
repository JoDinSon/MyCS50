from cs50 import get_int


def main():

    # Ask for Credit Card Number
    credit = get_int("Number: ")

    # Turn Number into a list of digits (reversed)
    digits = digitize(credit)

    if check_sum(digits):

        print(ident_card(digits))

    else:
        print("INVALID")


def digitize(n):
    '''Put digits of Card Number "n" into list in reversed order (the C way)'''
    digits = []
    i = 0
    while n > 0:
        digits.append(n % 10)
        n = (n - digits[i]) / 10
        i += 1

    return digits


def check_sum(digits):
    '''Calculate check sum and return True if Number is valid'''

    # Iterate through digits and calculate check sum
    fst_sum = 0
    sec_sum = 0
    for i in range(len(digits)):
        # odd digit positions
        if i % 2 == 1:
            digit = digits[i] * 2
            if digit >= 10:
                sec_sum += digit % 10 + 1
            else:
                sec_sum += digit

        # even digit positions
        else:
            fst_sum += digits[i]

    # calculate final check sum
    check_sum = fst_sum + sec_sum

    # return true if card is Valid according to Nuhn's algorithm
    return check_sum % 10 == 0


def ident_card(digits):
    '''Identify and return credit institute'''
    print(len(digits))
    l = len(digits)
    # AMEX Case
    if l == 15 and digits[l - 1] == 3:
        if digits[l - 2] in [4, 7]:
            return "AMEX"
        else:
            return "INVALID"

    #  Master case
    elif l == 16 and digits[l - 1] == 5:
        if digits[l - 2] in range(1, 6):
            return "MASTERCARD"
        else:
            return "INVALID"

    # VISA case
    elif l in [13, 16] and digits[l - 1] == 4:
        return "VISA"
    else:
        return "INVALID"


main()