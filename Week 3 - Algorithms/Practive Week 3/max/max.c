// Practice writing a function to find a max value

#include <cs50.h>
#include <stdio.h>

int max(int array[], int n);

int main(void)
{
    int n;
    do
    {
        n = get_int("Number of elements: ");
    }
    while (n < 1);

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = get_int("Element %i: ", i);
    }

    printf("The max value is %i.\n", max(arr, n));
}

// TODO: return the max value
int max(int array[], int n)
{
    int max = array[0]; // initialize max variable and set it to first enry of array
    for (int i = 0; i < n; i++) // iterate through array
    {
        if (array[i] > max) // compare each value to current max value
        {
            max = array[i]; // if current array value is larger than max
            // it becomes the new max
        }
    }
    return max;
}
