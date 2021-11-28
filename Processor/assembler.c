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
int StrCompare(const char *str1, const char *str2)
{
    int i = 0;
    while (1)
    {
        if (str1[i] != str2[i])
            break;
        if (str2[i] == '\0')
            break;
        i++;
    }
    return (str1[i] - str2[i]);
}

int * CodeGenerate (char ** Index, int s_numb)
{
    assert (Index);
    FILE * code_file = fopen ("code.bin", "wb");
    int cmd = 0;
    int caret = 0;
    int* code = (int*) calloc (s_numb, sizeof(int));
    assert (code);
    for (int  i = 0; i < s_numb; i++)
    {
        cmd = CmdNumber (*(Index + i));
        CmdCode (code, &caret, cmd, *(Index + i));
    }

    ///*
    for (int i = 0; i < caret; i ++)
        printf("%d\n", code[i]);
    //*/

    fwrite (code, sizeof(int), caret, code_file);
    return code;
}





int FindArg (char * comand_line)
{
    int ARG = 0;
    int len = strlen (comand_line);
    for (int i = 0; i < len; i++)
    {
        while (comand_line[i] == ' ' || comand_line[i] == '\t')
            i++;

        int digit = comand_line[i] - '0';
        if (digit < 10 && digit >= 0)
        {
            ARG = ARG*10 + digit;
        }
        else
        {
            printf("SINTAXIS_EROR\n");
            printf ("str = %s\n", comand_line);
        }
    }
    return ARG;
}




void CmdCode (int * code, int*caret, int cmd, char * comand_line)
{
    assert(code);
    assert(comand_line);
    int ARG = 0;
    switch (cmd)
    {
    case PUSH:
        ARG = FindArg(comand_line + strlen ("push"));
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
        printf("PIZDA %d\n", cmd);
        printf ("str = %s\n", comand_line);
        break;
    }
}

int CmdNumber (char * comand_line)
{
    if (StrnCompare (comand_line, "push", strlen("push") - 1) == 0)
        return PUSH;
    else if (StrCompare (comand_line, "mul") == 0)
        return MUL;
    else if (StrCompare (comand_line, "sub") == 0)
        return SUB;
    else if (StrCompare (comand_line, "out") == 0)
        return OUT;
    else if (StrCompare (comand_line, "add") == 0)
        return ADD;
    else if (StrCompare (comand_line, "div") == 0)
        return DIV;
    else if (StrCompare (comand_line, "sqrt") == 0)
        return SQRT;
    else if (StrCompare (comand_line, "hlt") == 0)
        return HLT;
    else if (StrCompare (comand_line, "in") == 0)
        return IN;
    return SINTAXIS_EROR;
}
