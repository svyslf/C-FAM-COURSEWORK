#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void riffle_once(void *L, int len, int size, void *work)
{
    memcpy(work, L, len * size);
    int midpoint = len / 2;
    char *riffled = L; 
    char *middle = work + (midpoint * size);
    char *end = work + ((len - 1) * size);
    

    char *start_pointer = work;
    char *middle_pointer = middle; 
    int i;
    srand(time(0));

    int pick_direction = rand() % 2;
    for (i = 0; i < len; i++)
    {
        if (pick_direction == 1 && (middle_pointer <= end))
        /* assign work_pointer to the values in the 2nd half of the "deck" */
        {
            memcpy(riffled,  middle_pointer, size);
            riffled += size; 
            middle_pointer += size;
        }
        if (pick_direction == 0 && (start_pointer < middle_pointer))
        /* assign work_pointer to the values in the 1st half of the "deck" */
        {
            memcpy(riffled,  start_pointer, size);
            riffled += size; 
            start_pointer += size;
        }

        if (start_pointer == middle)
        /* if there's nothing left to shuffle in the 2nd half, pick from 1st half */
        {
            pick_direction = 1;
        }

        else if (middle_pointer > end)
        /* if there's nothing left to shuffle in the 1st half, pick from 2nd half */
        {
            pick_direction = 0;
        }

        else
        /* if there are items left in both sides, pick one side randomly */
        {
            pick_direction = rand() % 2;
        }
    }
}

void riffle(void *L, int len, int size, int N) {
    int * work = malloc(size);
    int i;
    for ( i = 0; i < N; i ++){
       riffle_once(L, len , size , work);
    }
    free(work);
}
