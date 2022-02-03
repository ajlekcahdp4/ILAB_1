#include "Stack.h"

int main (void)
{
    Stack * stk = (Stack*)calloc(1, sizeof(Stack));
    StackCtor (stk, 1024);
    StackPush (stk, 100);
    StackPush (stk, 100);
    StackPush (stk, 100);
    StackPush (stk, 100);
    StackPush (stk, 100);
    StackPush (stk, 100);
    int x = 0;
    StackPop(stk, &x);
    printf("%d\n", x);
    StackPop(stk, &x);
    printf("%d\n", x);
    StackPop(stk, &x);
    printf("%d\n", x);
    StackDtor(stk);
    return 0;

}
