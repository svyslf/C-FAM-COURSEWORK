#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pig.h"

void test()
{
    char *x = "happy";
    char *y = "duck";
    char *z = "glove";
    char *t = "evil";
    printf("%s => %s\n", x, pig(x));
    printf("%s => %s\n", y, pig(y));
    printf("%s => %s\n", z, pig(z));
    printf("%s => %s\n", t, pig(t));
}