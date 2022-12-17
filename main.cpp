#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CExport.h"
#include "SymbolTable.h"
#include "LexicalAnalyzer.h"
#include "CExport.h"
#include "RDParser.h"

int main(int argc, char *argv[])
{
    FILE *fileStream = NULL;
    char *filename = argv[1];
    int isFilenameDynamic = 0;

    if (argc > 1)
    {
        // If first parameter doesn't have the dot char
        if (!strchr(argv[1], '.'))
        {
            // Allocs space to the name received + file extension
            int length = strlen(argv[1]);
            filename = (char *)malloc(sizeof(char) * (length + 6));
            isFilenameDynamic = 1; // Indicates the filename needs to be freed
            if (!filename)
            {
                exit(1); // If can't allocate memory, exits
            }
            strcpy(filename, argv[1]); // Copy name received to the begining of the allocated space
            strcat(filename, ".cmm"); // Concats the file extension
        }
        fileStream = fopen(filename, "r");
        if (!fileStream)
        {
            printf("File '%s' can't be opened \n", filename);
            exit(2);
        }
    }
    else
    {
        // If no args are found, uses stdin as the fileStream
        fileStream = stdin;
    }

    constructorTable();

    lexicalConstructor(fileStream);

    RDParser *parser = new RDParser();

    parser->startParser();

    // Relativo a parte 1 do trabalho
    // int token = -1;
    // while (token != END_OF_FILE)
    // {
    //     token = getNextToken();
    //     char *tokenName = getTokenName(token);
    //     char *lexeme = getLexeme();

    //     // sending to stdout
    //     if (token == ID || token == REAL || token == INTEGER || token == LITERAL)
    //     {
    //         printf("%s.%s\n", tokenName, lexeme);
    //     }
    //     else
    //     {
    //         printf("%s\n", tokenName);
    //     }
    // }

    printf("\nERROS DE COMPILACAO\n");
    printf("---------------------------------------\n");
    dumpErrors();

    printf("\nTABELA DE SIMBOLOS: PALAVRAS RESERVADAS\n");
    printf("---------------------------------------\n");
    printf("LEXEMA                Token numerico\n");
    printf("---------------------------------------");
    printReservedWordTable();
    printf("\nTABELA DE SIMBOLOS: IDENTIFICADORES\n");
    printf("-----------------------------------");
    printIdentifierTable();
    printf("\nTABELA DE SIMBOLOS: LITERAIS\n");
    printf("----------------------------");
    printLiteralTable();

    destructorTable();

    
    errorBufferDestructor();
    lexicalDestructor();

    if (isFilenameDynamic)
    {
        free(filename);
    }
    if (fclose(fileStream))
    {
        perror("fclose() failed");
    }
    return 0;
}
