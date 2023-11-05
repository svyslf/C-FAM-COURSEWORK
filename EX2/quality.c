#include <stdio.h>
#include "riffle.h"
#include <time.h> 
#include <stdlib.h>
/** @brief
 *  Driver program to check the quality of the riffle function over a set of shuffles over a set number of trials.
*/
int main() {
    srand(time(NULL));
    int N = 50; 
    int trials = 30; 
    int shuffles = 15; 
    int i; 
    
    FILE *file, *file2;
    file2 = fopen("new_quality.txt", "w");
    for(i=1; i<=shuffles; i ++ ){
        fprintf(file2, "average quality on %d shuffle(s):  %f \n", i, average_quality(N, i, trials));
    }
    fclose(file2);
    return 0; 
}