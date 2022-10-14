#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CExport.h"
#include "LexicalAnalyzer.h"


int main()
{
    FILE *fp;
    char ch;

   fp = fopen("ArquivoEntrada.txt", "r");
   if (NULL == fp) {
        printf("File can't be opened \n");
    }
 
    printf("Content of this file are \n");

    do {
        ch = fgetc(fp);
        printf("%c", ch);
 
        // Verifica se o caracter não é EOF;
        // Se for ele para a leitura.
    } while (ch != EOF);
 
    // Fecha o arquivo
    fclose(fp);
    return 0;
}

