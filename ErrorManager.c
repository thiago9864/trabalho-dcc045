#include "ErrorManager.h"

static char LEXICAL_ERROR_NAME[] = "Lexical error";

void writeLexicalError(char *description, int line, int column){
    fprintf(stderr, "%s at line %d, column %d: %s\n", LEXICAL_ERROR_NAME, line, column, description);
}