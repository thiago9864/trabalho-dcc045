#ifndef ERROR_MANAGER
#define ERROR_MANAGER
#include <stdio.h>

typedef enum ErrorType
{
    LEXICAL_ERROR
} ErrorType;

static char LEXICAL_ERROR_NAME[] = "Lexical error";
static char UNKNOWN_ERROR_NAME[] = "Unknown error";

// writeError(LEXICAL_ERROR, "Digit expected after sign");
// writeError(LEXICAL_ERROR, "Digit or sign expected after exponent");
// writeError(LEXICAL_ERROR, "Unexpected end of file in literal");
// writeError(LEXICAL_ERROR, "Invalid escape sequence character");
// writeError(LEXICAL_ERROR, "Unexpected end of file in block comment");
// writeError(LEXICAL_ERROR, "Invalid char error");
// writeError(LEXICAL_ERROR, "Char literals can have only one char");

/**
 * Writes the error in the stderr output stream
*/
void writeError(ErrorType type, char *description);

#endif // ERROR_MANAGER