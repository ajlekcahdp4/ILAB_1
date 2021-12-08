DEF_CMD(push, 1, 1, {
    StackPush (&stk, code[*ip+1]);
    *ip += 1;
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
})

DEF_CMD(DIV, 6, 0, {
    StackPop(&stk, &x);
    StackPop(&stk, &y);
    if (x != 0)
        StackPush(&stk, y/x);
    else
        fprintf(log_file, "ERROR: devide by zero\n");
})

DEF_CMD (in, 7, 0, {
    scanf ("%d", &x);
    StackPush (&stk, x);
})

DEF_CMD(hlt, -1, 0, {
    StackDtor(&stk);
    free(code);
    fclose(log_file);
})
