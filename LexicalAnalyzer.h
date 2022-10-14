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

// private variables
static int dfaState = 0;
static char *lexemeBuffer = NULL;
static int lexemeLength = 0;
static int lexemeBufferSize = LEXEME_BUFFER_SIZE; // Counting the endl char
static char *lexemeFoundBuffer = NULL;
static FILE *inputStreamPointer = NULL;
static char *fileChunkBuffer = NULL;
static int fileChunkLength = 0;
static int fileChunkReadPos = 0;
// static char prevChar = '\0';
static char currentChar = '\0';
static int sourceCodeLine = 0;
static int sourceCodeColumn = 0;

// Token names
static char const *tokenList[] = {
    // Puntuaction
    "MINUS", "POINTER", "COMMA", "SEMICOLON", "COLON",
    "EXCLAMATION", "DOT", "QUOTE", "LPAREN", "RPAREN",
    "LBRACKET", "AMP", "RBRACKET", "LBRACE", "RBRACE",

    // Math
    "MULT", "DIV", "MOD", "SUM",

    // BinOp
    "NOT_EQUAL", "AND", "LE", "LEQ", "EQUAL",
    "GT", "GTE", "OR", "VERBAR",

    // Types
    "TYPEDEF", "STRUCT", "BOOL", "CHAR", "DOUBLE", "LONG",
    "REAL", "INTEGER",

    // Statements
    "IF", "ELSE", "BREAK", "CASE", "TRY", "CATCH", "PRINT",
    "READLN", "RETURN", "SWITCH", "THROW", "WHILE",

    // Primary
    "ID", "NUM", "LITERAL", "FALSE", "TRUE", "ASSIGN", "END_OF_FILE"};

// Error labels
static char DIGIT_EXPECTED_ERROR[] = "Digit expected after sign";
static char DIGIT_OR_SIGN_EXPECTED_ERROR[] = "Digit or sign expected after exponent";
static char EOF_LITERAL_ERROR[] = "Unexpected end of file in literal";
static char INVALID_ESCAPE_ERROR[] = "Invalid escape sequence character";
static char EOF_COMMENT_BLOCK_ERROR[] = "Unexpected end of file in block comment";
static char INVALID_CHAR_ERROR[] = "Invalid char error";
static char ONE_CHAR_ERROR[] = "Char literals can have only one char";

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

/**
 * Get next char of the source file
 */
static char getNextChar();

/**
 * Auxiliar method to determine if a char is scaped
 */
static int isScapeChar(char c);

/**
 * Build lexeme string by concating the chars received
 */
static void buildLexeme(char c);

/**
 * Clear the lexeme string
 */
static void clearLexeme();

#endif // LEXICAL_ANALYZER