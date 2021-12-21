#ifndef PROCESSOR_INCLUDED
#define PROCESSOR_INCLUDED

#include "Stack.h"
#include "includes.h"


struct ProcData
{
    Stack * stk;
    int * reg;
};



void Processor (FILE* log_file);
void RunCode (char* code, int* ip, FILE* log_file, Stack* Rets, struct ProcData * Data);

#endif // PROCESSOR_INCLUDED
