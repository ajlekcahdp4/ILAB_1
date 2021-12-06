DEF_CMD(push, 1, 1, {
    StackPush (&stk, code[*ip]);
})

DEF_CMD(add, 2, 0, {
    StackPop (&stk, &x);
    StackPop (&stk, &y);
    StackPush (&stk, x + y);
})

DEF_CMD(sub, 3, 0, {
    StackPop (&stk, &x);
    StackPop (&stk, &y);
    StackPush (&stk, y - x);
})


DEF_CMD(out, 4, 0, {
    StackPop(&stk, &x);
    printf("%d\n", x);
})

DEF_CMD(mul, 5, 0, {
    StackPop(&stk, &x);
    StackPop(&stk, &y);
    StackPush(&stk, x*y);
    printf("%d\n", x*y);
    StackDump(&stk, "CHECK");
})

DEF_CMD(hlt, -1, 0, {
    StackDtor(&stk);
    free(code);
    close(log_file);
})

