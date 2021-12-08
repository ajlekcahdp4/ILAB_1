#ifndef ASSEMBLER_INCLUDED
#define ASSEMBLER_INCLUDED

#include "includes.h"


void Assembler (char* buffer, int ch_numb, FILE* log_file);
int StrnCompare(const char *str1, const char *str2, int n);
int FindArg (char * comand_line, FILE* log_file);
void CmdCode (int * code, int*ip, char * comand_line, FILE* log_file);
int CmdNumber (char * comand_line);
#endif
