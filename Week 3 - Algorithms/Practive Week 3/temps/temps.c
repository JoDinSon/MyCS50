// Practice working with structs
// Practice applying sorting algorithms

#include <cs50.h>
#include <stdio.h>

#define NUM_CITIES 10

typedef struct
{
    string city;
    int temp;
}
avg_temp;

avg_temp temps[NUM_CITIES];

void sort_cities_selection(void);
void sort_cities_bubble(void);

int main(void)
{
    temps[0].city = "Austin";
    temps[0].temp = 97;

    temps[1].city = "Boston";
    temps[1].temp = 82;

    temps[2].city = "Chicago";
    temps[2].temp = 85;

    temps[3].city = "Denver";
    temps[3].temp = 90;

    temps[4].city = "Las Vegas";
    temps[4].temp = 105;

    temps[5].city = "Los Angeles";
    temps[5].temp = 82;

    temps[6].city = "Miami";
    temps[6].temp = 97;

    temps[7].city = "New York";
    temps[7].temp = 85;

    temps[8].city = "Phoenix";
    temps[8].temp = 107;

    temps[9].city = "San Francisco";
    temps[9].temp = 66;

    sort_cities_bubble();

    printf("\nAverage July Temperatures by City\n\n");

    for (int i = 0; i < NUM_CITIES; i++)
    {
        printf("%s: %i\n", temps[i].city, temps[i].temp);
    }
}

// TODO: Sort cities by temperature in descending order
void sort_cities_selection(void)
{
    // Selection Sort

    int max_index; //index of the entrie with the highes temp


    for (int i = 0; i < NUM_CITIES; i++) // iterate through array
    {
        max_index = i; // set current entries temp to max
        for (int j = i; j < NUM_CITIES; j++) // iterate though array entries larger than i
        {
            if (temps[j].temp > temps[max_index].temp) // if current entries temp is larger than max
            {
                max_index = j; //current entries is the current max
            }
        }

        //swap
        avg_temp hold; // Dummie for the swap
        hold = temps[i];
        temps[i] = temps[max_index];
        temps[max_index] = hold;

    }

}

void sort_cities_bubble(void)
{
    //Bubble Sort (in descending order)

    int swap = -1; // Set a swap counter
    avg_temp hold; // Dummie for the swap
    while(swap != 0)
    {
        swap = 0; // set swap to zero
        for(int i = 0; i < NUM_CITIES-1; i++) //iterate through avg_temp array
        {
            if (temps[i].temp < temps[i+1].temp) // compare adjacent pairs
            // if two elements are not in descending order: swap
            {
                hold = temps[i];
                temps[i] = temps[i+1];
                temps[i+1] = hold;
                swap++; //increase swap by one
            }
        }
    }
}
