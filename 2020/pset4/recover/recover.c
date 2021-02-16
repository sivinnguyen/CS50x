#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc != 2)
    {
        // https://cboard.cprogramming.com/c-programming/100766-whats-difference-between-printf-fprintf-stdout-fprintf-stderr.html
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // Remember filenames
    char *infile = argv[1];

    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // Create buffer
    BYTE buffer[512];

    // To count recovered image number
    int imageCount = 0;

    // File name i'll be writing to
    char filename[8];
    // Output file pointerS
    FILE *outptr = NULL;

    // Read the file
    // https://stackoverflow.com/questions/10696845/does-fread-move-the-file-pointer
    // https://www.udemy.com/blog/fread-c/
    while (fread(buffer, sizeof(buffer), 1, inptr) == 1)
    {
        // Looking for JPEG header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (imageCount > 0)
            {
                fclose(outptr); // close current file
            }

            // Write to outfile
            sprintf(filename, "%03i.jpg", imageCount); // set filename;
            outptr = fopen(filename, "w");
            imageCount++; // increase number of found image
        }

        // write anytime we have an open file
        if (outptr != NULL)
        {
            fwrite(buffer, sizeof(buffer), 1, outptr);
        }
    }


    // Close last file
    fclose(outptr);
    // Close infile
    fclose(inptr);

    // Success
    return 0;
}
