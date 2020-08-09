#include <stdio.h>
#include <stdlib.h>

/**
 *
 * @author HimelSaha
 */


int main(int argc, char *argv[])
{
    if (argc != 2)                      // checking for valid argument
    {
        printf("Usage: ./recover image(in raw format)\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");   // opening raw file
    if (file == NULL)
    {
        printf("File is empty\n");
        return 1;
    }

    // creating temporary block of memory and storing data from input file to check for start of JPEG file

    unsigned char bytes[512];           // buffer
    FILE *img = NULL;                   // output file
    int counter = 0;
    char *newJpeg = malloc(sizeof(bytes));

    // fread returning 0 means no data has been read, indicating end of file

    while (!((fread(&bytes, 512, 1, file)) == 0))             // reading 512 bytes of data from 'file' and storing in 'bytes'
    {

        // checking for the first 4 signature bytes of the JPEG file in the buffer

        // if JPEG header is encountered, it means the start of a new JPEG
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {
            if (img != NULL)
            {
                fclose(img);                                // the current file is closed and a new file is opened to write data to
            }

            // start writing if it represents a JPEG file
            sprintf(newJpeg, "%03i.jpg", counter);          // assigning new file name to the output file in 3-digit format
            img = fopen(newJpeg, "w");
            fwrite(&bytes, 512, 1, img);                    // writing 512 byes of data from 'bytes' to 'img'
            counter++;
        }
        else if (img != NULL)
        {
            fwrite(&bytes, 512, 1, img);                    // continue writing data
        }
    }

    // closing the input and output files and freeing allocated memory blocks

    free(newJpeg);
    fclose(img);
    fclose(file);
    return 0;
}
