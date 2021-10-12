#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int StrCompare(const char *str1, const char *str2);
void StringsSort(char * Index[], int size);

int main(void)
{
    FILE * fp = fopen("strings.txt", "r");
    long curr_pos = fseek (fp, 0L, SEEK_CUR);
    fseek(fp, 0L, SEEK_END);
    long ftellL = ftell(fp);
    fseek (fp, 0L, curr_pos);
    char text[10000] = "";
    char out[10000];
    int freadL = fread(text, sizeof(char), ftellL, fp);

    //=====================================================================================
    int s_numb = ftellL - freadL + 1;
    char * Index[s_numb];
    Index[0] = text;
    int j = 1;

    for (int i = 1; i < freadL; i++)
        if (text[i] == '\n')
        {
            text[i] = '\0';
            Index[j++] = &text[i+1];
        }
    for (int i = 0; i < s_numb; i++)
        printf("%s\n", Index[i]);
        printf("\n");
    //=====================================================================================
    StringsSort(Index, s_numb);
    //=====================================================================================

    for (int i = 0; i < s_numb; i++)
        printf("%s\n", Index[i]);

//    FILE * fp2 = fopen("output.txt", "w");
    return 0;
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
