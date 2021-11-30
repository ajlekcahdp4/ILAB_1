#ifndef ASSEMBLER_INCLUDED
#define ASSEMBLER_INCLUDED

#include <stdio.h>
#include <assert.h>
#include <math.h>
#define $meow printf("meow from %s (%d) from %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
enum CMDS
{
    HLT = -1,
    SINTAXIS_EROR = 0,
    PUSH = 1,
    MUL = 2,
    SUB = 4,
    OUT,
    ADD,
    DIV,
    SQRT,
    IN
};


void CodeGenerate (char* buffer, int ch_numb);
int StrnCompare(const char *str1, const char *str2, int n);
int FindArg (char * comand_line);
void CmdCode (int * code, int*caret, int cmd, char * comand_line);
int CmdNumber (char * comand_line);
#endif
