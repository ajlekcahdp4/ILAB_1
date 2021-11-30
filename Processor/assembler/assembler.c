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

void CodeGenerate (char * buffer, int ch_numb)
{
    assert (buffer);
    FILE * code_file = fopen ("code.bin", "wb");
    int cmd = 0;
    int caret = 0;
    int* code = (int*) calloc (ch_numb, sizeof(int));
    assert (code);


    cmd = CmdNumber(buffer);
    CmdCode (code, &caret, cmd, buffer);
    for (int  i = 0; i < ch_numb; i++)
    {
        if (buffer[i] == '\n' || buffer[i] == EOF)
        {
            cmd = CmdNumber(buffer + i + 1);
            CmdCode (code, &caret, cmd, buffer + i + 1);
        }
    }

    ///*
    for (int i = 0; i < caret; i ++)
        printf("%d\n", code[i]);
    //*/

    fwrite (code, sizeof(int), caret, code_file);
    free(code);
    fclose(code_file);
    return code;
}





int FindArg (char * comand_line)
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
            printf("SINTAXIS_EROR\n");
            printf ("str = <%s>\n", comand_line);
        }
        i++;
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
        ARG = FindArg(comand_line + 4);
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
        printf("\nPIZDA %d\n", cmd);
        printf ("str = %s\n\n", comand_line);
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

