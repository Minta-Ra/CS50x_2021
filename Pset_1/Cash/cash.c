#include <cs50.h>
#include <stdio.h>
#include <math.h>


int main(void)
{
    // TODO: Prompt for input
    float input;
    do
    {
        input = get_float("Change owed in dollars: ");
    }
    while (input < 0);

    // TODO: round to cents
    int cents = round(input * 100);


    int quarter = 25;
    int dime = 10;
    int nickel = 5;
    int penny = 1;


    // TODO: Calculate
    int sum = 0;


    while (cents > 0)
    {
        if (cents >= quarter)
        {
            cents = cents - quarter;
            sum++;
        }
        else if (cents >= dime)
        {
            cents = cents - dime;
            sum++;
        }
        else if (cents >= nickel)
        {
            cents = cents - nickel;
            sum++;
        }
        else if (cents >= penny)
        {
            cents = cents - penny;
            sum++;
        }
        // printf("%i", cents);
        // printf("\n");
    }
    printf("Left1: %i\n", sum);

}