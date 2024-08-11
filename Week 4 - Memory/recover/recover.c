#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;


int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./revocer infile\n");
        return 1;
    }

    // Open input file
    FILE *raw = fopen(argv[1], "r");
    if (raw == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    //define Block Size
    int blocksize = 512;

    // initialize buffer
    BYTE buffer[blocksize];



    // open first file outside of loop
    FILE *outptr = fopen("000.jpg", "w");

    // create filename array
    char filename[8];
    int count = 0;

    // create boolean to check wether the first file has been encountered
    int file_found = 0;

    // iterate through file in blocks of blocksize
    while (fread(buffer, 1, blocksize, raw) == blocksize)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        // check for beginning of a jpg file
        {
            if (file_found == 0)
            // makes file_found true if the first jpg file i encountered
            {
                file_found = 1;
            }

            if (count > 0) // second and all following files
            {
                // close previous file
                fclose(outptr);

                // create next filename
                sprintf(filename, "%03i.jpg", count);

                // open next file and write first block to it
                outptr = fopen(filename, "w"); // note: dont declare file variable again, reuse the existing one
                fwrite(buffer, 1, blocksize, outptr);
            }
            else
            {
                // write to first file while count is 0
                fwrite(buffer, 1, blocksize, outptr);
            }
            // increase file count
            count++;
        }
        else if (file_found == 1)
        {
            // if no start of a new file is detected continue to write blocks to the open output file
            fwrite(buffer, 1, blocksize, outptr);
        }
    }

    // close files
    fclose(raw);
    fclose(outptr);

}
