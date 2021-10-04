#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};



//int compute_score(string word);

int main(void)
{
    // Get input words from both players

    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");



    // Score word1

    // int score1 = compute_score(word1);
    int score1 = 0;
    int letter1 = 0;

    for (int i = 0, n = strlen(word1); i < n; i++)
    {
        if (isalpha(word1[i]))
        {
            word1[i] = toupper(word1[i]);
        }
        else
        {
            word1[i] = 0;
        }

        letter1 = (int) word1[i] - 65;
        score1 = score1 + POINTS[letter1];

        // printf("%i\n", score1);
    }



    // Score word2

    // int score2 = compute_score(word2);
    int score2 = 0;
    int letter2 = 0;

    for (int j = 0, o = strlen(word2); j < o; j++)
    {
        if (isalpha(word2[j]))
        {
            word2[j] = toupper(word2[j]);
        }
        else
        {
            word2[j] = 0;
        }

        letter2 = (int) word2[j] - 65;
        score2 = score2 + POINTS[letter2];

        // printf("%i\n", score2);
    }



    // TODO: Print the winner

    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 == score2)
    {
        printf("Tie\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }


    return 0;
    return 0;
}


// int compute_score(string word)
// {
//     // TODO: Compute and return score for string
// }