#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int StrCompare(const char *str1, const char *str2);
void StringsSort(char * Index[], int size);
void PrintIntoFile (char * Index[], int str_num, FILE * fileptr);
int StrNumber (char * Buffer, int ch_numb);
void FillIndex (char * Index[], int ch_numb, char * Buffer);

int main(void)
{
    FILE * fp = fopen("strings.txt", "r");


    long curr_pos = fseek (fp, 0L, SEEK_CUR);
    fseek(fp, 0L, SEEK_END);
    long ftellL = ftell(fp);
    fseek (fp, 0L, curr_pos);


    char * text = calloc (ftellL, sizeof(char));
    int freadL = fread(text, sizeof(char), ftellL, fp);

    //=====================================================================================
    int s_numb = StrNumber(text, freadL);

    char * Index[s_numb];

    int j = 1;
    for (int i = 1; i < freadL; i++)
        if (text[i] == '\0')
        {
            Index[j++] = &text[i+1];
        }

    //FillIndex(Index, freadL, text);

    for (int i = 0; i < s_numb; i++)
        printf("%s\n", Index[i]);
        printf("\n");
    //=====================================================================================
    StringsSort(Index, s_numb);
    //=====================================================================================

    for (int i = 0; i < s_numb; i++)
        printf("%s\n", Index[i]);


    FILE * fp2 = fopen("output.txt", "w");
    fseek(fp2, 0L, SEEK_SET);
    PrintIntoFile (Index, s_numb, fp2);
    return 0;
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
    int j = 0;
    for (int i = 0; i < ch_numb; i++)
    {
        printf("%c ", *(Buffer + i));
        if (*(Buffer + i) == '\0')
            Index[j++] = &Buffer[i + 1];
    }
    printf("\n");
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

