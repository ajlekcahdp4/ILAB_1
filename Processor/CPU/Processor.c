#include "Processor.h"
#include "Stack.h"
#include <sys/stat.h>


#define DEF_CMD(name, num, args, ...)       \
case num: {                                 \
    __VA_ARGS__;                            \
    break;                                  \
    }                                       \


void Processor (FILE* log_file)
{

    struct ProcData Data = {};
    Data.reg = (int *)calloc(5, sizeof(int));
    Data.stk = (Stack*)calloc(1, sizeof(Stack));

    StackCtor (Data.stk, 10);

    Stack * Rets = (Stack*) calloc (1, sizeof (Stack));
    StackCtor(Rets, 1);


    FILE* code_file = fopen ("code.bin", "rb");


    struct stat buf;
    stat("code.bin", &buf);
    int int_numb = buf.st_size;


    char* code = (char*)calloc (int_numb, sizeof(char));
    int_numb = fread (code, sizeof(char), int_numb, code_file);
    fclose (code_file);
    for (int ip = 0; code[ip] != -1; ip++)
    {
        RunCode(code, &ip, log_file, Rets, &Data);
    }
}

void RunCode (char* code, int* ip, FILE* log_file, Stack* Rets, struct ProcData * Data)
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

