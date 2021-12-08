#include "Processor.h"
#include "Stack.h"
#include <sys/stat.h>

Stack stk = {};//структура со стеком и регистрами

#define DEF_CMD(name, num, args, ...)       \
case num: {                                 \
    __VA_ARGS__;                            \
    break;                                  \
    }                                       \


void Processor (FILE* log_file)
{
    FILE* code_file = fopen ("code.bin", "rb");


    struct stat buf;
    stat("code.bin", &buf);
    int int_numb = buf.st_size;


    int* code = calloc (int_numb, sizeof(char));
    int_numb = fread (code, sizeof(int), int_numb, code_file);

    code = (int*)realloc (code, int_numb * sizeof (int));

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
#undef DEF_CMD
