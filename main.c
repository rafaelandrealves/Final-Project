#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "textual.h"
#include "grafica.h"

int main (int argc, char * argv[])
{
    char ficheiro1[MAX_SIZE];
    char ficheiro2[MAX_SIZE];
    int modo = obterParametros(argc,argv,ficheiro1,ficheiro2);

    if(modo == 0) TEXTUAL(ficheiro1, ficheiro2);
    else if (modo == 1) GRAFICO(ficheiro2);

    return EXIT_SUCCESS;
}








