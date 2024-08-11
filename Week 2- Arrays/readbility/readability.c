#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    string text = get_string("Please Enter text: ");


    double letters = count_letters(text);
    double words = count_words(text);
    double sentences = count_sentences(text);

    double L = letters / words * 100;
    double S = sentences / words * 100;

    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index > 15)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }
}

int count_letters(string text)
{
    // Compute number of letters and return as int
    int length = strlen(text);
    int letter_count = 0;
    for (int i = 0; i < length; i++)
    {
        if (isalpha(text[i]))
        {
            letter_count++;
        }
    }
    return letter_count;
}

int count_words(string text)
{
    //compute number of word and return as int
    int length = strlen(text);
    int word_count = 1;
    for (int i = 0; i < length; i++)
    {
        if (text[i] == 32)
        {
            word_count++;
        }
    }
    return word_count;
}

int count_sentences(string text)
{
    //Compute number of sentences and return as int
    int length = strlen(text);
    int sentence_count = 0;
    for (int i = 0; i < length; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentence_count++;
        }
    }
    return sentence_count;
}
