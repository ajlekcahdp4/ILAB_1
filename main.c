#include "Stack_test.h"
int main (void)
{
    Stack stk = {};
    StackCtor(&stk, 10);
    $meow
    StackPush(&stk, 1);
    $meow
    StackPush(&stk, 2);
    $meow
    StackPush(&stk, 2);
    $meow
    StackPush(&stk, 2);
    StackPush(&stk, 2);
    StackPush(&stk, 2);
    double x;
    StackPop(&stk, &x);
    printf("%f\n", x);
    StackPop(&stk, &x);
    printf("%f\n", x);

    StackDtor(&stk);
    return 0;
}
