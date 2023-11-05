#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "riffle.h"
/** @brief
 *  Driver program to demo the riffle, check_shuffle and associated functions using the data provided.
 */
int main()
{
    srand(time(NULL));
    int i;
    int L[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
    size_t size_L = sizeof(L);
    size_t len_L = size_L / sizeof(int);
    riffle(L, len_L, sizeof(int), 30);
    int check_L = check_shuffle(L, len_L, sizeof(int), cmp_int);

    printf("\n Number shuffle result: %d. The shuffled array is:\n", check_L);

    for (i = 0; i < len_L; i++)
    {
        printf(" %d ", L[i]);
    }
    printf("\n");

    char *greek[] = {"alpha", "beta", "gamma", "delta", "epsilon", "zeta", "eta", "theta", "iota", "kappa", "lambda", "mu"};
    size_t greek_size = sizeof(greek);
    size_t len_G = greek_size / sizeof(greek[0]);
    riffle(greek, len_G, sizeof(greek[0]), 30);
    int check_greek = check_shuffle(L, len_L, sizeof(int), cmp_str);

    printf("\n Greek shuffle result: %d. The shuffled array is:\n", check_greek);

    for (i = 0; i < len_G; i++)
    {
        printf("%s ", greek[i]);
    }
    printf("\n");

    return 0;
}