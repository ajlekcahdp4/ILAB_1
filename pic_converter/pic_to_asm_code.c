#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
int main (int argc, char ** argv)
{
    FILE * pic_file = fopen (argv[argc - 1], "r");
    FILE * asm_file = fopen ("pic_code.txt", "w");

    struct stat buf;
    stat(argv[argc - 1], &buf);
    int pixels_numb = buf.st_size;

    char * pic = (char*)calloc (pixels_numb + 1, sizeof(char));
    fread (pic, sizeof(char), pixels_numb, pic_file);

    int ip = 256;
    for (int i = 0; i < pixels_numb; i++)
    {
        while (pic[i] == '\r')
            i++;
        if (pic[i] == '\n')
        {
            fprintf(asm_file, "push 10\npop [%d]\n", ip);
            ip++;
        }
        if (pic[i] == '.')
        {
            fprintf(asm_file, "push 0\npop [%d]\n", ip);
            ip++;
        }
        else if (pic[i] == '#')
        {
            fprintf(asm_file, "push 1\npop [%d]\n", ip);
            ip++;
        }
    }
    fprintf(asm_file, "draw\nhlt");

    free (pic);
    fclose (pic_file);
    fclose (asm_file);
    return 0;
}
