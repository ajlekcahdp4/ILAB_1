#include <stdio.h>
#include <stdlib.h>
#define NDEBUG 1
#include <assert.h>
#include <stdbool.h>

#define $meow printf("meow from %s (%d) %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);

#define CANARY1 0xBE31AB
#define CANARY2 0xDEDBEDA
#define CANARY3 0xDEDBAD
#define CANARY4 0xC0FFEE

#define ERR_STACK_UNDERFLOW "(ERR_STACK_UNDERFLOW)"
#define CHECK "(CHECK)"

#define ERR_PTR 0

typedef struct Stack
{
    long canary1;
    int capacity;
    size_t size;
    double * data;
    long canary2;
}Stack;

int StackOk (Stack * stk)
{
    if (stk == 0)
        return 0;
    if (stk->capacity < 1)
        return 0;
    if (stk->size > stk->capacity)
        return 0;
    if (stk->size < 0)
        return 0;
    if (stk->canary1 != CANARY1)
        return 0;
    if (stk->canary2 != CANARY2)
        return 0;
    if (stk->data[0] != CANARY3)
        return 0;
    if (stk->data[stk->capacity + 1] != CANARY4)
        return 0;
    return 1;
}

void StackDump (Stack * stk, char * string)
{
    assert (stk != 0);
    FILE * log_file = fopen ("Logfile.txt", "w");
    fprintf (log_file, "Stack [%p] %s\n", stk, string);
    fprintf (log_file, "{\n");
    fprintf (log_file, "%4scanary1 = %x\n", "", stk->canary1);
    fprintf (log_file, "%4scapacity = %d\n", "", stk->capacity);
    fprintf (log_file, "%4ssize = %d\n", "",stk->size);
    fprintf (log_file, "%4sdata[%p]\n", "", stk->data);
    fprintf (log_file, "%4s{\n", "");
    fprintf (log_file, "%8sc[0] = %x\n", "", (long)stk->data[0]);
    int i = 1;
    for (i = 1; i <= stk->capacity; i ++)
    {
        if (i <= stk->size)
            fprintf (log_file, "%8s*[%d] = %x\n", "", i, stk->data[i]);
        else
            fprintf (log_file, "%8s [%d] = %x\n", "", i, stk->data[i]);
    }
    fprintf (log_file, "%8sc[%d] = %x\n", "", i, (long)stk->data[i]);
    fprintf (log_file, "%4s{\n", "");
    fprintf (log_file, "}\n");

}

void StackCheck (Stack * stk)
{
    if (StackOk(stk) != true)
    {
        StackDump (stk, "(ERR)");
        assert (0);
    }
    else
        StackDump (stk, "(OK)");
}
void StackCtor(Stack * stk, int capacity)
{
    assert(stk != 0);
    assert (capacity > 2);
    stk->canary1 = CANARY1;
    stk->canary2 = CANARY2;
    stk->data = (double *) calloc (capacity + 2, sizeof(double));
    assert (stk->data != 0);
    stk->data[0] = CANARY3;
    stk->data[capacity + 1] = CANARY4;
    stk->capacity = capacity;
    stk->size = 0;
}


void StackResize (Stack * stk, size_t capacity)
{
    StackCheck (stk);
    StackCheck (stk);
    stk->data = (double *) realloc (stk->data, capacity);
    stk->capacity = capacity - 2;
    stk->data[capacity + 1] = CANARY4;
    StackCheck (stk);
}
void StackPush (Stack * stk, double value)
{
    StackCheck (stk);
    assert (stk != 0);
    if (stk->size == stk->capacity)
    {
        StackResize(stk, stk->capacity * 2);
    }
    stk->size++;
    stk->data[stk->size] = value;
    StackCheck (stk);
}

int StackPop(Stack * stk, double * value)
{
    StackCheck (stk);
    assert (stk != 0);
    if (stk->size == 0)
    {
        StackDump (stk, ERR_STACK_UNDERFLOW);
        return 1;
    }
    else
    {
        *value = stk->data[stk->size];
        stk->size--;
    }
    StackCheck (stk);
    return 0;
}



void StackDtor (Stack * stk)
{
    StackCheck(stk);
    assert (stk != 0);
    free (stk->data);
    stk->data = ERR_PTR;
}
