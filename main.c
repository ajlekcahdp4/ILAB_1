
#include "Reading.h"
#include "assembler.h"
int main()
{
    char * Buf = 0;
    int ch_numb = FillBuffer (&Buf);
    int s_numb = StrNumber(Buf, ch_numb);
    char** Index = (char**)calloc (s_numb, sizeof (char*));
    FillIndex (Index, s_numb, ch_numb, Buf);
    int * CODE = CodeGenerate (Index, s_numb);
    return 0;
}
