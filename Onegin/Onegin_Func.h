#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>

struct str_inf
{
    const char * sptr;
    const char * endstr;
};

int GetCharNumb(FILE * fp)
{
    long curr_pos = fseek (fp, 0L, SEEK_CUR);
    fseek(fp, 0L, SEEK_END);
    long buf_size = ftell(fp);
    fseek (fp, 0L, curr_pos);
    return buf_size;
}

int FillBuffer (char * Buffer, int buf_size, FILE * fp)
{
    Buffer[0] = '\0';
    int ch_numb = fread(Buffer + 1, sizeof(char), buf_size, fp);
    Buffer[buf_size-1] = '\0';
    return ch_numb;
}

int StrNumber (char * Buffer, int ch_numb)
{
    int s_numb = 1;
    int i = 0;
    while (i < ch_numb)
    {
        if (Buffer[i] == '\n' || Buffer[i] == -1)
        {
            s_numb++;
            Buffer[i] = '\0';
        }
        i++;
    }
    return s_numb;
}

int FillIndex (struct str_inf INDEX[],int s_numb, int ch_numb, char * Buffer)
{
    assert (ch_numb != 0);
    assert (Buffer != 0);
    INDEX[0].sptr = Buffer + 1;
    int i, j = 1;
    int slen = 0, SNUMB = 0;;
    for (i = 1; i < ch_numb; i++)
    {
        slen++;
        if (Buffer[i] == '\0' && slen == 1)
        {
            i++;
            slen = 0;
        }
        if (Buffer[i] == '\0' && slen > 1)
        {
            assert (Buffer + i - 1 != 0);
            INDEX[j - 1].endstr = Buffer + i - 1;
            INDEX[j].sptr = Buffer + i + 1;
            j++;
            SNUMB++;
            slen = 0;
        }
    }
    INDEX[j - 1].endstr = Buffer + i;
    return SNUMB;
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

int ReverseCompare(const char * str1, const char * str2)
{
    assert(str1 != 0);
    assert(str2 != 0);
    int i = 0;
    //printf("str1 = %p, str2 = %p\n", str1, str2);
    for(;;)
    {
        assert (str1 - i != 0);
        assert (str2 - i != 0);
        //printf("str1[] = %c, str2[] = %c\n", *(str1 - i), *(str2 - i));
        if (*(str1 - i) != *(str2 - i))
            break;
        if (*(str1 - i) == '\0')
            break;
        i++;
    }
    //printf("return %d\n", *(str1 - i) - *(str2 - i));
    return (*(str1 - i) - *(str2 - i));
}


void StringsSort(struct str_inf INDEX[], int size)
{
    for (int nPass = 0; nPass < size - 1; nPass++)
        for(int i = 0; i < size - 1; i++)
        {
            assert (INDEX[i].sptr != 0);
            assert (INDEX[i + 1].sptr != 0);
            if (StrCompare(INDEX[i].sptr, INDEX[i + 1].sptr) > 0)
            {
                struct str_inf temp = INDEX[i];
                INDEX[i] = INDEX[i + 1];
                INDEX[i + 1] = temp;
            }
        }
}

void ReverseSort(struct str_inf INDEX[], int size)
{
    for (int nPass = 0; nPass < size - 1; nPass++)
    {
        //printf("\n\n");
        //PrintStrings(INDEX, size);
        for(int i = 0; i < size-1; i++)
        {

            //printf("1   INDEX[%d].endstr = %p, INDEX[%d].endstr = %p\n", i, INDEX[i].endstr, i + 1, INDEX[i+1].endstr);
            assert (INDEX[i].endstr != 0);
            assert (INDEX[i + 1].endstr != 0);
            //printf("c1 = %c, c2 = %c\n", *INDEX[i].endstr, *INDEX[i+1].endstr);
            //printf("str1 = %s  str2 = %s\n", INDEX[i].sptr, INDEX[i+1].sptr);
            //printf("str1 = %s  str2 = %s\n", INDEX[i].endstr - 3, INDEX[i+1].endstr - 3);
            if (ReverseCompare(INDEX[i].endstr, INDEX[i + 1].endstr) > 0)
            {
                //printf("swap\n");
                struct str_inf temp = INDEX[i];
                INDEX[i] = INDEX[i + 1];
                INDEX[i + 1] = temp;
            }
            //printf("2   INDEX[%d].endstr = %p, INDEX[%d].endstr = %p\n", i, INDEX[i].endstr, i + 1, INDEX[i+1].endstr);
        }
    }
}

void PrintIntoFile (struct str_inf INDEX[], int str_num, FILE * fileptr)
{
    for (int i = 0; i < str_num; i ++)
    {
        if(INDEX[i].sptr != 0)
        {
            fputs (INDEX[i].sptr, fileptr);
            fputc('\n', fileptr);
        }
        else
            break;
    }
}

void PrintStrings(struct str_inf INDEX[], int s_numb)
{
    for (int i = 0; i < s_numb; i++)
        printf("%s\n", INDEX[i].sptr);
        printf("\n");
}

void Ending (FILE * fp_input, FILE * fp_output1, FILE * fp_output2, struct str_inf INDEX[], char *text)
{
    free (text);
    free (INDEX);
    fclose (fp_input);
    fclose (fp_output1);
    fclose (fp_output2);
}

void NoVoidStr(struct str_inf INDEX[], int s_numb)
{
    for (int i = 0; i < s_numb - 1; i ++)
    {
        if (fabs(INDEX[i].sptr - INDEX[i+1].sptr) <= 1)
        {
            INDEX[i].sptr = 0;
            break;
        }
    }
}
