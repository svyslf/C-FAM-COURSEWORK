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
    char *response;
    printf("%s => %s\n", x, response = pig(x));
    printf("%s => %s\n", y, response = pig(y));
    printf("%s => %s\n", z, response = pig(z));
    printf("%s => %s\n", t, response = pig(t));
    free(response);

}
int main() {
    test();
}