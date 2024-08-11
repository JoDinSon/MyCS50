#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    // TODO
    int index = strlen(input)-1; // get last index of last char
    // base case
    if (index < 0) // if length of string is 0 return 0
    {
        return 0;
    }

    // recursive case

    if (input[index] >= '0' && input[index] <= '9') //if char is between 0 and 9
    {
        char last = input[index]; // save last char to 'last'
        input[index] = '\0'; // move null terminator one position to the left
        return convert(input) * 10 + last - '0'; // call function mutply it by 10 and add the digit
        // behind char last to the output
    }
    return 0;
}