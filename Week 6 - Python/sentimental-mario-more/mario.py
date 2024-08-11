from cs50 import get_int

height = 0
# Prompt user to enter int between 1 and 8 until he complies
while height not in range(1, 9):
    height = get_int("Please enter integert between 1 and 8.\n")

# increase height to get the proper range
height += 1

# print pyramides
for i in range(1, height):
    d = height - 1 - i
    print(" " * d + "#" * i + "  " + "#" * i)
