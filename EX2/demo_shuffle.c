#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "riffle.h"


int main()
{
    int i;
    int L[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    size_t size_L = sizeof(L);
    size_t len_L = size_L / sizeof(int);
    int * work_L = malloc(size_L);
    int * shuffled_L = riffle_once(L, len_L, sizeof(int), work_L);
    
    for( i = 0 ; i < len_L ; i ++){
        printf(" %d ", ((char*)shuffled_L)[i]);
    }
    free(work_L);
   

       
    printf("\n");
    char *greek[] = {"alpha", "beta", "gamma", "delta", "epsilon", "zeta", "eta", "theta", "iota", "kappa", "lambda", "mu"};
    size_t greek_size = sizeof(greek);
    size_t len_G = greek_size / sizeof(greek[0]);
    int *work_G = malloc(greek_size);
    int * shuffled_G = riffle_once(greek, len_G, sizeof(greek[0]), work_G);
 
    printf("%s", ((char*)shuffled_G));
    free(work_G);
   
    return 0;
}