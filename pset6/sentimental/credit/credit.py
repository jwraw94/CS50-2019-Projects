import cs50


def main():
    cardnum = input("Card number: ")
    length = len(cardnum)

    while cardnum.isnumeric() == 0:
        print("INVALID")
        cardnum = input("Card number: ")

    # Check that the number is of a required length
    if cardnum.isnumeric() and length != 13 and length != 15 and length != 16:
        print("INVALID")
        return 'Error'

    i = length - 1
    sum_a = 0
    sum_b = 0

    # Iterate through the input number, applying Luhns algo
    while i >= 0:
        # Convert the string at i to an int
        floatnum = int(cardnum[i])
        i -= 1
        # Check if the number is meant to be doubled or not (see if it is second to last)
        if int((length - i) % 2) == 0:
            sum_a = sum_a + floatnum
        elif (2 * floatnum > 9):
            # Add the digits together if greater than 10
            sum_b = sum_b + ((2 * floatnum) % 10) + 1
        else:
            sum_b = sum_b + (2 * floatnum)

    # Check the output has a 0 at the end, for valid numbers.
    if (sum_a + sum_b) % 10 == 0:
        if length == 15 and cardnum[0] == '3' and cardnum[1] == '7' or cardnum[1] == '4':
            print("AMEX")
        elif ((length == 13 or length == 16) and (cardnum[0] == '4')):
            print("VISA")
        elif (length == 16 and cardnum[0] == '5' and (cardnum[1] == '1' or cardnum[1] == '2' or cardnum[1] == '3' or cardnum[1] == '4' or cardnum[1] == '5')):
            print("MASTERCARD")
        else:
            print("INVALID")
    else:
        print("INVALID")


if __name__ == "__main__":
    main()