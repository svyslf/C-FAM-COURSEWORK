#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pig.h"

int main()
{
    // test();
    char input[255];
    char *string, *word;

    do
    {

        printf("\n Enter Sentence: ");

        string = fgets(input, sizeof(input), stdin);
        string[strcspn(string, "\n")] = 0; // remove newline
        while ((word = strsep(&string, " ")) != NULL)
        {
            printf("%s ", pig(word));
        }

    } while (input[0] != '\n');

    return 0;
}