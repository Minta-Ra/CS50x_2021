while True:

    while True:
        try:
            # Get height from the user
            height = int(input("Height: "))
            break
        # If I get ValueError
        except ValueError:
            # Ask again for an input - continue returns the control to the beginning of the while loop
            continue

    if height > 0 and height < 9:

        for i in range(height):
            # Print left pyramid
            print(" " * (height - i - 1) + "#" * (i + 1), end="  ")
            # Print right pyramid
            print("#" * (i + 1))
        # Break while statement
        break