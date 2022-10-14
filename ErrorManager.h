#ifndef ERROR_MANAGER
#define ERROR_MANAGER
#include <stdio.h>

static char LEXICAL_ERROR_NAME[] = "Lexical error";

/**
 * Writes the error in the stderr output stream
*/
extern void writeLexicalError(char *description, int line, int column);

#endif // ERROR_MANAGER