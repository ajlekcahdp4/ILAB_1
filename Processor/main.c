#include <string.h>
#include "Reading.h"
#include "assembler.h"
#include "Processor.h"
#include "Stack.h"

FILE* log_file = 0;

int main()
{
    char * buffer = 0;
    int ch_numb = FillBuffer (&buffer, log_file);
    CodeGenerate (buffer, ch_numb, log_file);//Сассемблировали, записали в файл и закрыли его
    Processor(log_file);
    return 0;
}

