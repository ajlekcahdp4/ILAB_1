DEF_CMD(push, 1, 1, {
    if (code[*ip + 1] == 0)
    {
        StackPush (Data->stk, code[*ip+2]);
        *ip += 5;
    }
    else
    {
        StackPush (Data->stk, Data->reg[(int)(code[*ip + 2])]);
        *ip += 2;
    }
})

DEF_CMD(add, 2, 0, {
    StackPop (Data->stk, &x);
    StackPop (Data->stk, &y);
    StackPush (Data->stk, x + y);
})

DEF_CMD(sub, 3, 0, {
    StackPop (Data->stk, &x);
    StackPop (Data->stk, &y);
    StackPush (Data->stk, y - x);
})


DEF_CMD(out, 4, 0, {
    StackPop(Data->stk, &x);
    printf("%d\n", x);
})

DEF_CMD(mul, 5, 0, {
    StackPop(Data->stk, &x);
    StackPop(Data->stk, &y);
    StackPush(Data->stk, x*y);
})

DEF_CMD(DIV, 6, 0, {
    StackPop(Data->stk, &x);
    StackPop(Data->stk, &y);
    if (x != 0)
        StackPush(Data->stk, y/x);
    else
        fprintf(log_file, "ERROR: devision by zero\n");
})

DEF_CMD (in, 7, 0, {
    scanf ("%d", &x);
    StackPush (Data->stk, x);
})

DEF_CMD (pop, 8, 1, {
    StackPop(Data->stk, &x);
    Data->reg[(int)(code[*ip + 2])] = x;
    *ip += 2;
})

DEF_CMD(hlt, -1, 0, {
    StackDtor(Data->stk);
    free(code);
    fclose(log_file);
})

DEF_CMD (jmp, 9, 1,{
    *ip = code[*ip + 1] - 1;
})

DEF_CMD (jne, 10, 1,{
    StackPop(Data->stk, &x);
    StackPop(Data->stk, &y);
    if (y != x)
        *ip = code[*ip + 1] - 1;
})

DEF_CMD (je, 11, 1,{
    StackPop(Data->stk, &x);
    StackPop(Data->stk, &y);
    if (y == x)
    {
        *ip = code[*ip + 1] - 1;
    }
    else
        *ip += 1;

})

DEF_CMD (ja, 12, 1,{
    StackPop(Data->stk, &x);
    StackPop(Data->stk, &y);
    if (x > y)
    {
        *ip = code[*ip + 1] - 1;
    }
    else
        *ip += 1;

})

DEF_CMD (jae, 13, 1,{
    StackPop(Data->stk, &x);
    StackPop(Data->stk, &y);
    if (x >= y)
    {
        *ip = code[*ip + 1] - 1;
    }
    else
        *ip += 1;

})

DEF_CMD (jb, 14, 1,{
    StackPop(Data->stk, &x);
    StackPop(Data->stk, &y);
    if (x < y)
    {
        *ip = code[*ip + 1] - 1;
    }
    else
        *ip += 1;

})

DEF_CMD (jbe, 15, 1,{
    StackPop(Data->stk, &x);
    StackPop(Data->stk, &y);
    if (x <= y)
    {
        *ip = code[*ip + 1] - 1;
    }
    else
        *ip += 1;

})

