#include <stdio.h>
#include <stdlib.h>
#define NDEBUG 1
#include <assert.h>
#include <stdbool.h>

#define $meow printf("meow from %s (%d) from %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);


#define PTR_DATA_CANARY1 (long*)((char*)stk->data - sizeof(long long))
#define PTR_DATA_CANARY2 (long*)((char*)stk->data + stk->capacity * sizeof(TYPE_NAME))

#define ERR_STACK_UNDERFLOW "(ERR_STACK_UNDERFLOW)"
#define CHECK "(CHECK)"

#define ERR_PTR 0
enum ERRORS {ERR_WRONG_STK_PTR = 1, ERR_WRONG_CAPACITY, ERR_WRONG_SIZE, ERR_WRONG_CANARY, ERR_WRONG_HASH};


/*
#if TYPE == double
#define FMT "%g"
#endif // TYPE

#if TYPE == int
#define FMT "%d"
#endif // TYPE

#if TYPE == char
#define FMT "%c"
#endif // TYPE
*/


//Changeable for the type you need
#define FMT "%g"
typedef double TYPE_NAME;
//

typedef struct Stack
{
    long long canary1;

    FILE * log_file;
    long long hash;

    int capacity;
    size_t size;
    TYPE_NAME * data;

    long long canary2;
}Stack;

long long HashCulc (Stack * stk)
{
    long long HASH = 0;
    for (int i = 0; i < (stk->capacity * sizeof (TYPE_NAME) + 2 * sizeof (long long) - 1); i++)
    {
        HASH += ((unsigned int)*((char*)stk->data - sizeof(long long) + i)) * i;
    }
    for (char* ptr = (char*)&stk->canary1; ptr < (char*)(&stk->canary2 + sizeof (long long)); ptr++)
    {
        if (ptr < (char*)&stk->hash || ptr >= (char*)&stk->capacity)
            HASH += ((unsigned int)(*ptr))* (int)(ptr - (char*)&stk->canary1);
    }
    return HASH;
}

int StackOk (Stack * stk)
{
    if (stk == 0)
        return ERR_WRONG_STK_PTR;
    if (stk->capacity < 1)
        return ERR_WRONG_CAPACITY;
    if (stk->size > stk->capacity)
        return ERR_WRONG_SIZE;
    if (stk->size < 0)
        return ERR_WRONG_SIZE;
    if (stk->canary1 != (long long)&stk->canary1)
        return ERR_WRONG_CANARY;
    if (stk->canary2 != (long long)&stk->canary2)
        return ERR_WRONG_CANARY;
    if (*PTR_DATA_CANARY1 != (long long)PTR_DATA_CANARY1)
        return ERR_WRONG_CANARY;
    if (*PTR_DATA_CANARY2 != (long long)PTR_DATA_CANARY2)
        return ERR_WRONG_CANARY;
    if (stk->hash != HashCulc(stk))
        return ERR_WRONG_HASH;
    return 0;
}

void StackDump (Stack * stk, char * string)
{
    assert (stk != 0);
    fprintf (stk->log_file, "Stack [%p] %s\n", stk, string);
    fprintf (stk->log_file, "{\n");
    fprintf (stk->log_file, "%4scanary1 = %X\n", "", stk->canary1);
    fprintf (stk->log_file, "%4scapacity = %d\n", "", stk->capacity);
    fprintf (stk->log_file, "%4ssize = %d\n", "",stk->size);
    fprintf (stk->log_file, "%4sdata[%p]\n", "", stk->data);
    fprintf (stk->log_file, "%4s{\n", "");
    fprintf (stk->log_file, "%8sdata canary 1 = %X\n", "", *PTR_DATA_CANARY1);
    int i = 0;
    for (i = 0; i < stk->capacity; i ++)
    {
        if (i < stk->size)
        {
            fprintf (stk->log_file, "%8s*[%d] = ", "", i);
            fprintf (stk->log_file, FMT, stk->data[i]);
            fprintf (stk->log_file, "\n");
        }
        else
            fprintf (stk->log_file, "%8s [%d] = %g\n", "", i, stk->data[i]);
    }
    fprintf (stk->log_file, "%8sdata canary 2 = %X\n", "", *PTR_DATA_CANARY2);
    fprintf (stk->log_file, "%4s}\n", "");
    fprintf (stk->log_file, "%4scanary2 = %X\n", "", stk->canary2);
    fprintf (stk->log_file, "}\n\n\n");

}

void StackCheck (Stack * stk)
{
    int errors = StackOk(stk);
    switch (errors)
    {
    case ERR_WRONG_STK_PTR:
        StackDump (stk, "(ERR_WRONG_STK_PTR)");
        break;
    case ERR_WRONG_CAPACITY:
        StackDump (stk, "(ERR_WRONG_CAPACITY)");
        break;
    case ERR_WRONG_SIZE:
        StackDump (stk, "(ERR_WRONG_SIZE)");
        break;
    case ERR_WRONG_CANARY:
        StackDump (stk, "(ERR_WRONG_CANARY)");
        break;
    case ERR_WRONG_HASH:
        StackDump (stk, "(ERR_WRONG_HASH)");
        break;
    default:;
    }
}
void StackCtor(Stack * stk, int capacity)
{
    assert(stk != 0);
    assert (capacity > 2);
    stk->log_file = fopen ("Logfile.txt", "w");
    stk->canary1 = (long long)(&(stk->canary1));
    stk->canary2 = (long long)(&(stk->canary2));

    stk->data = (TYPE_NAME *) calloc (capacity*sizeof(TYPE_NAME) + 2*sizeof(long long), sizeof(char));
    stk->capacity = capacity;

    stk->data = (TYPE_NAME*)((char*)stk->data + 1 * sizeof(long long));

    *PTR_DATA_CANARY1 = (long long)PTR_DATA_CANARY1;
    *PTR_DATA_CANARY2 = (long long)PTR_DATA_CANARY2;


    stk->size = 0;
    stk->hash = HashCulc (stk);

}


void StackResize (Stack * stk, size_t capacity)
{
    StackCheck (stk);
    stk->capacity = capacity;
    stk->data = (TYPE_NAME*) realloc ((void*)((char*)stk->data - sizeof(long long)), stk->capacity * sizeof(TYPE_NAME) + 2 * sizeof (long long));
    assert (stk->data != 0);
    stk->data = (TYPE_NAME*)((char*)stk->data + 1 * sizeof(long long));
    *PTR_DATA_CANARY1 = (long long)PTR_DATA_CANARY1;
    *PTR_DATA_CANARY2 = (long long)PTR_DATA_CANARY2;

    for (int i = stk->size; i < stk->capacity; i++)
    {
        stk->data[i] = 0;
    }

    StackDump (stk, "(RESIZED)");
    stk->hash = HashCulc (stk);
    StackCheck (stk);
}
void StackPush (Stack * stk, TYPE_NAME value)
{
    StackCheck (stk);
    assert (stk != 0);
    if (stk->size == stk->capacity)
    {
        StackResize(stk, stk->capacity + 10);
    }
    stk->data[stk->size] = value;
    stk->size++;
    stk->hash = HashCulc (stk);
    StackCheck (stk);
}

int StackPop(Stack * stk, TYPE_NAME * value)
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
        *value = stk->data[stk->size - 1];
        stk->data[stk->size - 1] = 0;
        stk->size--;
    }
    stk->hash = HashCulc (stk);
    StackCheck (stk);
    return 0;
}




void StackDtor (Stack * stk)
{
    assert (stk != 0);
    StackCheck (stk);
    StackDump (stk, "(END)");
    free ((char*)stk->data - sizeof(long long));
    fclose(stk->log_file);
    stk->data = ERR_PTR;
}
