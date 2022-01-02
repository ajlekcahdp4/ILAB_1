#ifndef PROCESSOR_INCLUDED
#define PROCESSOR_INCLUDED

#include "includes.h"
#include "Stack.h"

struct ProcData
{
    Stack * stk;
    int * reg;
};



void Processor (FILE* log_file);
void RunCode (char* code, int* ip, FILE* log_file, Stack* Rets, struct ProcData * Data, int* RAM);

#endif // PROCESSOR_INCLUDED
