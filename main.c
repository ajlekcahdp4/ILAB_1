#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main ()
{
    Queue *que = (Queue*)calloc(1, sizeof(Queue));
    int x = 0;
    QueCtor (que, 10);
    QuePushB (que, 1);
    QuePushB (que, 2);
    QuePushB (que, 3);

    QuePopF (que, &x);
    printf ("%d\n", x);

    QuePopF (que, &x);
    printf ("%d\n", x);

    QuePopF (que, &x);
    printf ("%d\n", x);
    
    QueDtor (que);
    return 0;
}