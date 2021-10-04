from sys import argv, exit
from csv import reader, DictReader


if len(argv) != 3:
    print("Missing command-line argument")
    # sys.exit(1) equivalent to return 1; in C
    exit(1)

#########################################################

# Open csv. file, convert to dictionary
with open(argv[1], "r") as csvFile:
    reader = DictReader(csvFile)
    # Create an array for each person (objects)
    dictList = list(reader)

# Open sequences file, convert to list
with open(argv[2], "r") as file:
    sequence = file.read()

#########################################################

# Take a string (s) and get a substring of it - s[i:j]
# Start from i and finish at position j

# For each STR find the longest repeated sequence
# "sequence" is a string; return substring with all characters from the i'th character up to (but not including the j'th)

maxCounts = []

for i in range(1, len(reader.fieldnames)):
    STR = reader.fieldnames[i]
    # append ADDING TO THE END OF THE maxCounts LIST WITHOUT DELETING ANYTHING
    maxCounts.append(0)

    # Loop through sequence to find STR
    for j in range(len(sequence)):
        STRcount = 0

        # If match found, count how many times it is repeated
        # Slicing up the hole sequence to STR size pieces
        # START : FINISH (+j KEEPS INCRAMENTING)
        if sequence[j: (len(STR) + j)] == STR:

            # print(sequence[j:(j + len(STR))])
            # print(STR)
            # print(" ")
            # print(sequence)

            count = 0

            while sequence[(count + j): (count + len(STR) + j)] == STR:
                STRcount += 1
                # If we foud the STR, skip by the whole size of STR
                count += len(STR)

            # If we found a new max repeated, update maxCounts
            # -1 because the array starts from 0
            if STRcount > maxCounts[i - 1]:
                maxCounts[i - 1] = STRcount

#########################################################

# dictList[i] - dictionary of one person
# reader.fieldnames[j] - key to look at the dictionary

# print(dictList[0]["AATG"])
# print(dictList)
# print(reader.fieldnames)

# Compare against the data if any matches
for i in range(len(dictList)):
    match = 0

    for j in range(1, len(reader.fieldnames)):

        # -1 as our maxCounts DOES NOT HAVE field "name", so we start from 0
        if int(maxCounts[j - 1]) == int(dictList[i][reader.fieldnames[j]]):
            match += 1

        if match == (len(reader.fieldnames) - 1):
            print(dictList[i]["name"])
            exit(1)

#########################################################

# Otherwise
print("No match")

#########################################################

# LIST
# Alice = [2,8,3]

# OBJECT
# Alice = {
#     AGATC : 2
#     AATG : 8
#     TATC : 3
# }