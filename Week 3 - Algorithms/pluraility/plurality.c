#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }

    }

    // Display winner of election
     print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{

    for (int i = 0; i < candidate_count; i++) //interate through candidates array
    {
        if (strcmp(candidates[i].name, name) == 0) //compare each canditate with vote user input
        {
            candidates[i].votes += 1; //if vote name is in candidate array - update number of votes of candidate
            return true; // return true to indicate successful vote
        }
    }
    return false; // return false if name is not in candidate array leading to output "invalid vote"

}


void print_winner(void)
{

    //Print the winner (or winners) of the election (Bubble Sort)

    int swap = -1; // Set a swap counter
    candidate hold; // Dummie for the swap
    while(swap != 0)
    {
        swap = 0; // set swap to zero
        for(int i = 0; i < candidate_count-1; i++) //iterate through avg_temp array
        {
            if (candidates[i].votes < candidates[i+1].votes) // compare adjacent pairs
            // if two elements are not in descending order: swap
            {
                hold = candidates[i];
                candidates[i] = candidates[i+1];
                candidates[i+1] = hold;
                swap++; //increase swap by one
            }
        }
    }
    int most_votes = candidates[0].votes;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == most_votes)
        {
            printf("%s\n", candidates[i].name);
        }
    }
    return;
}