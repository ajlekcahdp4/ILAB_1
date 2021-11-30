#include "Reading.h"
#include "assembler.h"
#include "Processor.h"
int main()
{
    char * buffer = 0;
    int ch_numb = FillBuffer (&buffer);
    CodeGenerate (buffer, ch_numb);//Сассемблировали, записали в файл и закрыли его
    RunCode();
    return 0;
}
