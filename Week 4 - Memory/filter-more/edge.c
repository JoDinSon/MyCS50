#include <stdio.h>

int main(void)
{
    int height = 3;
    int width = 3;
    // create kernels
    // int kernel_Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    // int kernel_Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("Current Pixe[%i, %i]\n", i, j);
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    printf("[%i, %i] ", i+k, j+l);
                }
                printf("\n");
            }
            printf("\n");
        }
    }

}

