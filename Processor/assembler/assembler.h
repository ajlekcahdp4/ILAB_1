#ifndef ASSEMBLER_INCLUDED
#define ASSEMBLER_INCLUDED

#include "includes.h"

struct LABLES {
    int b_numb;
    char * lable_name;
};
typedef struct LABLES LABLES;


int     FillBuffer (char ** buffer, FILE** log_file);
void    Assembler (char* buffer, int ch_numb, FILE* log_file);
int     TranslateToCode (char* buffer, int ch_numb, char* code, LABLES** lables, int *labl_cnt, FILE* log_file);
int     StrnCompare(const char *str1, const char *str2, int n);
int     FindArg (char * comand_line, FILE* log_file);
int     FindReg (char * comand_line, FILE* log_file);
void    SkipSpaces (char* comand_line, int *i, FILE * log_file);
int     IsLable (char* command_line, LABLES** lables, int labl_cnt);
int     IsJump (char* name);
void    CmdCode (char * code, int*ip, char * comand_line, LABLES ** lables, int *labl_cnt, FILE* log_file, int run_numb);
int     CmdNumber (char * comand_line);
#endif
