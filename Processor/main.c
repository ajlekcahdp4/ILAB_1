#include "includes.h"
#include "assembler.h"
#include "Processor.h"


int main(int argc, char** argv)
{
    char * buffer = 0;
    FILE* log_file = 0;
    int ch_numb = FillBuffer (argv[argc - 1], &buffer, &log_file);
    Assembler (buffer, ch_numb, log_file);
    Processor(log_file);
    return 0;
