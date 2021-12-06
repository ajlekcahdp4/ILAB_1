#include "assembler.h"
#define DEF_CMD(name, num, args, ...)                                           \
    if (StrnCompare(comand_line, #name, strlen(#name)- 1) == 0)                 \
    {                                                                           \
            code[*ip] = num;                                                    \
            *ip += 1;                                                           \
            if (args)                                                           \
            {                                                                   \
                code[*ip] = FindArg(comand_line + strlen(#name), log_file);     \
                *ip += 1;                                                       \
            }                                                                   \
    }                                                                           \
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

void CodeGenerate (char * buffer, int ch_numb, FILE* log_file)
{
    assert (buffer);
    FILE * code_file = fopen ("code.bin", "wb");
    int cmd = 0;
    int ip = 0;
    int* code = (int*) calloc (ch_numb, sizeof(int));
    assert (code);

    CmdCode (code, &ip, buffer, log_file);
    //printf("\n%5s\n", buffer);
    for (int  i = 0; i < ch_numb; i++)
    {
        if (buffer[i] == '\n' || buffer[i] == EOF)
        {
            //printf("\n%5s\n", buffer+i+1);
            CmdCode (code, &ip, buffer + i + 1, log_file);
        }
    }

    //printf ("ip = %d\n", ip);

    //for (int i = 0; i < ip; i ++)
      //  printf("<%d>\n", code[i]);


    fwrite (code, sizeof(int), ip, code_file);
    free(code);
    fclose(code_file);
}





int FindArg (char * comand_line, FILE* log_file)
{
    int ARG = 0;
    int i = 0;
    int len = strlen (comand_line);
    while ((comand_line[i] == ' ' || comand_line[i] == '\t') && comand_line[i] != '\n')
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
            fprintf(log_file, "ERROR: Found argument (%c)\n", comand_line[i]);
        }
        i++;
    }
    return ARG;
}


void CmdCode (int * code, int*ip, char * comand_line, FILE* log_file)
{
    assert(code);
    assert(comand_line);
    assert (log_file);
    int ARG = 0;
    #include "commands.h"
    fprintf(log_file, "ERROR: NFC in line.\n");
}
#undef DEF_CMD
