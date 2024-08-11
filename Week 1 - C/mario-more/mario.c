#include <cs50.h>
#include <stdio.h>

int get_height(void);
void make_pyr(int h);

int main(void)
{
    // Getting correct User input
    int h = 0;

    while (h < 1 || h > 8)
    {
        h = get_height();
    }

    // Gernerating Pyramids

    make_pyr(h);

}

int get_height(void)
{
    int h = get_int("Height: ");
    return h;
}

void make_pyr(int h)
{
    string hash = "#";

    for (int i = 1; i < h + 1; i++)
    {
        for (int y = 0; y < h - i; y++)
        {
            printf(" ");
        }
        for (int y = 0; y < i; y++)
        {
            printf("%s", hash);
        }
        printf("  ");
        for (int y = 0; y < i; y++)
        {
            printf("%s", hash);
        }
        printf("\n");
    }
}