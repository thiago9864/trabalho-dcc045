#ifndef ERROR_MANAGER
#define ERROR_MANAGER
#include <stdio.h>
#include <stdlib.h>

#define ERROR_BUFFER_SIZE 32

void errorBufferDestructor();

/**
 * Writes the error in the stderr output stream
*/
void writeLexicalError(char *description, int line, int column);

/**
 * Print errors stored at the error buffer on the stderr stream
*/
void dumpErrors();

#endif // ERROR_MANAGER