#include "helpers.h"

// important for edge detection (root function)
#include <math.h>

// for printf() to troubleshoot code
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // create dummy variable to temporarily save greyscaled image
    RGBTRIPLE dummy[height][width];

    //int count = 0; For testing

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            // create the average of the RGB values
            float av = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            int average = round(av);

            //count++; Also for testing

            /* Area for testing and troubleshooting
            printf("%i\n", count);
            printf("B: %i\nG: %i\nR: %i\n", image[i][j].rgbtBlue, image[i][j].rgbtGreen, image[i][j].rgbtRed);
            printf("%f : %i\n\n", av, average);
            */

            // write the average to the dummy to leave pixels in the original picture untouched
            dummy[i][j].rgbtBlue = average;
            dummy[i][j].rgbtGreen = average;
            dummy[i][j].rgbtRed = average;

        }
    }

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            // write dummy to the image
            image[i][j] = dummy[i][j];
        }
    }


    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // create dummy variable to temporarily save greyscaled image
    RGBTRIPLE dummy[height][width];

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            /* Fill dummy with the pixels from the image starting with the largest index in the row aka width-1 and working its way until it reaches the left most
            pixel. Aka 0*/
            dummy[i][j] = image[i][width-1-j];
            //printf("%i\n", width-1-j);

            /* Area for testing and troubleshooting*/
            //printf("{%i, %i, %i}, ", dummy[i][j].rgbtBlue, dummy[i][j].rgbtGreen, dummy[i][j].rgbtRed);
        }
        //printf("\n");
    }

    // Write Dummy to output image
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            // write dummy to the image
            image[i][j] = dummy[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create dummy variable to temporarily save greyscaled image
    RGBTRIPLE dummy[height][width];

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            int red = 0;
            int green = 0;
            int blue = 0;

            float pixel_count = 0.0;

            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if (i+k < 0 || i+k >= height || j+l < 0 || j+l >= width)
                    {
                        continue;
                    }
                    else
                    {
                        red += image[i+k][j+l].rgbtRed;
                        green += image[i+k][j+l].rgbtGreen;
                        blue += image[i+k][j+l].rgbtBlue;

                        pixel_count += 1.0;
                    }
                }
            }
            float new_red = red / pixel_count;
            float new_green = green / pixel_count;
            float new_blue = blue / pixel_count;

            dummy[i][j].rgbtRed = round(new_red);
            dummy[i][j].rgbtGreen = round(new_green);
            dummy[i][j].rgbtBlue = round(new_blue);
        }

    }

    // Write Dummy to output image
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            // write dummy to the image
            image[i][j] = dummy[i][j];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    /*------------------------------------------------------------------------------------------
    // convert to greyscale
    RGBTRIPLE grey[height][width];


    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            // create the average of the RGB values
            float av = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            int average = round(av);

            // write the average to the dummy to leave pixels in the original picture untouched
            grey[i][j].rgbtBlue = average;
            grey[i][j].rgbtGreen = average;
            grey[i][j].rgbtRed = average;

        }
    }

    ------------------------------------------------------------------------------------------*/
    // Making the kernels
    int kernel_Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int kernel_Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    // Make a new rgbt array with a 1 pixel thick black padding;
    int pad_height = height + 2;
    int pad_width = width + 2;

    RGBTRIPLE padding[pad_height][pad_width];

    for (int i = 0; i < pad_height; i++)
    {
        for (int j = 0; j < pad_width ; j++)
        {
            if (i == 0 || i == height + 1 || j == 0 || j == width + 1)
            {
            padding[i][j].rgbtRed = 0;
            padding[i][j].rgbtBlue = 0;
            padding[i][j].rgbtGreen = 0;
            }
            else
            {
                padding[i][j] = image[i-1][j-1];
            }
        }
    }
    /*
    for (int i = 1; i < height+1; i++)
    {
        printf("\nRow %i:\n", i);
        for (int j = 1; j < width+1; j++)
        {
            printf("R: %i\nG: %i\nB: %i\n\n", padding[i][j].rgbtRed, padding[i][j].rgbtGreen, padding[i][j].rgbtBlue);
        }
        printf("\n");
    }
    */

    // create dummy image to temporarily save filtered image
    RGBTRIPLE dummy[height][width];

    // Iterate over Padding leaving out the actual black padding
    for (int i = 1; i < pad_height - 1; i ++)
    {
        for (int j = 1; j < pad_height - 1; j++)
        {
            //initializing Gx values
            int gx_red = 0;
            int gx_green = 0;
            int gx_blue = 0;

            //initializing Gy values
            int gy_red = 0;
            int gy_green = 0;
            int gy_blue = 0;

            //printf("\nRow %i Pixel %i:\n", i, j);


            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {

                    //if (i+k < height && i+k >= 0 && j+l < width && j+l >= 0)
                    //{
                    // Calculating Gx values
                    //printf("Redx\n%i + %i * %i\n", gx_red, image[i+k][j+l].rgbtRed, kernel_Gx[k+1][l+1]);
                    gx_red += image[i+k][j+l].rgbtRed * kernel_Gx[k+1][l+1];
                    gx_green += image[i+k][j+l].rgbtGreen * kernel_Gx[k+1][l+1];
                    gx_blue += image[i+k][j+l].rgbtBlue * kernel_Gx[k+1][l+1];

                    //printf("R: %i\nG: %i\nB: %i\n\n", padding[i+k][j+l].rgbtRed, padding[i+k][j+l].rgbtGreen, padding[i+k][j+l].rgbtBlue);


                    // Calculating Gy values
                    // printf("Redy\n%i + %i * %i\n\n", gy_red, image[i+k][j+l].rgbtRed, kernel_Gy[k+1][l+1]);
                    gy_red += image[i+k][j+l].rgbtRed * kernel_Gy[k+1][l+1];
                    gy_green += image[i+k][j+l].rgbtGreen * kernel_Gy[k+1][l+1];
                    gy_blue += image[i+k][j+l].rgbtBlue * kernel_Gy[k+1][l+1];
                   // }
                }
            }
        //    printf("\n");

            //Calulate the final value for the color channels
            int final_red = round(sqrt(gx_red * gx_red + gy_red * gy_red));
            int final_green = round(sqrt(gx_green * gx_green + gy_green * gy_green));
            int final_blue = round(sqrt(gx_blue * gx_blue + gy_blue * gy_blue));

            // cap final value at 255
            if (final_red > 255)
            {
                final_red = 255;
            }

            if (final_green > 255)
            {
                final_green = 255;
            }

            if (final_blue > 255)
            {
                final_blue = 255;
            }

            //
            dummy[i][j].rgbtBlue = final_blue;
            dummy[i][j].rgbtGreen = final_green;
            dummy[i][j].rgbtRed = final_red;

            printf("%i %i %i\n", final_red, final_green, final_blue);

        }
    }

    // Write Dummy to output image
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            // write dummy to the image
            image[i][j] = dummy[i][j];
        }
    }

    return;
}
