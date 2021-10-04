#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for height from 1 to 8
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);


    // TODO: print left pyramid #
    for (int hash1 = 0; hash1 < height; hash1++)
    {
        for (int hash2 = 0; hash2 < height; hash2++)
        {
            if (hash1 + hash2 >= height - 1)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }


        // TODO: print space between #  #
        printf("  ");


        // TODO: print right pyramid #
        for (int hash3 = 0; hash3 < hash1 + 1; hash3++)
        {
            printf("#");
        }

        printf("\n");
    }
}










// IF LESS CONFORTABLE OPTION:

// #include <cs50.h>
// #include <stdio.h>

// int main(void)
// {
//     // TODO: Prompt for height from 1 to 8
//     int height;
//     do
//     {
//         height = get_int("Height: ");
//     }
//     while (height < 1 || height > 8);


//     // TODO: print #
//     for (int hash1 = 0; hash1 < height; hash1++)
//     {
//         for (int hash2 = 0; hash2 < height; hash2++)
//         {
//             if (hash1 + hash2 >= height - 1)
//             printf("#");
//             else
//             printf(" ");
//         }
//         printf("\n");
//     }
// }


