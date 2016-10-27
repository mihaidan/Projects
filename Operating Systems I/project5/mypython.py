# # # # # # # # # # # # # 
# Program: mypython.py  #
# Author: Mihai Dan     #
# Class: CS 344         #
# Date: 10/21/2015      #
# # # # # # # # # # # # #

import random
import string

# Define the files function.
def files():
    # For loop to create three files
    for i in range(3):
        # Open file named file[i].txt
        file = open("file" + str(i) + ".txt", "w")
        
        print("Random characters in file" + str(i) + ":")
        
        # For loop placing 10 random lowercase
        # letters into the files, as well as
        # printing them to the screen.
        for j in range(10):
            line = random.choice(string.ascii_lowercase)
            file.write(line)
            print(line),
        file.close()
        print("\n")

# Define the numbers function.
def numbers():
    print("Here are two random numbers between 1 and 42:")

    # Assign num1 and num2 to a random number
    # between 1 and 42.
    num1 = random.randint(1, 42)
    num2 = random.randint(1, 42)

    print(str(num1) + " and " + str(num2))

    # Get their sum... 
    summer = num1 * num2

    #...and print it to the screen.
    print("Their product is " + str(summer) + ".")

# Define main.
def main():
    # Function calls.
    files()
    numbers()

# Call to main().
main()
