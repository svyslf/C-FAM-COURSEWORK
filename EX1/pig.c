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
    char *returnedWord = malloc(strlen(word) + 3);
    strcpy(returnedWord, word);

    char lower = tolower(*word);
    int StartsWithVowel = strcspn(&lower, "aeiou");
    int startsWithY = strcspn(&lower, "y");

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
