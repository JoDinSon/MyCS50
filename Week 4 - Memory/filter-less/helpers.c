#include <math.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // create dummy variable to temporarily save greyscaled image
    RGBTRIPLE dummy[height][width];

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            // create the average of the RGB values
            float av = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0;
            int average = round(av);

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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
        // create dummy variable to temporarily save greyscaled image
    RGBTRIPLE dummy[height][width];

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            // create the average of the RGB values
            float sepiaRed = image[i][j].rgbtBlue * .189 + image[i][j].rgbtGreen * .769 + image[i][j].rgbtRed * .393;
            float sepiaGreen = image[i][j].rgbtBlue * .168 + image[i][j].rgbtGreen * .686 + image[i][j].rgbtRed * .349;
            float sepiaBlue = image[i][j].rgbtBlue * .131 + image[i][j].rgbtGreen * .534 + image[i][j].rgbtRed * .272;

            // cap final value at 255
            if (sepiaRed > 255.0)
            {
                sepiaRed = 255.0;
            }

            if (sepiaGreen > 255.0)
            {
                sepiaGreen = 255.0;
            }

            if (sepiaBlue > 255.0)
            {
                sepiaBlue = 255.0;
            }


            // write the average to the dummy to leave pixels in the original picture untouched
            dummy[i][j].rgbtBlue = round(sepiaBlue);
            dummy[i][j].rgbtGreen = round(sepiaGreen);
            dummy[i][j].rgbtRed = round(sepiaRed);

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

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create dummy variable to temporarily save greyscaled image
    RGBTRIPLE dummy[height][width];

    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            //initialize color variable to sum up color values in the box
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
