#include "Reading.h"
int FillBuffer (char ** buffer)
{
    FILE * reading_file = fopen ("reading_file.txt", "r");
    long cur_pos = ftell (reading_file);
    fseek (reading_file, 0L, SEEK_END);
    int ch_numb = ftell (reading_file);
    fseek (reading_file, cur_pos, SEEK_SET);
    *buffer = (char*)calloc (ch_numb, sizeof (char));
    ch_numb = fread (*buffer, sizeof (char), ch_numb, reading_file) + 1;
    *buffer = realloc (*buffer, ch_numb);
    int i = 0;
    /*
    for (int j = 0; j < ch_numb; j++)
        printf ("%c\n", (*buffer)[j]);
    */
    while (i < ch_numb)
    {
        if ((*buffer)[i] == '\n')
        {
            (*buffer)[i] = '\0';
        }
        i++;
    }



    return ch_numb;
}

void FillIndex (char **INDEX,int s_numb, int ch_numb, char * Buffer)
{
    assert (ch_numb != 0);
    assert (Buffer != 0);
    assert (INDEX);
    INDEX[0] = Buffer;
    int i, j = 1;
    for (i = 1; i < ch_numb && j < s_numb; i++)
    {
        if (Buffer[i] == '\0')
        {
            INDEX[j] = Buffer + i + 1;
            j++;
        }
    }
}
int StrNumber (char * Buffer, int ch_numb)
{
    int s_numb = 0;
    int i = 0;
    while (i < ch_numb)
    {
        if (Buffer[i] == '\0')
        {
            s_numb++;
        }
        i++;
    }
    return s_numb;
}

void WriteIntoFile (char * buffer, int ch_numb)
{
    FILE * code = fopen ("code.txt", "w");
    fprintf (code, "%s\n", buffer);
    int i = 0;
    while (i < ch_numb)
    {
        if (buffer[i] == '\0')
            fprintf (code, "%s\n", buffer + i + 1);
        i++;
    }
}
