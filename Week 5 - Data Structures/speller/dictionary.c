// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 676;

// Hash table
node *table[N];

// Keep track of size of dictionary
unsigned int count = 0;

// Create search function to search Lists recursively
bool search(node *cursor, const char *word);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash word to obtain hash value

    int h = hash(word);

    if (table[h] == NULL)
    {
        return false;
    }
    else
    {
        node *cursor = table[h];
        while (cursor != NULL)
        {
            if (strcasecmp(cursor->word, word) == 0)
            {
                return true;
            }
            cursor = cursor->next;

        }
    }
    return false;

}

bool search(node *cursor, const char *word)
{
    // Traverse linked list, looking for the word (strcasecmp)
    if (cursor == NULL)
    {
        return false;
    }
    else if (strcasecmp(cursor->word, word) == 0)
    {
        return true;
    }
    else
    {
        //printf("%s\n", cursor->word);
        return search(cursor->next, word);
    }
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    int hash = 0;
    
    if (word[1] != 0)
    {
        hash = (toupper(word[0]) - 'A') * 26 + (toupper(word[1]) - 'A');
    }
    else
    {
        hash = toupper(word[0]) - 'A';
    }


    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // open file
    FILE *f = fopen(dictionary, "r");
    // check wether file opening successful
    if (f == NULL)
    {
        return false;
    }

    // read strings from file one at a time
    // fscanf returns "EOF" once it reaches end of file propbably into word
    char new_word[LENGTH + 1];
    while (fscanf(f, "%s", new_word) != EOF)
    {
        // create a new node for each word
        node *n = malloc(sizeof(node));

        // check if running out of memory
        if (n != NULL)
        {
            n->next = NULL;
            strcpy(n->word, new_word);
        }
        else
        {
            fclose(f);
            free(n);
            return false;
        }
        // compute hash value of new_word
        int h = hash(n->word);

        // insert node into hash table
        if (table[h] == NULL)
        {
            // if there are no nodes, pointer in table should point to n
            table[h] = n;
        }
        else
        {
            // let next pointer of new node n point to same adress as table[h] points to
            n->next = table[h];
            // let table[h] point to new node n
            table[h] = n;
        }
        count++;


    }

    fclose(f);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *cursor = NULL;

    int c = 0;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
        table[i] = NULL;
    }

    return true;
}
