#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

void name(char ciph[]);
void append_encr(int i, char a, char encr[], char ciph[]);
string alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

/*Have to check wether there are (multiple) duplicates in the key.
So for example if there is two time the letter Y in the key the program should exit with code 1.
Maybe convert whole key into upper case for comparison. CAn reuse or shift the code from the "name funkction*/

int main(int argc, string argv[])
{
   if (argc == 2)
   /*Check wether exactly one command line argument was given*/
   {
      if (strlen(argv[1]) == 26)
      /*Check wether key is 26 characters long*/
      {
         /*correct becomes 0 if one of the characters in the key is not in the alphabet*/
         int correct = 1;
         for (int i = 0; i < 26; i++)
         {
            if (isalpha(argv[1][i]) == 0)
            {
               correct = 0;
            }
         }
         if (correct == 1)
         {
            /* Here has to be the code for deciding wether key has duplicates*/
            char ciph[26];
            /*first convert key to capital letters*/
            for (int i = 0; i <26; i++)
            {
               ciph[i] = toupper(argv[1][i]);
            }
            /*Iterates through newly created upper case string and compares each letter to the whole string
            if ciph[i] and ciph [y] is equal more than one time there should be a duplicate and the program should exit while returning 1 before the
            "name" function is called.*/
            for (int i = 0; i < 26; i++)
            {
               int count = 0;
               for (int y = 0; y < 26; y++)
               {
                  if (ciph[i] == ciph[y])
                  {
                     count++;
                  }
               }
               if (count > 1)
               {
                  printf("Please avoid duplicates in your key!\n");
                  return 1;
               }
            }
            name(ciph);
         }
         else
         {
            printf("Usage: ./substitution key\n");
            return 1;
         }

      }
      else
      {
         printf("Key must contain 26 characters.\n");
         return 1;
      }

   }
   else
   {
      printf("Usage: ./substitution key\n");
      return 1;
   }
}

void name(char ciph[])
{
   /*just didnt come up with a good name for the funtion. It basically does all the work here. It's kind of the main function.
   Main is just the basic arror catching part in this programm.-*/


   string plaintext = get_string("plaintext: ");
   int length = strlen(plaintext);
   char encr[length];

   for (int i = 0; i < length; i++)
   {
      if (isalpha(plaintext[i]))
      {
         append_encr(i, plaintext[i], encr, ciph);
      }
         else if (plaintext[i] == 0)
      {
         encr[i] = 32;
        /*Adds a space where input plain text has a space*/
      }
      else
      {
         encr[i] = plaintext[i];
      }
   }

   encr[length] = '\0'; /*turns character array "encr" into a pseudo string*/

   printf("ciphertext:  %s\n", encr);
}



void append_encr(int i, char a, char encr[], char ciph[])
{
   /*Gets index of plaintext input string and corresponding character. It then maps the charcter to the correct character in the key (ciph)
   and appends the character array encr with that mapped character*/
   char arg = toupper(a);

   int k = 0;
   while (arg != alph[k])
   {
      k++;
      if (k > 26)
      {
         printf("Character not found!\n");
      }
   }
   if (isupper(a))
   {
      encr[i] = ciph[k];
   }
   else
   {
      encr[i] = tolower(ciph[k]);
   }
}

