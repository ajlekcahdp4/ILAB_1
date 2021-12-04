#ifndef PROCESSOR_INCLUDED
#define PROCESSOR_INCLUDED
#include "Stack.h"
#define $meow printf("meow from %s (%d) from %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);

void Processor (FILE* log_file);
void RunCode (int* code, int* caret, FILE* log_file);

#endif // PROCESSOR_INCLUDED
