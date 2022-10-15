#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CExport.h"
#include "LexicalAnalyzer.h"

int main()
{
    FILE *fp = NULL;
    // char ch;

    // fp = fopen("test/errors.txt", "r");
    fp = fopen("test/tokens.cmm", "r");
    if (NULL == fp)
    {
        printf("File can't be opened \n");
        exit(2);
    }

    lexicalConstructor(fp);

    int token = -1;
    while (token != END_OF_FILE)
    {
        token = nextToken();
        char *tokenName = getTokenName(token);
        char *lexeme = getLexeme();

        // sending to stdout
        if (token == ID || token == REAL || token == INTEGER || token == LITERAL)
        {
            printf("%s.%s\n", tokenName, lexeme);
        }
        else
        {
            printf("%s\n", tokenName);
        }
    }

    dumpErrors();
    errorBufferDestructor();
    lexicalDestructor();

    if (fclose(fp))
    {
        perror("fclose() failed");
    }
    return 0;
}
