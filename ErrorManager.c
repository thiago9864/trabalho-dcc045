#include "ErrorManager.h"

void writeLexicalError(char *description, int line, int column){
    fprintf(stderr, "%s at line %d, column %d: %s\n", LEXICAL_ERROR_NAME, line, column, description);
}