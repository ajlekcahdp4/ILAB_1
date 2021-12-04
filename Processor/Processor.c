#include "Processor.h"
#include "Stack.h"
#include "assembler.h"
#include <math.h>
Stack stk = {};

void Processor (FILE* log_file)
{
    FILE* code_file = fopen ("code.bin", "rb");
    long cur_pos = ftell(code_file);
    fseek (code_file, 0L, SEEK_END);
    int int_numb = ftell (code_file);
    fseek (code_file, 0L, cur_pos);

    int* code = calloc (int_numb, sizeof(int));
    int_numb = fread (code, sizeof(int), int_numb, code_file);
    code = (int*)realloc (code, int_numb);

    StackCtor (&stk, 10);
    for (int i = 0; i < int_numb; i++)
    {
        RunCode(code, &i, log_file);
    }
}

void RunCode (int* code, int* caret, FILE* log_file)
{
    int x = 0;
    int y = 0;
    switch (code[*caret])
    {
    case PUSH:
        *caret += 1;
        StackPush (&stk, code[(*caret)]);
        break;
    case OUT:
        StackPop (&stk, &x);
        printf ("%d\n", x);
        break;
    case MUL:
        StackPop (&stk, &x);
        StackPop (&stk, &y);
        StackPush (&stk, x * y);
        break;
    case SUB:
        StackPop (&stk, &x);
        StackPop (&stk, &y);
        StackPush (&stk, y - x);
        break;
    case SQRT:
        StackPop (&stk, &x);
        StackPush (&stk, sqrt(x));
        break;
    case IN:
        scanf ("%d", &x);
        StackPush (&stk, x);
        break;
    case HLT:
        StackDtor (&stk);
        free (code);
        fclose (log_file);
        break;
    case ADD:
        StackPop (&stk, &x);
        StackPop (&stk, &y);
        StackPush (&stk, x + y);
        break;
    case DIV:
        StackPop (&stk, &x);
        StackPop (&stk, &y);
        if (x == 0)
            fprintf (log_file, "ERROR: ");
        else
            StackPush (&stk, y / x);
        break;
    default:;
    }
}
