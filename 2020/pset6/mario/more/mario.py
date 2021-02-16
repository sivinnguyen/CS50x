from cs50 import get_int

while True:  # Get height
    h = get_int("Height: ")
    if h > 0 and h < 9:  # Prompt user for positive integer between 1 and 8
        break

w = h * 2 + 2  # Width of the paramid

for i in range(h):  # Prints out the pyramid
    for j in range(w):
        if (j >= h - i - 1 and j < h) or (j > h + 1 and j < h + i + 3):
            print("#", end="")
        elif j < h - i - 1 or (j >= h and j <= h + 1):  # Avoid error: did you add too much trailing whitespace
            print(" ", end="")
    print()