#include "Stack.h"
int main (void)
{
    Stack stk = {};
    StackCtor (&stk, 10);
    StackPush (&stk, 100);
    StackPush (&stk, 100);
    StackPush (&stk, 100);
    StackPush (&stk, 100);
    StackPush (&stk, 100);
    StackPush (&stk, 100);
    StackPush (&stk, 100);
    StackPush (&stk, 100);
    StackPush (&stk, 100);
    StackPush (&stk, 100);
    StackPush (&stk, 100);
    StackPush (&stk, 100);
    double x = 0;
    StackPop(&stk, &x);
    StackPop(&stk, &x);
    StackPop(&stk, &x);
    printf("%g\n", x);
    StackPop(&stk, &x);
    printf("%g\n", x);
    StackDtor(&stk);
    return 0;
}

