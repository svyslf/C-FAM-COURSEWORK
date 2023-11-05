#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <string.h>
#include "../EX2/riffle.h"
#include "beggar.h"
#define MAX_SIZE 52

int main(int argc, char *argv[])
{

    int *deck = malloc(MAX_SIZE * sizeof(int));
    int i;

    for (i = 0; i < MAX_SIZE; i++)
    /* convert i to 52 to a standard deck representation */
    {
        deck[i] = i % 13 + 2;
    }
    srand(time(NULL));
    riffle(deck, MAX_SIZE, sizeof(int), 7);

    if (argc < 2){
        printf("Not enough arguments! Provide number of players and talkative value: 0 or 1");
        return -1;
    }

    int Nplayers = atoi(argv[1]);
    int talkative = atoi(argv[2]);

    if (Nplayers < 2)
    {
        printf("That's not enough players to play!");
        return -1;
    }
    else if (Nplayers > 25)
    {
        printf("hmm...That's too many players!");
        return -1;
    }
    beggar(Nplayers, deck, talkative);
    free(deck);
}