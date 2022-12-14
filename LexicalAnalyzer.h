#ifndef LEXICAL_ANALYZER
#define LEXICAL_ANALYZER

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "TokenDefinitions.h"
#include "ErrorManager.h"
#include "CExport.h"

#define LEXEME_BUFFER_SIZE 32
#define FILE_CHUNK_BUFFER_SIZE 4096
#define TOKEN_NAME_SIZE 32

/**
 * Module constructor
 */
void lexicalConstructor(FILE *inputStream);

/**
 * Module destructor
 */
void lexicalDestructor();

/**
 * Returns the next token from the source code
 */
int getNextToken();

/**
 * Returns the token name
 */
char *getTokenName(int token);

/**
 * Returns the current lexeme
 */
char *getLexeme();

/**
 * Return the source code line where the AFD stopped
*/
int getSourceCodeLine ();

/**
 * Return the source code column where the AFD stopped
*/
int getSourceCodeColumn ();

#endif // LEXICAL_ANALYZER