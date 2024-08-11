#include <cs50.h>
#include <stdio.h>

int collatz(int n);

int main(void)
{
    int input = get_int("Please enter positive non zero number:\n");
    printf("Number of steps: %i\n", collatz(input));
}

int collatz(int n)
{
    // Base Case
    if (n == 1)
        return 0;
    // Recursive Case 1 - even numbers
    else if (n % 2 == 0)
        return 1 + collatz(n / 2);
    // Recursive Case 2 - odd numbers
    else if (n % 2 == 1)
        return 1 + collatz(3 * n + 1);

    return 0;
}