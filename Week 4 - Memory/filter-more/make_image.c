#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(void)
/* A Programm that was frankensteined from the bottomup.c program. It takes an image as input but only to steal the Header information for the Bitmap File. It
then can change the size of the image and fill it with individually chosen pixels. So far the pixels and the size have to hard coded into the Programm in
Line 56 - 70.
*/
{
    // Ensure proper usage
    /*
    if (argc != 3)
    {
        printf("Usage: copy infile outfile\n");
        return 1;
    }
    */

    // Remember filenames
    char *infile = "Header.bmp";
    char *outfile = "Minibmp.bmp";

    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // Open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("Could not create %s.\n", outfile);
        return 3;
    }

    // Read (steal) infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // Read (steal) infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        printf("Unsupported file format.\n");
        return 4;
    }
/*--------------Enter desired size and pixel colors here------------------*/

    int n = 2;

    bi.biWidth = n;
    bi.biHeight = n;

    // create 3D array holding the 2D picel array and the colors of each individual pixel
    int colors[3][3][3] = {
        {{0, 10, 25}, {0, 10, 30}, {40, 60, 80}}, // first row
         {{20, 30, 90}, {30, 40, 100}, {80, 70, 90}}, // second row
          {{20, 20, 40}, {30, 10, 30}, {50, 40, 10}}}; // third row

/*---------------------------End Input here------------------------------*/

    // Write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Determine padding for scanlines
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // fill RGBTRIPLE array with the color values
    RGBTRIPLE triple[n][n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            triple[i][j].rgbtBlue = colors[i][j][0];
            triple[i][j].rgbtGreen = colors[i][j][1];
            triple[i][j].rgbtRed = colors[i][j][2];
        }
    }

    // Iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // Iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // Temporary storage


            // Read RGB triple from infile
            //fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // Write RGB triple to outfile
            fwrite(&triple[i][j], sizeof(RGBTRIPLE), 1, outptr);
        }

        // Skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // Then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // Close infile
    fclose(inptr);

    // Close outfile
    fclose(outptr);

    // Success
    return 0;

}