import cs50
from cs50 import get_int

height = -1

while height < 0 or height > 23:
    height = get_int("Height: ")

i = 1

while i <= height:
    print(" " * (height - i), end="")
    print("#" * i, end="")
    print("  ", end="")
    print("#" * i)
    i += 1