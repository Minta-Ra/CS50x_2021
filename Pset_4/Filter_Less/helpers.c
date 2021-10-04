// FIRST ROW OF IMAGE - image[0]
// LAST ROW OF IMAGE - image[height-1]
// FIRST AND SECOND PIXEL ON LEFT TOP - image[0][0] ; image[0][1]...
// image[2][3].rgbtBlue = 0;
// image[2][3].rgbtGreen = 0;
// image[2][3].rgbtRed = 0;

#include <math.h>
#include "helpers.h"



// R,G,B VALUES FOR GREYSCALE HAS TO BE THE SAME
// (R + G + B) / 3 - CALCULATE AN AVERAGE OF COLOURS TO GET GRAYSCALE
// LOOPING THROUGH PIXELS AND round()

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            int avg = round((image[a][b].rgbtBlue + image[a][b].rgbtGreen + image[a][b].rgbtRed) / 3.0);
            image[a][b].rgbtBlue = avg;
            image[a][b].rgbtGreen = avg;
            image[a][b].rgbtRed = avg;
        }
    }
    return;
}


// ALGORITHM FOR SEPIA:
// sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
// sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
// sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue

// ROUND NUMBER TO GET INT VALUE
// VALUES NEED TO BE IN RANGE REPRESENTABLE BY 8-BITS OF MEMORY - MAX VALUES NOT TO EXCEED 255

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int c = 0; c < height; c++)
    {
        for (int d = 0; d < width; d++)
        {
            int sepiaBlue = round(.272 * image[c][d].rgbtRed + .534 * image[c][d].rgbtGreen + .131 * image[c][d].rgbtBlue);
            int sepiaGreen = round(.349 * image[c][d].rgbtRed + .686 * image[c][d].rgbtGreen + .168 * image[c][d].rgbtBlue);
            int sepiaRed = round(.393 * image[c][d].rgbtRed + .769 * image[c][d].rgbtGreen + .189 * image[c][d].rgbtBlue);

            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            image[c][d].rgbtBlue = sepiaBlue;
            image[c][d].rgbtGreen = sepiaGreen;
            image[c][d].rgbtRed = sepiaRed;
        }
    }
    return;
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // SET UP TEMP FILE - 1 BYTE
    RGBTRIPLE temp [height][width];

    for (int e = 0; e < height; e++)
    {
        // WIDTH DIVIDE TO 2
        for (int f = 0; f < (width / 2); f++)
        {
            // swap
            temp[e][f] = image[e][f];
            image[e][f] = image[e][width - f - 1];
            image[e][width - f - 1] = temp[e][f];
        }
    }
    return;
}


// TAKING AVERAGE OF 9 ORIGINAL COLOUR PIXELS - WITHIN 1 ROW && 1 COLUMN
// EDGE PIXELS - AVERAGE COLOUS OF SURROUNDING PIXELS
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // // SET UP TEMP FILE - 1 BYTE
    RGBTRIPLE temp [height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float blurBlue = 0;
            float blurGreen = 0;
            float blurRed = 0;
            int squareCount = 0;



            blurBlue += image[i][j].rgbtBlue;
            blurGreen += image[i][j].rgbtGreen;
            blurRed += image[i][j].rgbtRed;
            squareCount++;


            if (i + 1 < height)
            {
                blurBlue += image[i + 1][j].rgbtBlue;
                blurGreen += image[i + 1][j].rgbtGreen;
                blurRed += image[i + 1][j].rgbtRed;
                squareCount++;
            }

            if (j + 1 < width)
            {
                blurBlue += image[i][j + 1].rgbtBlue;
                blurGreen += image[i][j + 1].rgbtGreen;
                blurRed += image[i][j + 1].rgbtRed;
                squareCount++;
            }

            if (i + 1 < height && j + 1 < width)
            {
                blurBlue += image[i + 1][j + 1].rgbtBlue;
                blurGreen += image[i + 1][j + 1].rgbtGreen;
                blurRed += image[i + 1][j + 1].rgbtRed;
                squareCount++;
            }

            if (i - 1 >= 0)
            {
                blurBlue += image[i - 1][j].rgbtBlue;
                blurGreen += image[i - 1][j].rgbtGreen;
                blurRed += image[i - 1][j].rgbtRed;
                squareCount++;
            }

            if (j - 1 >= 0)
            {
                blurBlue += image[i][j - 1].rgbtBlue;
                blurGreen += image[i][j - 1].rgbtGreen;
                blurRed += image[i][j - 1].rgbtRed;
                squareCount++;
            }

            if (i - 1 >= 0 && j - 1 >= 0)
            {
                blurBlue += image[i - 1][j - 1].rgbtBlue;
                blurGreen += image[i - 1][j - 1].rgbtGreen;
                blurRed += image[i - 1][j - 1].rgbtRed;
                squareCount++;
            }

            if (i + 1 < height && j - 1 >= 0)
            {
                blurBlue += image[i + 1][j - 1].rgbtBlue;
                blurGreen += image[i + 1][j - 1].rgbtGreen;
                blurRed += image[i + 1][j - 1].rgbtRed;
                squareCount++;
            }

            if (i - 1 >= 0 && j + 1 < width)
            {
                blurBlue += image[i - 1][j + 1].rgbtBlue;
                blurGreen += image[i - 1][j + 1].rgbtGreen;
                blurRed += image[i - 1][j + 1].rgbtRed;
                squareCount++;
            }

            // STORE BLUR TO TEMP
            temp[i][j].rgbtBlue = round(blurBlue / squareCount);
            temp[i][j].rgbtGreen = round(blurGreen / squareCount);
            temp[i][j].rgbtRed = round(blurRed / squareCount);

        }
    }

    // COPY TEMP IMAGE INTO IMAGE
    for (int g = 0; g < height; g++)
    {
        for (int h = 0; h < width; h++)
        {
            image[g][h] = temp[g][h];
        }
    }


    return;
}