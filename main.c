#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "CExport.h"
#include "LexicalAnalyzer.h"

int main()
{
    FILE *fp;
    char ch;

    fp = fopen("test/errors.txt", "r");
    if (NULL == fp)
    {
        printf("File can't be opened \n");
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

    lexicalDestructor();
    return 0;
}
