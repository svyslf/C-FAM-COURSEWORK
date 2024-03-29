#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
/**
 * @brief  
 * "Riffles" the array L in place once, following the methodology discussed in the specification.
 * 
 * @param  *L::void The array to riffle
 * @param len::int The length of the array
 * @param size::int The size of the type of elem in array
 * @param *work::void The temp array to work in
 * 
*/
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

    int pick_direction = rand() % 2;
    for (i = 0; i < len; i++)
    {
        if (pick_direction == 1 && (middle_pointer <= end))
        /* assign work_pointer to the values in the 2nd half of the "deck" */
        {
            memcpy(riffled, middle_pointer, size);
            riffled += size;
            middle_pointer += size;
        }
        if (pick_direction == 0 && (start_pointer < middle_pointer))
        /* assign work_pointer to the values in the 1st half of the "deck" */
        {
            memcpy(riffled, start_pointer, size);
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

/**
 * @brief  
 * "Riffles" the Array L in place N times, following the methodology discussed in the specification.
 * 
 * @param  *L::void The array to riffle
 * @param len::int The length of the array
 * @param size::int The size of the type of elem in array
 * @param N::int The number of times the array must be shuffled 
 * 
*/
void riffle(void *L, int len, int size, int N)
{

    int *work = malloc(size * len);
    int i;
    for (i = 0; i < N; i++)
    {
        riffle_once(L, len, size, work);
    }
    free(work);
}

/**
 * @brief 
 * Finds whether element L_1 exists in array L_2, if it does, return 1 else return 0
 * 
 * @param *L_1::void The element to find 
 * @param *L_2::void The array where you're searching for the element
 * @param len::int length of the array you're searching through
 * @param size::int size of the type of items in the array,
 * @param (*cmp)::int comparison function to compare values.
 * 
 * @returns 
 * int: 1 if element was found, 0 if it was not found.
*/
int find_elem(void *L_1, void *L_2, int len, int size, int (*cmp)(void *, void *))
{

    int i;
    int res;
    for (i = 0; i < len; i++)
    {
        void *L_2_elem = L_2 + i * size;
        if (cmp(L_1, L_2_elem) == 0)
        {
            res = 1;
            break;
        }
        else
        {
            res = 0;
        }
    }
    return res;
}

/**
 * @brief
 * Makes a copy of the array to riffle, riffles it, and checks whether the riffled items exist in the original and vice versa.
 * @param *L::void The array to shuffle 
 * @param len:int length of the array
 * @param size::int size of the type of array 
 * @param (*cmp)::int comparision function to compare array elems
 * 
 * @returns 
 * int: 0 if the check fails, 1 if it succeeds.
 *  
*/
int check_shuffle(void *L, int len, int size, int (*cmp)(void *, void *))
{

    void *L_copy = malloc(len * size);
    memcpy(L_copy, L, len * size);
    riffle(L_copy, len, size, 1);
    int i;
    int res = 1;
    for (i = 0; i < len; i++)
    {
        void *L_i = L + i * size;
        void *L_copy_i = L_copy + i * size;
        int found_in_L_copy = find_elem(L_i, L_copy, len, size, cmp);
        int found_in_L = find_elem(L_copy_i, L, len, size, cmp);

        if (!found_in_L_copy || !found_in_L)
        {
            res = 0;
        }
    }
    free(L_copy);
    return res;
}

/**
 *  @brief
 *  Compares two integers by value.
 *  @param L::void* integer in original array, void* L_riffled: integer in riffled array
 * 
 *  @returns    
 *  int: 0 if they match, 1 if they don't
*/
int cmp_int(void *L, void *L_riffled)
{

    int *L_pointer = (int *)L;
    int *L_riffled_pointer = (int *)L_riffled;
    int i, j;

    if (*L_pointer == *L_riffled_pointer)
    {
        return 0;
    }
    else if (*L_pointer > *L_riffled_pointer)
    {
        return -1;
    }
    else if (*L_pointer < *L_riffled_pointer)
    {
        return 1;
    }
    return 1;
}

/**
 *  @brief
 *  Compares two strings by content.
 *  @param L::void* string in original array, void* L_riffled: string in riffled array
 *  @returns   
 *  int: 0 if they match, 1 if they don't
*/
int cmp_str(void *L, void *L_riffled)
{

    char *L_pointer = (char *)L;
    char *L_riffled_pointer = (char *)L_riffled;
    return strcmp(L_pointer, L_riffled_pointer);
}

/**
 *  @brief
 *  Returns the quality of the shuffle which is determined by how often consecutive numbers are in ascending order. 
 *  
 *  (more often/not often enough => high/low numerical value => bad quality) 
 *  A good quality value is close to 0.5.
 * 
 *  @param *numbers::int the number array you've shuffled , int len: length of the number array
 *  @returns
 *  float: value of quality
*/
float quality(int *numbers, int len)
{

    int larger = 0;
    int i;
    float quality = 0.0;
    for (i = 0; i < len; i++)
    {
        if (i + 1 != len)
        {
            if (numbers[i] < numbers[i + 1])
            {
                larger += 1;
            }
        }
    }
    quality += (float)larger / (len - 1);
    return quality;
}

/**
 *  @brief
 *  Returns the average quality per set of shuffles over a number of trials
 *  @param N::int length of the number array
 *  @returns
 * float: value of quality
*/
float average_quality(int N, int shuffles, int trials)
{

    int *to_shuffle = malloc(N * sizeof(int));
    if (to_shuffle == NULL)
    {
        printf("Could not allocate enough memory");
        exit(-1);
    }

    int i, j, k;
    float total_quality = 0.0;

    for (i = 0; i < trials; i++)
    {

        for (j = 0; j < N; j++)
        {
            to_shuffle[j] = j;
        }
        riffle(to_shuffle, N, sizeof(int), shuffles);
        total_quality += quality(to_shuffle, N);
    }

    free(to_shuffle);
    float average_quality = total_quality / (float)trials;
    return average_quality;
}