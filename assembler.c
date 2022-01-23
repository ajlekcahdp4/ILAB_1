#include "assembler.h"

#define NOT_END (command_line[i] != '\r' && command_line[i] != '\n' && command_line[i] != '\0')

#define K_FLAG ((*(code + *ip - 1)) & (1 << 7))
#define R_FLAG ((*(code + *ip - 1)) & (1 << 6))
#define M_FLAG ((*(code + *ip - 1)) & (1 << 5))



#define DEF_CMD(name, num, args, ...)                                                                                                       \
    if (strncmp(command_line, #name, strlen(#name)) == 0)                                                                                   \
    {                                                                                                                                       \
        code[*ip] = num;                                                                                                                    \
        int cmd = *ip;                                                                                                                      \
        *ip += 1;                                                                                                                           \
        if (args)                                                                                                                           \
        {                                                                                                                                   \
            int i = strlen(#name);                                                                                                          \
            while ((command_line[i] == ' ' || command_line[i] == '\t') && NOT_END )                                                         \
                i++;                                                                                                                        \
            if (command_line[i] == '\n' || command_line[i] == '\r' || command_line[i] == '\0')                                              \
            {                                                                                                                               \
                fprintf(log_file, "ERROR: "#name" must have an argument\n");                                                                \
                ERROR (ERR_NO_ARGUMENT);                                                                                                    \
            }                                                                                                                               \
            else                                                                                                                            \
            {                                                                                                                               \
                if (IsJump(#name))                                                                                                          \
                {                                                                                                                           \
                    *((int*)(code + *ip)) = -1;                                                                                             \
                    for (int lp = 0; lp < *labl_cnt; lp++)                                                                                  \
                    {                                                                                                                       \
                        if (strncmp (command_line + i, ((*lables)[lp]).lable_name, strlen(((*lables)[lp]).lable_name)) == 0)                \
                        {                                                                                                                   \
                            IsEndOfStr (command_line + strlen(((*lables)[lp]).lable_name), &i, log_file);                                   \
                            *((int*)(code + *ip)) = ((*lables)[lp]).b_numb;                                                                 \
                            break;                                                                                                          \
                        }                                                                                                                   \
                    }                                                                                                                       \
                    if (run_numb == 2 && *((int*)(code + *ip)) == -1)                                                                       \
                    {                                                                                                                       \
                        fprintf (log_file, "ERROR: function(or jump) without defenition(or lable)\n");                                      \
                        ERROR (ERR_FUNC_WITHOUT_DEFENITION);                                                                                \
                    }                                                                                                                       \
                    *ip += 4;                                                                                                               \
                }                                                                                                                           \
                else                                                                                                                        \
                {                                                                                                                           \
                    int flag_cnt = 0;                                                                                                       \
                    if (command_line[i] == '[')                                                                                             \
                    {                                                                                                                       \
                        int j = i;                                                                                                          \
                        while (NOT_END)                                                                                                     \
                        {                                                                                                                   \
                            if (command_line[j] == ']')                                                                                     \
                            {                                                                                                               \
                                (*(code + cmd)) = (*(code + cmd)) | (1 << 5);                                                               \
                                flag_cnt++;                                                                                                 \
                                break;                                                                                                      \
                            }                                                                                                               \
                            j++;                                                                                                            \
                        }                                                                                                                   \
                        i++;                                                                                                                \
                        SkipSpaces(command_line, &i, log_file);                                                                             \
                    }                                                                                                                       \
                    if (command_line[i] == 'r' && NOT_END )                                                                                 \
                    {                                                                                                                       \
                        (*(code + cmd)) = (*(code + cmd)) | (1 << 6);                                                                       \
                        flag_cnt++;                                                                                                         \
                        char reg = FindReg (command_line, &i, log_file);                                                                    \
                        if (command_line[i] == ']')                                                                                         \
                            i++;                                                                                                            \
                        code[*ip] = reg;                                                                                                    \
                        *ip += 1;                                                                                                           \
                    }                                                                                                                       \
                    if ((command_line[i] <= '9' && command_line[i] >= '0' || command_line[i] == '-' || command_line[i] == '+') && NOT_END ) \
                    {                                                                                                                       \
                        (*(code + cmd)) = (*(code + cmd)) | (1 << 7);                                                                       \
                        *((int*)(code + *ip)) = FindArg (command_line, &i, log_file);                                                       \
                        if (command_line[i] == ']')                                                                                         \
                            i++;                                                                                                            \
                        flag_cnt++;                                                                                                         \
                        *ip += 4;                                                                                                           \
                    }                                                                                                                       \
                    if (flag_cnt == 0)                                                                                                      \
                    {                                                                                                                       \
                        fprintf (log_file, "ERROR: Wrong argument of cmd "#name"\n");                                                       \
                        ERROR (ERR_WRONG_ARGUMENT);                                                                                         \
                    }                                                                                                                       \
                }                                                                                                                           \
            }                                                                                                                               \
        }                                                                                                                                   \
        else                                                                                                                                \
        {                                                                                                                                   \
            int i = 0;                                                                                                                      \
            IsEndOfStr (command_line + strlen(#name), &i, log_file);                                                                        \
        }                                                                                                                                   \
    }                                                                                                                                       \
    else
//===========================================================================================================================================
//>rename "cmd"
void CmdCode (char * code, int *ip, char * command_line, LABLES ** lables, int *labl_cnt, FILE* log_file, int run_numb)
{
    assert (code);
    assert (command_line);
    assert (log_file);
    assert(command_line);
    assert(ip);
    assert(lables);
    assert(labl_cnt);

    int p = 0;
    #include "commands.h"
    {
        if (run_numb == 1)
        {
            int len = 0;
            while (command_line[len] != ' ' && command_line[len] != '\t' && command_line[len] != '\n'&& command_line[len] != '\r')
                len++;
            if (command_line[len - 1] == ':')
            {
                p = 0;
                if (IsLable(command_line, lables, *labl_cnt))
                {
                    fprintf (log_file, "ERROR: double defenition of lable <%.*s>\n", len, command_line);
                    ERROR(ERR_DOUBLE_DEF_OF_LABLE);
                }
                else
                {
                    *labl_cnt += 1;
                    *lables = realloc ((*lables), (*labl_cnt) * sizeof(LABLES));
                    ((*lables)[*labl_cnt - 1]).lable_name = (char*)calloc(len + 1, sizeof(char));
                    ((*lables)[*labl_cnt - 1]).b_numb = *ip;
                    while (p < len - 1)
                    {
                        ((*lables)[*labl_cnt - 1]).lable_name[p] = command_line[p];
                        p++;
                    }
                    ((*lables)[*labl_cnt - 1]).lable_name[p] = '\0';
                }
                IsEndOfStr(command_line, &len, log_file);
                
            }
            
        }
        else
        {
            if (IsLable (command_line, lables, *labl_cnt) != 1 && command_line[0] != '\0')
            {
                fprintf(log_file, "ERROR: No fucking command or lable in line.\n");
                fprintf (log_file, "line: <");
                while (command_line[p] != '\n')
                {
                    fputc (command_line[p], log_file);
                    p++;
                }
                fclose (log_file);
                fprintf (log_file, ">\n");
                ERROR (ERR_WRONG_ARGUMENT);
            }
        }
    }

}
#undef DEF_CMD


int IsJump (char * name)
{
    if (strcmp (name, "jmp") == 0)
        return 1;
    if (strcmp(name, "ja") == 0)
        return 1;
    if (strcmp(name, "jae") == 0)
        return 1;
    if (strcmp(name, "jb") == 0)
        return 1;
    if (strcmp(name, "jbe") == 0)
        return 1;
    if (strcmp(name, "je") == 0)
        return 1;
    if (strcmp(name, "jne") == 0)
        return 1;
    if (strcmp(name, "call") == 0)
        return 1;
    return 0;
}




int FillBuffer (char* file_name, char ** buffer, FILE** log_file)
{
    *log_file = fopen ("Proc_log_file.txt", "w");
    FILE * reading_file = fopen (file_name, "r");
    long cur_pos = ftell (reading_file);
    fseek (reading_file, 0L, SEEK_END);
    int ch_numb = ftell (reading_file);
    fseek (reading_file, cur_pos, SEEK_SET);
    *buffer = (char*)calloc (ch_numb + 1, sizeof (char));

    if (*buffer == 0)
    {
        fprintf (*log_file, "ERROR: Can not allocate buffer\n");
        assert(!"ERR_CANNOT_ALOCATE_BUFFER");
    }
    ch_numb = fread (*buffer, sizeof (char), ch_numb + 1, reading_file);
    (*buffer)[ch_numb] = '\0';
    *buffer = realloc (*buffer, ch_numb + 1);

    
    fclose(reading_file);
    return ch_numb;
}

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

    int labl_cnt = 0;
    LABLES * lables = (LABLES*) calloc (labl_cnt + 1, sizeof(LABLES));
    assert(lables);

    char* code = (char*) calloc (6*ch_numb, sizeof(char));
    assert (code);
   


    int ip = TranslateToCode (buffer, ch_numb, code, &lables, &labl_cnt, log_file);
    ip = TranslateToCode (buffer, ch_numb, code, &lables, &labl_cnt, log_file);
    LablesCheck(lables, labl_cnt, log_file);


    fwrite (code, sizeof(char), ip, code_file);

    for (int i = 0; i < labl_cnt; i++)
        free((lables[i]).lable_name);

    free(code);
    free(buffer);
    free(lables);   
    fclose(code_file);
}





int FindArg (char * command_line, int *index, FILE* log_file)
{
    int ARG = 0;
    int i = *index;
    int sign = 1;
    SkipSpaces (command_line, &i, log_file);
    if (command_line[i] == '-' && sign == 1)
    {
        sign *= -1;
        i++;
        SkipSpaces (command_line, &i, log_file);
    }
    else if (command_line[i] == '+')
    {
        sign *= 1;
        i++;
        SkipSpaces (command_line, &i, log_file);
    }
    while (command_line[i] != '\t' &&command_line[i] != ' ' && NOT_END )
    {
        int digit = command_line[i] - '0';
       
        if (digit <= 9 && digit >= 0)
        {
            ARG = ARG*10 + digit;
        }
        else if (command_line[i] != ']' && command_line[i] != 'r')
        {
            fprintf(log_file, "ERROR: wrong argument (%c)\n", command_line[i]);
            ERROR (ERR_WRONG_ARGUMENT);
        }    
        i++;
    }
    ARG *= sign;
    *index = i;
    SkipSpaces (command_line, index, log_file);
    return ARG;
}



#define DEF_REG(namer, numr)                                                                \
    if (strncmp(command_line + i, #namer, 3) == 0)                                          \
    {                                                                                       \
        i += strlen(#namer);                                                                \
        REG = numr;                                                                         \
    }                                                                                       \
    else




int FindReg (char * command_line, int *index, FILE * log_file)
{
    int REG = 0;
    int i = *index;

    #include "registers.h"

    {
        fprintf (log_file, "ERROR: Wrong register\n");
        ERROR (ERR_WRONG_ARGUMENT);
    }
    *index = i;
    SkipSpaces (command_line, index, log_file);
    return REG;
}



#undef DEF_REG




int IsEndOfStr (char *command_line, int *i, FILE *log_file)
{
    while ((command_line[*i] == ' ' || command_line[*i] == '\t') && command_line[*i] != '\n' && command_line[*i] != '\r' && command_line[*i] != '\0')
        *i += 1;
    if (command_line[*i] != '\r' && command_line[*i] != '\n' && command_line[*i] != '\0')
    {
        int p = *i;
        fprintf (log_file, "ERROR: wrong end of line\n");
        fprintf (log_file, "line: <");
        while (command_line[p] != '\n')
        {
            fputc (command_line[p], log_file);
            p++;
        }
        fprintf (log_file, ">\n");
        ERROR (ERR_WRONG_END_OF_THE_LINE);
    }
    return 0;
}

int IsLable (char* command_line, LABLES** lables, int labl_cnt)
{
    int res = 0;
    for (int i = 0; i < labl_cnt; i++)
    {
        if (strncmp(command_line, ((*lables)[i]).lable_name, strlen(((*lables)[i]).lable_name)) == 0)
        {
            res = 1;
            break;
        }
    }
    return res;
}


void LablesCheck (LABLES *lables, int labl_cnt, FILE* log_file)
{
    for (int i = 0; i < labl_cnt; i++)
    {
        if ((lables[i]).b_numb == -1)
        {
            fprintf(log_file, "error in lable<%s>\n", lables[i].lable_name);
            fprintf (log_file, "ERROR: function(or jump) without defenition(or lable)\n");
            ERROR (ERR_FUNC_WITHOUT_DEFENITION);
        }
    }
}
void SkipSpaces (char* command_line, int *i, FILE * log_file)
{
    while ((command_line[*i] == ' ' || command_line[*i] == '\t') && command_line[*i] != '\n')
            *i += 1;
}



int  TranslateToCode (char* buffer, int ch_numb, char* code, LABLES** lables, int *labl_cnt, FILE* log_file)
{
    int i = 0;
    int ip = 0;
    static int run_numb = 1;

    while ((buffer[i] == ' ' || buffer[i] == '\t' ||buffer[i] == '\n' || buffer[i] == '\r') && buffer[i] != '\0')
                i++;

    
    CmdCode (code, &ip, buffer + i, lables, labl_cnt, log_file, run_numb);


    for (i = 0; i < ch_numb -1; i++)
    {
        if (buffer[i] == '\n')
        {
            while (buffer[i + 1] == ' ' || buffer[i + 1] == '\t' || buffer[i + 1] == '\n' || buffer[i + 1] == '\r')
                i++;
            CmdCode (code, &ip, buffer + i + 1, lables, labl_cnt, log_file, run_numb);
        }
    }
    run_numb++;


    return ip;
}



#undef NOT_END
#undef K_FLAG
#undef R_FLAG
#undef M_FLAG