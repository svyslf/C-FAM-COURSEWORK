#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../EX2/riffle.h"
#include "beggar.h"
#define MAX_SIZE 52

/**
 * @brief Represents the stats of a numerical data set. Includes shortest, longest, and the average values.
 *
 * @param shortest (int): the minimum value in the data set
 * @param longest (int): the maximum value in the data set
 * @param average (float): the mean of the data set
 *
 */
typedef struct
{
    int shortest;
    int longest;
    float average;
} Stats;

/**
 * @brief Simulates multiple games of beggar my neighbour returns stats on the length of the games.
 *
 * @param Nplayers (int): the number of players in each game
 * @param games (int): the numer of games to be simulated
 *
 * @returns stats: The struct representing a the stats calculated. Includes shortest, longest, and the average values.
 *
 */
Stats *statistics(int Nplayers, int games)
{
    Stats *stats = malloc(sizeof(Stats));
    int total_turns = 0;
    if (stats == NULL)
    {
        printf("Not enough memory!");
        exit(-1);
    }
    stats->shortest = -1;
    stats->longest = 0;

    int *deck = malloc(MAX_SIZE * sizeof(int));
    int turns_per_game, i, j;

    for (i = 0; i < MAX_SIZE; i++)
    /* convert i to 52 to a standard deck representation */
    {
        deck[i] = i % 13 + 2;
    }
    for (j = 0; j < games; j++)
    {
        /* Reshuffle deck each game */
        riffle(deck, MAX_SIZE, sizeof(int), 7);
        /*no. of turns returned in each round */
        turns_per_game = beggar(Nplayers, deck, 0);
        if (turns_per_game < stats->shortest || stats->shortest == -1)
        {

            stats->shortest = turns_per_game;
        }
        if (turns_per_game > stats->longest)
        {

            stats->longest = turns_per_game;
        }
        total_turns += turns_per_game;
    }
    float average_turns = (float)total_turns / (float)games;
    stats->average = average_turns;

    free(deck);
    return stats;
}
int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("Not enough arguments! Provide number of Max no. of players and games");
        return -1;
    }
    int Nplayers = atoi(argv[1]);
    int games = atoi(argv[2]);
    if (Nplayers < 2 || games < 2)
    {
        printf("Not enough players / games ");
        return -1;
    }
    else if (Nplayers > 25)
    {
        printf("hmm...That's too many players!");
        return -1;
    }

    FILE *file, *file2;
    file = fopen("statistics.txt", "w");
    file2 = fopen("User Stats.txt", "w");
    int i;
    for (i = 2; i <= 10; i++)
    {
        Stats *stats = statistics(i, 100);
        fprintf(file, "%d player game: Longest game: %d, Average game length: %f, Shortest game: %d \n", i, stats->longest, stats->average, stats->shortest);
    }
    fprintf(file, "Every game was played %d times.\n", 100);
    fclose(file);
    for (i = 2; i <= Nplayers; i++)
    {
        Stats *stats = statistics(i, games);
        fprintf(file2, "%d player game: Longest game: %d, Average game length: %f, Shortest game: %d \n", i, stats->longest, stats->average, stats->shortest);
    }
    fprintf(file2, "Every game was played %d times.\n", games);
    fclose(file2);
    return 0;
}