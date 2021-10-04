#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


int main(int argc, string argv[])
{
    // Get key - the amount we shift the character by - in the command-line argument

    if (argc != 2)     // || !isalpha(argv[1][1])
    {
        printf("Usage: ./caesar key \n");
        return 1;
    }
    else if (atoi(argv[1]) < 0)
    {
        printf("Usage: ./caesar key \n");
        return 1;
    }
    else // (isdigit(argv[1][1]))
    {

    }


    // Key
    int clNumber = atoi(argv[1]);


    // Get plain text from the user
    string text = get_string("Plaintext: ");


    // Encipher - shifting text by the key
    string shifted = text;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isupper(text[i]) && isalpha(text[i]))
        {
            char shiftedChar = (text[i] - 65 + clNumber) % 26 + 65;
            shifted[i] = shiftedChar;
        }

        else if (islower(text[i]) && isalpha(text[i]))
        {
            char shiftedChar = (text[i] - 97 + clNumber) % 26 + 97;
            shifted[i] = shiftedChar;
        }

    }
    // Print ciphertext
    printf("Ciphertext: %s\n", shifted);


    return 0;
}