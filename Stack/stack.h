#ifndef STACK_INCLUDED
#define STACK_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

#define NDEBUG 1

#define $meow printf("meow from %s (%d) from %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);


#define PTR_DATA_CANARY1 (long*)((char*)stk->data - sizeof(long long))
#define PTR_DATA_CANARY2 (long*)((char*)stk->data + stk->capacity * sizeof(TYPE_NAME))


#define ERR_STACK_UNDERFLOW "(ERR_STACK_UNDERFLOW)"
#define CHECK "(CHECK)"

#define ERR_PTR (TYPE_NAME*)666


#define DOUBLE 0
#define INT 1
#define CHAR 2
#define LONG 3
#define LONG_LONG 4
#define UNSIGNED 5
#define UNSIGNED_LONG 6
#define UNSIGNED_LONG_LONG 7




//Changeable for the type you need
#define TYPE INT
//

#if TYPE == DOUBLE
#define TYPE_NAME double
#define FMT "%g"
#endif

#if TYPE == INT
#define TYPE_NAME int
#define FMT "%d"
#endif

#if TYPE == CHAR
#define TYPE_NAME char
#define FMT "%c"
#endif

#if TYPE == LONG
#define TYPE_NAME long
#define FMT "%ld"
#endif

#if TYPE == LONG_LONG
#define TYPE_NAME long long
#define FMT "%lld"
#endif

#if TYPE == UNSIGNED
#define TYPE_NAME unsigned
#define FMT "%u"
#endif

#if TYPE == UNSIGNED_LONG
#define TYPE_NAME unsigned long
#define FMT "%lu"
#endif

#if TYPE == UNSIGNED_LONG_LONG
#define TYPE_NAME unsigned long long
#define FMT "%llu"
#endif


enum ERRORS
{
    ERR_WRONG_STK_PTR = 1, ERR_WRONG_DATA_PTR, ERR_WRONG_CAPACITY, ERR_WRONG_SIZE, ERR_WRONG_CANARY, ERR_WRONG_HASH, ERR_DOUBLE_DTOR, ERR_DAMAGED_CONTENT};
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

static long long HashCalc (Stack * stk);
static int StackOk (Stack * stk);
void StackDump (Stack * stk, char * string);
void StackCheck (Stack * stk);
void StackCtor(Stack * stk, int capacity);
void StackResize (Stack * stk, size_t capacity);
void StackPush (Stack * stk, TYPE_NAME value);
int StackPop(Stack * stk, TYPE_NAME * value);
void StackDtor (Stack * stk);
int ZerosCheck (Stack * stk);
#endif // STACK_INCLUDED
