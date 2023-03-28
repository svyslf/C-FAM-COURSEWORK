#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "pig.h"
/* The pig function returns a pig latin-ified version of the word entered
 */
char *pig(char *word)
// TODO: assign memory properly to returnedWord
{
   
    char lower = tolower(*word);
    int StartsWithVowel = strcspn(&lower, "aeiou");
    int startsWithY = strcspn(&lower, "y");
    char *returnedWord = malloc((strlen(word) + 3)*sizeof(char));
    int size; 
    size = (StartsWithVowel == 0) ? 3: 2;
    returnedWord = (StartsWithVowel == 0) ? malloc((strlen(word) + size) * sizeof(char)): malloc((strlen(word) + size) * sizeof(char));
    strcpy(returnedWord, word);

    if (StartsWithVowel == 0)
    {
        strcat(returnedWord, "way");
        return returnedWord;
    }

    while (*returnedWord != ' ')
    {

        char character = *returnedWord;
        int isVowel = (startsWithY == 0) ? strcspn(&character, "aeiou") : strcspn(&character, "aeiouy");

        if (isVowel != 0)
        {
            strncat(returnedWord, &character, 1);
            returnedWord++;
        }
        else
        {
            strcat(returnedWord, "ay");

            return returnedWord;
        }
    }

    return 0;
}
