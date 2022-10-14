#ifndef LEXICAL_ANALYZER
#define LEXICAL_ANALYZER

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "TokenDefinitions.h"
#include "ErrorManager.h"

#define LEXEME_BUFFER_SIZE 2
#define FILE_CHUNK_BUFFER_SIZE 1

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
int nextToken();

/**
 * Returns the token name
 */
char *getTokenName(int token);

/**
 * Returns the current lexeme
 */
char *getLexeme();

#endif // LEXICAL_ANALYZER