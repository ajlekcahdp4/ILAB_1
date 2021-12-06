#include "Processor.h"
#include "Stack.h"
#include "assembler.h"
#include <math.h>
Stack stk = {};

#define DEF_CMD(name, num, args, ...)       \
case num: {                                 \
    __VA_ARGS__;                            \
    }                                       \
    break;


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

void RunCode (int* code, int* ip, FILE* log_file)
{
    int x = 0;
    int y = 0;
    switch (code[*ip])
    {
    #include "commands.h"
    default:;
    }
}
