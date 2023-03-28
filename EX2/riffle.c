#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void riffle_once(void *L, int len, int size, void *work)
    /*
        riffle_once 
        -----------------------------------------------
        Riffles the Array L in place, as described in the spec.  
        Args:   void *L: array to riffle, int len: length of the array, 
                int size: size of the type of elem in array, void *work: temp array to work in 
    
    */
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
    /*
        riffle
        ----------------------------------------
        Calls riffle_once N number of times to do a proper shuffle in place. 
        Args:   void *L: the array to riffle, int len: length of the array, 
                int size: size of the type of elem in the array, 
                int N: Number of times it should be riffled.
    */
    int * work = malloc(size*len);
    int i;
    for ( i = 0; i < N; i ++){
       riffle_once(L, len , size , work);
    }
    free(work);
}

int find_elem(void *L_1 , void *L_2, int len, int size, int (*cmp)(void*, void*)){
    /* 
        find_elem
        --------------------------------------------------------------------------
        Finds whether element L_1 exists in array L_2, if it does, return 1 else return 0 

        Args:       void *L_1: The element to find , void *L_2: the array where you're searching for the element 
                    int len: length of the array you're searching through 
                    int size: size of the type of items in the array, 
                    int (*cmp)(void*, void*): comparison function to compare values. 
        Returns:    1 if found, 0 if not found. 
    
    */
    int i;
    int res; 
    for ( i = 0; i < len; i ++) {
        void * L_2_elem = L_2 + i *size;
        if (cmp(L_1, L_2_elem) == 0) {
            res = 1; 
            break;
        } else {
            res = 0; 
        }
    }
    return res; 
}

int check_shuffle(void *L, int len, int size, int (*cmp)(void *, void *)) {
    /* 
        check_shuffle 
        ---------------------------------------------------------------
        Makes a copy of the array to riffle, riffles it, and checks whether the riffled items exist in the original and vice versa.

        Args :      void *L: the array to shuffle , int len: length of the array, 
                    int size: size of the type of array, int (*cmp)(void *, void *): comparision function to compare array elems. 
        Returns :   int: 0 if the check fails, 1 if it succeeds. 

    */
    void *L_copy = malloc(len * size);
    memcpy(L_copy, L, len * size); 
    riffle(L_copy, len, size, 1);  
    int i; 
    int res = 1; 
    for (i = 0; i < len; i++) {
        void * L_i  = L + i * size;
        void * L_copy_i = L_copy + i * size; 
        int found_in_L_copy = find_elem(L_i, L_copy, len, size, cmp);
        int found_in_L = find_elem(L_copy_i, L, len, size, cmp);
        
        if (!found_in_L_copy || !found_in_L){
            res = 0;  
        } 
    }
    free(L_copy); 
    return res;
}


int cmp_int(void* L, void* L_riffled) {
    /* 
        cmp_int
        -----------------------------------
        Compares two integers by value. 

        Args:       void* L: integer in original array, void* L_riffled: integer in riffled array
        Returns:    int: 0 if they match, 1 if they don't

    */
    int *L_pointer = (int *)L;
    int *L_riffled_pointer = (int *)L_riffled;
    int i, j; 

    if (*L_pointer == *L_riffled_pointer){
        return 0; 
    }
    else if ( *L_pointer > *L_riffled_pointer) {
        return -1; 
    }
    else if ( *L_pointer < *L_riffled_pointer){
        return 1;
    }
    return 1; 
}

int cmp_str(void* L, void* L_riffled){
    /* 
        cmp_str
        ------------------------------
        Compares two strings by content. 

        Args:       void* L: string in original array, void* L_riffled: string in riffled array
        Returns:    int: 0 if they match, 1 if they don't
    */
    char * L_pointer = (char*)L;
    char *L_riffled_pointer= (char*)L_riffled;
    return strcmp(L_pointer, L_riffled_pointer); 
}

float quality(int *numbers, int len){
    /*
        quality 
        ---------------------------------
        Returns the quality of the shuffle which is determined by how often consecutive numbers are in ascending order.
        (more often => high quality value) (a quality value close to 0.5 is a good quality)

        Args:       int *numbers: the number array you've shuffled , int len: length of the number array
        Returns:    float: value of quality 

    */
    int larger = 0; 
    int i; 
    float quality = 0.0; 
    for(i =0; i < len ; i ++) {
        if(i+1 != len){
            if (numbers[i] < numbers[i+1]){
                larger += 1; 
            }
        }
    }   
    quality += (float)larger / (len-1); 
    return quality; 
}

float average_quality(int N, int shuffles, int trials) {
    /*
        average_quality 
        ----------------------------------------------------
        Returns the average quality per shuffle set over a number of trials
        Args:       int N: length of the number array
        Returns:    float value of quality 

    */
    int *to_shuffle = malloc( N * sizeof(int));
    if (to_shuffle == NULL){
        printf("Could not allocate enough memory");
        exit(-1);
    }

    int i, j, k;
    float total_quality = 0.0; 
 
    for ( i = 0; i < trials; i++){
        
        for ( j = 0 ; j < N; j++ ){
            to_shuffle[j] = j; 
        }
        riffle(to_shuffle, N, sizeof(int), shuffles);
        total_quality += quality(to_shuffle, N);
    }

    free(to_shuffle);
    float average_quality = total_quality / (float)trials;
    return average_quality;
}