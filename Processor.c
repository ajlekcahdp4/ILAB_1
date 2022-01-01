#include "Processor.h"
#include <sys/stat.h>


int BitComp (char a, char b, int n)
{
    int i = 0;
    while (i < n)
    {
        if ((a & (1<<i)) != (b & (1<<i)))
            return 0;
        i++;
    }
    return 1;
}

void Processor (FILE* log_file)
{

    struct ProcData Data = {};
    Data.reg = (int *)calloc(5, sizeof(int));
    Data.stk = (Stack*)calloc(1, sizeof(Stack));

    StackCtor (Data.stk, 8, "Data_stk_logfile.txt");

    Stack * Rets = (Stack*) calloc (1, sizeof (Stack));
    StackCtor(Rets, 1, "Rets_logfile.txt");


    FILE* code_file = fopen ("code.bin", "rb");


    struct stat buf;
    stat("code.bin", &buf);
    int int_numb = buf.st_size;


    char* code = (char*)calloc (int_numb, sizeof(char));
    int_numb = fread (code, sizeof(char), int_numb, code_file);
    fclose (code_file);
    int ip = 0;
    for ( ip = 0; code[ip] != -1; ip++)
    {
        RunCode(code, &ip, log_file, Rets, &Data);
    }
    RunCode(code, &ip, log_file, Rets, &Data);
}

#define DEF_CMD(name, num, args, ...)       \
if (BitComp(code[*ip], num, 5))             \
{                                           \
    __VA_ARGS__;                            \
}                                           \
else

void RunCode (char* code, int* ip, FILE* log_file, Stack* Rets, struct ProcData * Data)
{
    int x = 0;
    int y = 0;
    #include "commands.h"
    {;}
}
#undef DEF_CMD
