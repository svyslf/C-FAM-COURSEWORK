#include <stdio.h>
#include "riffle.h"
#include <time.h> 
#include <stdlib.h>
int main() {
    /*
        quality.c 
        ----------
        Driver program to check the quality of the riffle function over a set of shuffles during a set number of trials.
    */
    srand(time(NULL));
    int N = 50; 
    int trials = 30; 
    int shuffles = 15; 
    int i; 
    for(i=1; i<=shuffles; i ++ ){
        printf("average quality on shuffle %d:  %f \n", i, average_quality(N, i, trials));
    }
    return 0; 
}