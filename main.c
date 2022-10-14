#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CExport.h"
#include "LexicalAnalyzer.h"


int main()
{
    FILE *fp;
    char ch;

   fp = fopen("test/ArquivoEntrada.txt", "r");
   if (NULL == fp) {
        printf("File can't be opened \n");
    }
    
    lexicalConstructor(fp);
    fclose(fp);
    lexicalDestructor();
    return 0;
}

