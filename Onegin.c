#include "Onegin.h"
int main(void)
{
    setlocale(LC_ALL,"Rus");

    FILE * fp_input = fopen("Onegin2.txt", "r");
    FILE * fp_output1 = fopen("output1.txt", "w");
    FILE * fp_output2 = fopen ("output2.txt", "w");

    int buf_size = GetCharNumb(fp_input);

    char * text = calloc (buf_size, sizeof(char));
    int ch_numb = FillBuffer(text, buf_size, fp_input);

    int s_numb = StrNumber(text, ch_numb);
    struct str_inf *INDEX = calloc (s_numb, sizeof(struct str_inf));
    s_numb = FillIndex(INDEX, s_numb, ch_numb, text);


    StringsSort(INDEX, s_numb);//By first letters
    PrintIntoFile (INDEX, s_numb, fp_output1);

    ReverseSort (INDEX, s_numb);
    PrintIntoFile (INDEX, s_numb, fp_output2);

    Ending(fp_input, fp_output1, fp_output2, INDEX, text);

    return 0;
}
