#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Declares a data type called BYTE
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Ask for one command line argument
    if (argc != 2)
    {
        // Return 1 otherwise
        return 1;
    }

    // Open memory card
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        fclose(file);
        // Return 1 if forensic image cannot be opened
        return 1;
    }


    int counter = 0;
    int jpegFound = 0;
    // Create empty string for filename
    char *filename = malloc(8);
    FILE *recovered;
    // Create a buffer - size 512 bytes
    BYTE buffer [512];


    // Repeat until end of card: read 512 bytes into buffer
    while (fread(buffer, sizeof(BYTE), 512, file) != 0)
    {

        // Check first 4 bytes of a new jpeg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {


            // Close the old recovered file and start writing new one
            if (jpegFound == 1)
            {
                fclose(recovered);
            }
            else
            {
                jpegFound = 1;
            }


            // Create a new jpeg filename and open it
            sprintf(filename, "%03i.jpg", counter);

            recovered = fopen(filename, "w");

            // Incrament image counter - start from 000.jpg, 001.jpg...
            counter++;
        }


        // Keep writing data in 512 byte chunks until a new jpeg is found
        if (jpegFound == 1)
        {
            fwrite(&buffer, sizeof(BYTE), 512, recovered);
        }


    }
    // Close input file
    fclose(file);
    // Close last photo
    fclose(recovered);
    // Free malloc space
    free(filename);
    // Success
    return 0;
}