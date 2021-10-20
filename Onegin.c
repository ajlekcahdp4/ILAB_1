#include <stdio.h>
#include <string.h>
#include <locale.h>


int StrCompare(const char *str1, const char *str2);
void StringsSort(char * Index[], int size);//!Sort strings by first letters
void PrintIntoFile (char * Index[], int str_num, FILE * fileptr);
int StrNumber (char * Buffer, int ch_numb);
void FillIndex (char * Index[], int ch_numb, char * Buffer);
void PrintStrings(char * Index[], int s_numb);
int GetCharNumb(FILE * fp);



int main(void)
{
    setlocale(LC_ALL,"Rus");
    FILE * fp_input = fopen("Onegin.txt", "r");
    int buf_size = GetCharNumb(fp_input);

    char * text = calloc (buf_size, sizeof(char));
    int ch_numb = fread(text, sizeof(char), buf_size, fp_input);

    int s_numb = StrNumber(text, ch_numb);

    char * Index[s_numb];
    FillIndex(Index, ch_numb, text);

    StringsSort(Index, s_numb);//By first letters


    FILE * fp_output = fopen("output.txt", "w");
    fseek(fp_output, 0L, SEEK_SET);
    PrintIntoFile (Index, s_numb, fp_output);
    free(text);
    fclose (fp_input);
    fclose(fp_output);
    return 0;
}

int GetCharNumb(FILE * fp)
{
    long curr_pos = fseek (fp, 0L, SEEK_CUR);
    fseek(fp, 0L, SEEK_END);
    long buf_size = ftell(fp);
    fseek (fp, 0L, curr_pos);
    return buf_size;
}

int StrNumber (char * Buffer, int ch_numb)
{
    int s_numb = 0;
    int i = 0;
    while (i < ch_numb)
    {
        if (Buffer[i] == '\n')
        {
            s_numb++;
            Buffer[i] = '\0';
        }
        i++;
    }
    s_numb++;
    return s_numb;
}

void FillIndex (char * Index[], int ch_numb, char * Buffer)
{
    int j = 1;
    Index[0] = &Buffer[0];
    for (int i = 0; i < ch_numb; i++)
    {
        if (*(Buffer + i) == '\0')
            Index[j++] = &Buffer[i + 1];
    }
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

void StringsSort(char * Index[], int size)
{
    for (int nPass = 0; nPass < size - 1; nPass++)
        for(int i = 0; i < size - 1; i++)
        {
            if (StrCompare(Index[i], Index[i + 1]) > 0)
            {
                char * temp = Index[i];
                Index[i] = Index[i + 1];
                Index[i + 1] = temp;
            }
        }
}

void PrintIntoFile (char * Index[], int str_num, FILE * fileptr)
{
    for (int i = 0; i < str_num; i ++)
    {
        fputs (Index[i], fileptr);
        fputc('\n', fileptr);
    }
}

void PrintStrings(char * Index[], int s_numb)
{
    for (int i = 0; i < s_numb; i++)
        printf("%s\n", Index[i]);
        printf("\n");
}
