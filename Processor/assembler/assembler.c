#include "assembler.h"


#define DEF_CMD(name, num, args, ...)                                                                       \
                                                                                                            \
                                                                                                            \
    if (StrnCompare(comand_line, #name, strlen(#name)- 1) == 0)                                             \
    {                                                                                                       \
            code[*ip] = num;                                                                                \
            *ip += 1;                                                                                       \
            if (args)                                                                                       \
            {                                                                                               \
                int i = strlen(#name);                                                                      \
                                                                                                            \
                                                                                                            \
                while ((comand_line[i] == ' ' || comand_line[i] == '\t') && comand_line[i] != '\n')         \
                    i++;                                                                                    \
                if (comand_line[i] == '\n')                                                                 \
                    fprintf(log_file, "ERROR: "#name"must have an argument\n");                             \
                else                                                                                        \
                {                                                                                           \
                    if (comand_line[i] <= '9' && comand_line[i] >= '0')                                     \
                    {                                                                                       \
                        code[*ip] = 0;                                                                      \
                        *ip += 1;                                                                           \
                        *((int*)(code + *ip)) = FindArg (comand_line + i, log_file);                        \
                        *ip += 4;                                                                           \
                    }                                                                                       \
                    else if (comand_line[i] == 'r')                                                         \
                    {                                                                                       \
                        code[*ip] = 1;                                                                      \
                        *ip += 1;                                                                           \
                        char reg = FindReg (comand_line + i, log_file);                                     \
                        code[*ip] = reg;                                                                    \
                        *ip += 1;                                                                           \
                    }                                                                                       \
                }                                                                                           \
            }                                                                                               \
                                                                                                            \
    }                                                                                                       \
    else


    //Заменить второй FindArg на FindReg
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

void Assembler (char * buffer, int ch_numb, FILE* log_file)
{
    assert (buffer);
    FILE * code_file = fopen ("code.bin", "wb");
    int ip = 0;
    int j  = 0;
    int i = 0;
    char* code = (char*) calloc (6*ch_numb, sizeof(char));
    assert (code);

    while ((buffer[i + j] == ' ' || buffer[i + j] == '\t') && (buffer[i + j] != '\n'))
                j++;



    if (buffer[i + j] == '\n')
        fprintf (log_file, "ERROR: NFC in line\n");
    else if (j == 0)
        CmdCode (code, &ip, buffer, log_file);
        else
            CmdCode (code, &ip, buffer + i + j, log_file);

    for (i = 0; i < ch_numb; i++)
    {
        if (buffer[i] == '\n' || buffer[i] == EOF)
        {
            j = 0;
            while ((buffer[i + j + 1] == ' ' || buffer[i + j + 1] == '\t') && (buffer[i + j + 1] != '\n'))
                j++;
            if (buffer[i + j + 1] == '\n')
                    fprintf (log_file, "ERROR: NFC in line\n");
            else
                CmdCode (code, &ip, buffer + i + j + 1, log_file);
        }
    }

    fwrite (code, sizeof(char), ip, code_file);
    free(code);
    fclose(code_file);
}





int FindArg (char * comand_line, FILE* log_file)
{
    int ARG = 0;
    int i = 0;
    SkipSpaces (comand_line, &i, log_file);

    while (comand_line[i] != '\n')
    {
        int digit = comand_line[i] - '0';
        if (digit < 10 && digit >= 0)
        {
            ARG = ARG*10 + digit;
        }
        else
        {
            fprintf(log_file, "ERROR: wrong argument (%c)\n", comand_line[i]);
        }
        i++;
    }

    return ARG;
}



#define DEF_REG(namer, numr)                                            \
    if (StrnCompare(comand_line + i, #namer, 2) == 0)                   \
        REG = numr;                                                     \
                                                                        \
    else


int FindReg (char * comand_line, FILE * log_file)
{
    int REG = 0;
    int i = 0;
    SkipSpaces (comand_line, &i, log_file);

    #include "registers.h"

    {
        fprintf (log_file, "ERROR: Wrong register\n");
    }
    return REG;
}

#undef DEF_REG


void SkipSpaces (char* comand_line, int *i, FILE * log_file)
{
    while ((comand_line[*i] == ' ' || comand_line[*i] == '\t') && comand_line[*i] != '\n')
            *i += 1;
    if (comand_line[*i] == '\n')
        fprintf (log_file, "ERROR: No arguments detected\n");
}
void CmdCode (char * code, int*ip, char * comand_line, FILE* log_file)
{
    assert (code);
    assert (comand_line);
    assert (log_file);
    int p = 0;
    #include "commands.h"
    {
        fprintf( log_file, "ERROR: NFC in line.\n");
        fprintf (log_file, "line: <");
        while (comand_line[p] != '\n')
        {
            fputc (comand_line[p], log_file);
            p++;
        }
        fprintf (log_file, ">\n");
    }

}
#undef DEF_CMD
