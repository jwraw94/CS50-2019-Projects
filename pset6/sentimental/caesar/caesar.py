import cs50
import sys
from cs50 import get_string


def main():
    count = len(sys.argv)

    # Check correct no. of arguments
    if count != 2:
        print("Usage: ./caesar k")
        sys.exit(1)
    else:
        print("plaintext: ", end="")
        instring = get_string()
        print("ciphertext: ", end="")

    # Set input to an int, to be the cipher.
    k = int(sys.argv[1])

    # Iterate through the input string, converting to relevant ASCII values dpending on case. Do not change if not alphabetic.
    for i in instring:
        if i.islower():
            j = ((ord(i) + k - 97) % 26) + 97
            print((chr(j)), end="")
        elif i.isupper():
            j = ((ord(i) + k - 65) % 26) + 65
            print((chr(j)), end="")
        else:
            print(i, end="")

    print()


if __name__ == "__main__":
    main()