#include <cs50.h>
#include <stdio.h>

// Llamas population growth

int main(void)
{
    // TODO: Prompt for start size
    int start;
    do
    {
        start = get_int("Start size (greater than or equal to 9):\n ");
    }
    while (start < 9);


    // TODO: Prompt for end size
    int end;
    do
    {
        end = get_int("End size (greater or equal to start size):\n ");
    }
    while (end < start);


    // Keep track on numbers of years
    int years = 0;

    // TODO: Calculate number of years until we reach threshold
    while (start < end)
    {
        start = start + (start / 3) - (start / 4);
        years++;
    }


    // TODO: Print number of years
    printf("Years: %i\n", years);
}

