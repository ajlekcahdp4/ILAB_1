#include <stdio.h>
#include <assert.h>
#include <math.h>
#define $meow printf("meow from %s (%d) from %s\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
enum CMDS
{
    HLT = -1,
    SINTAXIS_EROR = 0,
    PUSH = 1,
    MUL = 2,
    SUB = 4,
    OUT,
    ADD,
    DIV,
    SQRT,
    IN
};



int * CodeGenerate (char ** Index, int s_numb);

