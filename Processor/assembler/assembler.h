#ifndef ASSEMBLER_INCLUDED
#define ASSEMBLER_INCLUDED

#include <stdio.h>
#include <assert.h>
#include <math.h>
#define $meow printf("meow from %s (%d) from %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
enum CMDS
{
    hlt = -1,
    sintaxis_error = 0,
    push = 1,
    add = 2,
    sub = 3,
    mul = 4,
    out = 5,
    divv,
    in
};


void CodeGenerate (char* buffer, int ch_numb, FILE* log_file);
int StrnCompare(const char *str1, const char *str2, int n);
int FindArg (char * comand_line, FILE* log_file);
void CmdCode (int * code, int*ip, char * comand_line, FILE* log_file);
int CmdNumber (char * comand_line);
#endif
