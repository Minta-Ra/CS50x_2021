#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


int main(void)
{
    // Count letters
    string text = get_string("Type text: ");

    int letters = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
    }
    // printf("Letters: %i\n", (int) letters);



    // Count words
    int words = 1;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            words++;
        }
    }
    // printf("Words: %i\n", (int) words);



    // Count sentences
    int sentences = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    // printf("Sentences: %i\n", (int) sentences);



    // Calculating grade
    // Coleman-Liau index

    float L = (float) letters / words * 100;
    float S = (float) sentences / words * 100;

    float index = round(0.0588 * L - 0.296 * S - 15.8);
    printf("Grade %i\n", (int) index);



    // Before Grade 1 and 16+
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }


    return 0;
}



// index = 0.0588 * L - 0.296 * S - 15.8

// L - is the average number of letters per 100 words in the text
// S - is the average number of sentences per 100 words in the text

// Calculate how many:        letters   words   sentences        in the typed text
// then use the index formula

// count uppercase and lowercase