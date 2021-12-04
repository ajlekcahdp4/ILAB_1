#include "assembler.h"

int StrnCompare(const char *str1, const char *str2, int n)
{
    int i = 0;
    while (i < n)
    {
        if (str1[i] != str2[i])
            break;
        if (str2[i] == '\0')
            break;
        i++;
    }
    return (str1[i] - str2[i]);
}

void CodeGenerate (char * buffer, int ch_numb, FILE* log_file)
{
    assert (buffer);
    FILE * code_file = fopen ("code.bin", "wb");
    int cmd = 0;
    int caret = 0;
    int* code = (int*) calloc (ch_numb, sizeof(int));
    assert (code);


    cmd = CmdNumber(buffer);
    CmdCode (code, &caret, cmd, buffer, log_file);
    for (int  i = 0; i < ch_numb; i++)
    {
        if (buffer[i] == '\n' || buffer[i] == EOF)
        {
            cmd = CmdNumber(buffer + i + 1);
            CmdCode (code, &caret, cmd, buffer + i + 1, log_file);
        }
    }

    /*
    for (int i = 0; i < caret; i ++)
        printf("%d\n", code[i]);
    */

    fwrite (code, sizeof(int), caret, code_file);
    free(code);
    fclose(code_file);
}





int FindArg (char * comand_line, FILE* log_file)
{
    int ARG = 0;
    int i = 0;
    int len = strlen (comand_line);
    while (comand_line[i] == ' ' || comand_line[i] == '\t')
            i++;
    while (comand_line[i] != '\n')
    {
        int digit = comand_line[i] - '0';
        if (digit < 10 && digit >= 0)
        {
            ARG = ARG*10 + digit;
        }
        else
        {
            fprintf(log_file, "ERROR: Wrong argument\n");
            fprintf(log_file, "ERROR: Found argument (%d)\n", ARG);
        }
        i++;
    }
    return ARG;
}




void CmdCode (int * code, int*caret, int cmd, char * comand_line, FILE* log_file)
{
    assert(code);
    assert(comand_line);
    int ARG = 0;
    switch (cmd)
    {
    case PUSH:
        ARG = FindArg(comand_line + 4, log_file);
        code[*caret] = cmd;
        *caret += 1;
        code[*caret] = ARG;
        *caret += 1;
        break;
    case MUL:
        code[*caret] = cmd;
        *caret += 1;
        break;
    case SUB:
        code[*caret] = cmd;
        *caret += 1;
        break;
    case OUT:
        code[*caret] = cmd;
        *caret += 1;
        break;
    case ADD:
        code[*caret] = cmd;
        *caret += 1;
        break;
    case DIV:
        code[*caret] = cmd;
        *caret += 1;
        break;
    case SQRT:
        code[*caret] = cmd;
        *caret += 1;
        break;
    case IN:
        code[*caret] = cmd;
        *caret += 1;
        break;
    case HLT:
        code[*caret] = cmd;
        *caret += 1;
        break;
    default:
        fprintf(log_file, "\nERROR: Wrong command number (%d)\n", cmd);
        break;
    }
}

int CmdNumber (char * comand_line)
{
    if (StrnCompare (comand_line, "push", 3) == 0)
        return PUSH;
    else if (StrnCompare (comand_line, "mul", 2) == 0)
        return MUL;
    else if (StrnCompare (comand_line, "sub", 2) == 0)
        return SUB;
    else if (StrnCompare (comand_line, "out", 2) == 0)
        return OUT;
    else if (StrnCompare (comand_line, "add", 2) == 0)
        return ADD;
    else if (StrnCompare (comand_line, "div", 2) == 0)
        return DIV;
    else if (StrnCompare (comand_line, "sqrt", 3) == 0)
        return SQRT;
    else if (StrnCompare (comand_line, "hlt", 2) == 0)
        return HLT;
    else if (StrnCompare (comand_line, "in", 1) == 0)
        return IN;
    return SINTAXIS_EROR;
}
