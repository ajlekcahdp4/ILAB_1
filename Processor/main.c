#include "includes.h"
#include "Reading.h"
#include "assembler.h"
#include "Processor.h"
#include "Stack.h"


int main()
{
    char * buffer = 0;
    FILE* log_file = 0;
    int ch_numb = FillBuffer (&buffer, &log_file);
    Assembler (buffer, ch_numb, log_file);
    Processor(log_file);
    return 0;
}

