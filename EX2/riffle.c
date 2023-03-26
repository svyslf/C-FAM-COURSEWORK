#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void * riffle_once(void *L, int len, int size, void *work)
{
    int midpoint = len / 2;
    char *start = L;
    char *middle = start + (midpoint*size);
    char *end = start + ((len - 1)*size);
    char *work_pointer = work;

    int i; 
    srand(time(0));
    char originalMiddle = *middle;

    for (i = 0; i < len; i++)
    {
        if (*start == originalMiddle)
        {
            work_pointer = middle;
           
            middle+=size;
        }
        else if (middle > end)
        {
            work_pointer = start;
            
            start+=size;
        }
        else
        {
            int pick_direction = rand() % 2;

            if (pick_direction == 1 && (middle <= end))
            {
                work_pointer = middle;
               
                middle+=size;
            }
            else if (pick_direction == 0 && (start < middle))
            {
                work_pointer = start;
              
                start+=size;
            }
        }
       
        if (size == sizeof(int)) ((char *)work)[i] = *work_pointer;
        else strcat(strcat(((char*)work), " "), *(char**)work_pointer);

        work_pointer++;
    }

    return work; 
}


// void riffle(void *L, int len, int size, int N) {
//     int * work = malloc(size); 
//     riffle_once(L, len , size , work); 
// }
