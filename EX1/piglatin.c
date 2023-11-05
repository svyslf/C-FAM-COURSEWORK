#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pig.h"
/** @brief
 *  The driver function that runs the interactive pig-latin converter.
*/
int main()
{
    
    char input[255];
    char *string, *word, *response;

    while (strlen(input) > 1){ 
        printf("\n");
        printf("Enter Sentence: ");

        /* get user input */
        string = fgets(input, sizeof(input), stdin);
        /* remove trailing newline that is inserted by fgets*/
        string[strcspn(string, "\n")] = 0; 
        while ((word = strsep(&string, " ")) != NULL)
        {
            if (*word == '\0') {
                // skip word if it's empty
                continue; 
            }
            printf("%s ", response = pig(word));
        }
    }
    free(response);
    return 0;
}