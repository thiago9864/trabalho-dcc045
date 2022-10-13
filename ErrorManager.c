#include "ErrorManager.h"




void writeError(ErrorType type, const char *description){
    char const *errorType = "";
    switch (type)
    {
    case LEXICAL_ERROR:
        errorType = LEXICAL_ERROR_NAME;
        break;
    
    default:
        errorType = UNKNOWN_ERROR_NAME;
        break;
    }

    fprintf(stderr, "%s: %s\n", errorType, description);
}