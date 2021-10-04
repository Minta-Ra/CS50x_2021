// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    // fread - the file I have
    // fwrite - to the new file
    // How many bytes do we want in the headder - [HEADER_SIZE]
    uint8_t headder [HEADER_SIZE];  // BUFFER REPRESENTING THE HEADDER
    fread(headder, HEADER_SIZE, 1, input);
    fwrite(headder, HEADER_SIZE, 1, output);


    // TODO: Read samples from input file and write updated data to output file
    int16_t buffer;

    // Loop through the file until you get to the end of the file
    while (fread(&buffer, sizeof(uint16_t), 1, input))
    {
        // Multiply each sample by factor - change volume
        buffer = buffer * factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }


    // Close files
    fclose(input);
    fclose(output);
}