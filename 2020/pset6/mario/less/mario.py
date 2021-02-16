from cs50 import get_int

while True:  # Get height
    h = get_int("Height: ")
    if h > 0 and h < 9:  # Prompt user for positive integer between 1 and 8
        break

for i in range(h):  # Prints out the haft-pyramid
    for j in range(h):
        if j < (h - i - 1):
            print(" ", end="")
        else:
            print("#", end="")
    print()

# style50 for python is suck