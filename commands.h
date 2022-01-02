DEF_CMD(push, 1, 1, {
    int arg = 0;
    char cmd = code[*ip];
    *ip += 1;
    if (cmd & (1<<6))
    {
        arg += Data->reg[ *(code + *ip) ];
        *ip += 1;
    }
    if (cmd & (1<<7))
    {
        arg += *((int*)(code + *ip));
        *ip += 4;
    }
    if (cmd & (1<<5))
    {
        arg = RAM[arg];
    }
    StackPush (Data->stk, arg);
})


DEF_CMD (pop, 2, 1, {
    StackPop(Data->stk, &x);
    char* dest = (char*)(&x);
    int index = 0;
    int cmd = code[*ip];
    *ip += 1;
    if (cmd & (1<<5))
    {
        if (cmd & (1<<6))
        {
            index += Data->reg[ *(code + *ip) ];
            *ip += 1;
        }
        if (cmd & (1<<7))
        {
            index += *((int*)(code + *ip));
            *ip += 4;
        }
        dest = (char*)RAM;
    }
    else if (cmd & (1<<6))
    {
        dest = (char*)(Data->reg + *(code + *ip));
        *ip += 1;
    }
    *((int*)(dest) + index) = x;
})

DEF_CMD (jmp, 3, 1,{
    *ip = *((int*)(code + *ip + 1));
})

#define DEF_JUMP(name, num, cond)                               \
                                                                \
DEF_CMD (name, num, 1, {                                        \
    StackPop(Data->stk, &x);                                    \
    StackPop(Data->stk, &y);                                    \
    if (y cond x)                                               \
        *ip = *((int*)(code + *ip + 1));                    \
    else                                                        \
        *ip += 5;                                               \
})

#include "jumps.h"

#undef DEF_JUMP

DEF_CMD (call, 10, 1, {
    StackPush (Rets, *ip + 4);
    *ip = *((int*)(code + *ip + 1));
})

DEF_CMD (ret, 11, 0, {
    StackPop (Rets, &x);
    *ip = x + 1;
})

DEF_CMD(add, 12, 0, {
    StackPop (Data->stk, &x);
    StackPop (Data->stk, &y);
    StackPush (Data->stk, x + y);
    *ip += 1;
})

DEF_CMD(sub, 13, 0, {
    StackPop (Data->stk, &x);
    StackPop (Data->stk, &y);
    StackPush (Data->stk, y - x);
    *ip += 1;
})


DEF_CMD(out, 14, 0, {
    StackPop(Data->stk, &x);
    printf("%d\n", x);
    *ip += 1;
})

DEF_CMD(mul, 15, 0, {
    StackPop(Data->stk, &x);
    StackPop(Data->stk, &y);
    StackPush(Data->stk, x*y);
    *ip += 1;
})

DEF_CMD(DIV, 16, 0, {
    StackPop(Data->stk, &x);
    StackPop(Data->stk, &y);
    if (x != 0)
        StackPush(Data->stk, y/x);
    else
        fprintf(log_file, "ERROR: devision by zero\n");
    *ip += 1;
})

DEF_CMD (in, 17, 0, {
    scanf ("%d", &x);
    StackPush (Data->stk, x);
    *ip += 1;
})



DEF_CMD(hlt, -1, 0, {
    StackDtor(Data->stk);
    free(Data->reg);
    free(code); 
    StackDtor(Rets);
    fclose(log_file);
})


DEF_CMD (dump, 18, 0,{
    StackDump(Data->stk, "(Check)");
    *ip += 1;
})



