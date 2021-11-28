#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define $meow printf("meow from %s (%d) from %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
int FillBuffer (char ** buffer);
void WriteIntoFile (char * buffer, int ch_numb);
int StrNumber (char * Buffer, int ch_numb);
void FillIndex (char **INDEX,int s_numb, int ch_numb, char * Buffer);
