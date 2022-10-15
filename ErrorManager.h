#ifndef ERROR_MANAGER
#define ERROR_MANAGER
#include <stdio.h>
#include <stdlib.h>

#define ERROR_BUFFER_SIZE 32

extern void errorBufferDestructor();

/**
 * Writes the error in the stderr output stream
*/
extern void writeLexicalError(char *description, int line, int column);

/**
 * Print errors stored at the error buffer on the stderr stream
*/
extern void dumpErrors();

#endif // ERROR_MANAGER