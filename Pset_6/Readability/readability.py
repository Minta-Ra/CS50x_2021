from cs50 import get_string


while True:
    try:
        text = get_string("Type text: ")
        if text.isalpha() or " ":
            break
    except VelueError:
        continue


# Count letters
letters = 0

for l in range(len(text)):
    # if text[l] != numpy.sign(l):      # REQUIRES import numpy
    if text[l].isalpha():
        letters += 1

# print(letters)


# Count words
words = 1

for w in range(len(text)):
    if text[w] == " ":
        words += 1

# print(words)


# Count sentences
sentences = 0

for s in range(len(text)):
    if text[s] == "." or text[s] == "!" or text[s] == "?":
        sentences += 1

# print(sentences)


# Calculating grade
# Coleman-Liau index

L = letters / words * 100
S = sentences / words * 100

index = round(0.0588 * L - 0.296 * S - 15.8)


# Print grades
if index < 0:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print("Grade: ", index)