#ifndef PROCESSOR_INCLUDED
#define PROCESSOR_INCLUDED
#include "Stack.h"
#include "includes.h"


struct ProcData
{
    Stack * stk;
    int * reg
};

void Processor (FILE* log_file);
void RunCode (int* code, int* caret, FILE* log_file);

#endif // PROCESSOR_INCLUDED
