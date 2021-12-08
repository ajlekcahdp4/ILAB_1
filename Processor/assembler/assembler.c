#include "assembler.h"


#define DEF_CMD(name, num, args, ...)                                                       \
                                                                                            \
                                                                                            \
    if (StrnCompare(comand_line, #name, strlen(#name)- 1) == 0)                             \
    {                                                                                       \
            code[*ip] = num;                                                                \
            *ip += 1;                                                                       \
            if (args)                                                                       \
            {                                                                               \
                code[*ip] = FindArg(comand_line + strlen(#name), log_file);                 \
                *ip += 1;                                                                   \
            }                                                                               \
                                                                                            \
    }                                                                                       \
    else


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
    int* code = (int*) calloc (ch_numb, sizeof(int));
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

    fwrite (code, sizeof(int), ip, code_file);
    free(code);
    fclose(code_file);
}





int FindArg (char * comand_line, FILE* log_file)
{
    int ARG = 0;
    int i = 0;
    while ((comand_line[i] == ' ' || comand_line[i] == '\t') && comand_line[i] != '\n')
            i++;
    if (comand_line[i] == '\n')
        fprintf (log_file, "ERROR: No arguments detected\n");
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


void CmdCode (int * code, int*ip, char * comand_line, FILE* log_file)
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

