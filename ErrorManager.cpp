#include "ErrorManager.h"

typedef struct
{
    char *type;
    char *description;
    int line;
    int column;
} Error;

static char LEXICAL_ERROR_NAME[] = "Lexical error";
static char SYNTAX_ERROR_NAME[] = "Syntax error";

static Error *errorBuffer = NULL;
static int errorBufferSize = 0;
static int errorLength = 0;

void errorBufferDestructor()
{
    free(errorBuffer);
}

void writeLexicalError(char *description, int line, int column)
{

    if (errorLength == errorBufferSize)
    {
        errorBufferSize += ERROR_BUFFER_SIZE;
        // With a NULL pointer the realloc function behaves like a m_alloc
        Error *newErrorBuffer = (Error *)realloc(errorBuffer, sizeof(Error) * errorBufferSize);
        if (newErrorBuffer)
        {
            errorBuffer = newErrorBuffer;
        }
        else
        {
            exit(8);
        }
    }

    int errInd = errorLength++;

    errorBuffer[errInd].type = LEXICAL_ERROR_NAME;
    errorBuffer[errInd].description = description;
    errorBuffer[errInd].line = line;
    errorBuffer[errInd].column = column;
}

void writeSyntaxError(char *description, int line, int column)
{

    if (errorLength == errorBufferSize)
    {
        errorBufferSize += ERROR_BUFFER_SIZE;
        // With a NULL pointer the realloc function behaves like a m_alloc
        Error *newErrorBuffer = (Error *)realloc(errorBuffer, sizeof(Error) * errorBufferSize);
        if (newErrorBuffer)
        {
            errorBuffer = newErrorBuffer;
        }
        else
        {
            exit(9);
        }
    }

    int errInd = errorLength++;

    errorBuffer[errInd].type = SYNTAX_ERROR_NAME;
    errorBuffer[errInd].description = description;
    errorBuffer[errInd].line = line;
    errorBuffer[errInd].column = column;
}

void dumpErrors()
{
    if (errorLength > 0)
    {
        for (int i = 0; i < errorLength; i++)
        {
            Error e = errorBuffer[i];
            fprintf(stderr, "%s at line %d, column %d: %s\n", e.type, e.line, e.column, e.description);
        }
    }
}
