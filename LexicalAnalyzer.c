#include "LexicalAnalyzer.h"

void lexicalConstructor(FILE *inputStream)
{
    fileChunkBuffer = (char *)malloc(sizeof(char) * FILE_CHUNK_BUFFER_SIZE);

    lexemeBuffer = (char *)malloc(sizeof(char) * LEXEME_BUFFER_SIZE);
    lexemeBuffer[0] = '\0'; // Initialize with endl char

    lexemeFoundBuffer = (char *)malloc(sizeof(char) * LEXEME_BUFFER_SIZE);
    lexemeFoundBuffer[0] = '\0'; // Initialize with endl char

    inputStreamPointer = inputStream;
    dfaState = 0; // Set initial state

    // Init with first char
    currentChar = getNextChar();
}

void lexicalDestructor()
{
    free(lexemeBuffer);
    free(lexemeFoundBuffer);
    free(fileChunkBuffer);
}

static char getNextChar()
{
    // Read a chunk of the file, if data is avaliable
    if (fileChunkLength - fileChunkReadPos == 0)
    {
        fileChunkLength = fread(fileChunkBuffer, sizeof(char), FILE_CHUNK_BUFFER_SIZE, inputStreamPointer);
        fileChunkReadPos = 0;
    }

    // If no char is read, return EOF
    if (fileChunkLength == 0)
    {
        // Close the file on the stream
        fclose(inputStreamPointer);
        return EOF;
    }
    else
    {
        return fileChunkBuffer[fileChunkReadPos++];
    }
}

static int isScapeChar(char c)
{
    if (c == '\'' || c == '\"' || c == '\?' || c == '\\' || c == '\a' || c == '\b' || c == '\f' || c == '\n' || c == '\r' || c == '\t' || c == '\v' || c == '\0')
    {
        return 1;
    }
    return 0;
}

static void buildLexeme(char c)
{
    // Lexeme length will exceed buffer size
    if (lexemeLength + 1 == lexemeBufferSize)
    {
        lexemeBufferSize += LEXEME_BUFFER_SIZE;
        // With a NULL pointer the realloc function behaves like a m_alloc
        lexemeBuffer = (char *)realloc(lexemeBuffer, sizeof(char) * lexemeBufferSize);
    }

    lexemeBuffer[lexemeLength++] = c;
    lexemeBuffer[lexemeLength] = '\0';
}

static void clearLexeme()
{
    memset(lexemeBuffer, '\0', lexemeBufferSize);
    lexemeLength = 0;
}

int nextToken()
{

    int done = 0;
    int token = -1;
    int notConsumeChar = 1;

    clearLexeme();
    dfaState = 0;

    while (done == 0)
    {
        if (notConsumeChar == 0)
        {
            // prevChar = currentChar;
            currentChar = getNextChar();
            // printf("currentChar (new): '%c' - dfaState: %d - done: %d\n", currentChar, dfaState, done);
        }
        else
        {
            // currentChar = prevChar;
            notConsumeChar = 0;
            // printf("currentChar (prev): '%c' - dfaState: %d - done: %d\n", currentChar, dfaState, done);
        }

        if (currentChar == '\n')
        {
            sourceCodeLine++;
            sourceCodeColumn = 0;
        }
        else
        {
            sourceCodeColumn++;
        }

        //  Switch between DFA states using only the number part of their names
        //  q0, q1, q2 turn to 0, 1, 2
        switch (dfaState)
        {

        // Initial State
        case 0:
            if (isspace(currentChar)) // Checks for [' ' \t \n \v \f \r].
            {
                // Stay in this state for the next char
                break;
            }
            else if (isalpha(currentChar)) // Checks for [a-zA-Z]
            {
                // Change to q1
                dfaState = 1;

                buildLexeme(currentChar);
                break;
            }
            else if (isdigit(currentChar)) // Checks for [0-9]
            {
                dfaState = 28;
                buildLexeme(currentChar);
                break;
            }
            else if (currentChar == EOF)
            {
                dfaState = 67;
                break;
            }
            else
            {
                // Check single char tokens
                switch (currentChar)
                {
                case '(':
                    dfaState = 3;
                    break;
                case ')':
                    dfaState = 4;
                    break;
                case '-':
                    dfaState = 5;
                    break;
                case ',':
                    dfaState = 8;
                    break;
                case ';':
                    dfaState = 9;
                    break;
                case ':':
                    dfaState = 10;
                    break;
                case '!':
                    dfaState = 11;
                    break;
                case '.':
                    dfaState = 14;
                    buildLexeme(currentChar);
                    break;
                case '\'':
                    dfaState = 30;
                    buildLexeme(currentChar);
                    break;
                case '"':
                    dfaState = 32;
                    buildLexeme(currentChar);
                    break;
                case ']':
                    dfaState = 38;
                    break;
                case '[':
                    dfaState = 39;
                    break;
                case '}':
                    dfaState = 40;
                    break;
                case '{':
                    dfaState = 41;
                    break;
                case '*':
                    dfaState = 42;
                    break;
                case '/':
                    dfaState = 44;
                    break;
                case '&':
                    dfaState = 50;
                    break;
                case '%':
                    dfaState = 52;
                    break;
                case '+':
                    dfaState = 53;
                    break;
                case '<':
                    dfaState = 54;
                    break;
                case '>':
                    dfaState = 57;
                    break;
                case '=':
                    dfaState = 60;
                    break;
                case '|':
                    dfaState = 63;
                    break;
                default:
                    // Other - ERROR: Invalid character
                    dfaState = 66;
                    break;
                }

                break;
            }
        case 1:
            if (isalpha(currentChar) || isdigit(currentChar)) // Checks if is [a-zA-Z0-9].
            {
                buildLexeme(currentChar);
                break;
            }
            else
            {
                // other
                dfaState = 2;
                notConsumeChar = 1;
            }
            break;
        case 2:
            // Search lexeme on symbols table and return its token/id
            /****** Aqui entra a busca na tabela de símbolos ********/
            token = ID;
            done = 1;
            notConsumeChar = 0;
            break;

        case 3:
            token = LPAREN;
            done = 1;
            break;
        case 4:
            token = RPAREN;
            done = 1;
            break;
        case 5:
            if (currentChar == '>')
            {
                dfaState = 7;
            }
            else
            {
                dfaState = 6;
                notConsumeChar = 1;
            }
            break;
        case 6:
            token = MINUS;
            done = 1;
            notConsumeChar = 1;
            break;
        case 7:
            token = POINTER;
            done = 1;
            break;
        case 8:
            token = COMMA;
            done = 1;
            break;
        case 9:
            token = SEMICOLON;
            done = 1;
            break;
        case 10:
            token = COLON;
            done = 1;
            break;
        case 11:
            if (currentChar == '=')
            {
                dfaState = 12;
            }
            else
            {
                dfaState = 13;
                notConsumeChar = 1;
            }
            break;
        case 12:
            token = NOT_EQUAL;
            done = 1;
            break;
        case 13:
            token = EXCLAMATION;
            done = 1;
            break;

            /////////////// Numbers /////////////////

        case 14:
            if (isdigit(currentChar))
            {
                dfaState = 16;
                buildLexeme(currentChar);
            }
            else
            {
                dfaState = 15;
                notConsumeChar = 1;
            }
            break;
        case 15:
            token = DOT;
            done = 1;
            break;
        case 16:
            if (currentChar == 'e' || currentChar == 'E')
            {
                dfaState = 17;
                buildLexeme(currentChar);
            }
            else if (isdigit(currentChar))
            {
                buildLexeme(currentChar);
                break;
            }
            else
            {
                dfaState = 20;
                notConsumeChar = 1;
            }
            break;
        case 17:
            if (currentChar == '+' || currentChar == '-')
            {
                dfaState = 18;
            }
            else if (isdigit(currentChar))
            {
                dfaState = 19;
            }
            else
            {
                dfaState = 22;
            }
            buildLexeme(currentChar);
            break;
        case 18:
            if (isdigit(currentChar))
            {
                dfaState = 19;
            }
            else
            {
                dfaState = 21;
            }
            buildLexeme(currentChar);
            break;
        case 19:
            if (isdigit(currentChar))
            {
                buildLexeme(currentChar);
                break;
            }
            else
            {
                dfaState = 20;
                notConsumeChar = 1;
            }
            break;
        case 20:
            token = REAL;
            done = 1;
            break;
        case 21:
            // ERROR: Digit expected after sign.
            // Restart automaton
            dfaState = 0;
            writeLexicalError(DIGIT_EXPECTED_ERROR, sourceCodeLine, sourceCodeColumn);
            clearLexeme();
            break;
        case 22:
            // ERROR: Digit or sign expected after exponent.
            // Restart automaton
            dfaState = 0;
            writeLexicalError(DIGIT_OR_SIGN_EXPECTED_ERROR, sourceCodeLine, sourceCodeColumn);
            clearLexeme();
            break;
        case 23:
            if (currentChar == '-')
            {
                dfaState = 18;
            }
            else if (currentChar == '+')
            {
                dfaState = 24;
            }
            else if (isdigit(currentChar))
            {
                dfaState = 25;
            }
            else
            {
                dfaState = 22;
            }
            buildLexeme(currentChar);
            break;
        case 24:
            if (isdigit(currentChar))
            {
                dfaState = 25;
            }
            else
            {
                dfaState = 21;
            }
            buildLexeme(currentChar);
            break;
        case 25:
            if (isdigit(currentChar))
            {
                buildLexeme(currentChar);
                break;
            }
            else
            {
                dfaState = 26;
                notConsumeChar = 1;
            }
            break;
        case 26:
            token = INTEGER;
            done = 1;
            break;
        case 27:
            if (isdigit(currentChar))
            {
                dfaState = 25;
                buildLexeme(currentChar);
            }
            else
            {
                dfaState = 26;
                notConsumeChar = 1;
            }
            break;
        case 28:
            if (currentChar == '.')
            {
                dfaState = 29;
                buildLexeme(currentChar);
            }
            else if (currentChar == 'e' || currentChar == 'E')
            {
                dfaState = 23;
                buildLexeme(currentChar);
            }
            else if (isdigit(currentChar))
            {
                buildLexeme(currentChar);
                break;
            }
            else
            {
                dfaState = 26;
                notConsumeChar = 1;
            }
            break;

        case 29:
            if (currentChar == 'e' || currentChar == 'E')
            {
                dfaState = 27;
                buildLexeme(currentChar);
            }
            else if (isdigit(currentChar))
            {
                dfaState = 16;
                buildLexeme(currentChar);
            }
            else
            {
                dfaState = 26;
                notConsumeChar = 1;
            }
            break;

            //////////////////////////////////////////

            /////////////// Literals /////////////////

        case 30:
            if (currentChar == '\'')
            {
                dfaState = 31;
            }
            else if (currentChar == EOF)
            {
                dfaState = 34;
            }
            else if (currentChar == '\\')
            {
                dfaState = 36;
            }
            else
            {
                dfaState = 37;
            }
            buildLexeme(currentChar);
            break;
        case 31:
            token = LITERAL;
            done = 1;
            notConsumeChar = 1;
            break;
        case 32:
            if (currentChar == '"')
            {
                dfaState = 31;
            }
            else if (currentChar == EOF)
            {
                dfaState = 34;
            }
            else if (currentChar == '\\')
            {
                dfaState = 33;
            }
            // If not match with any of the conditions, is other and loop
            // in this state
            buildLexeme(currentChar);
            break;
        case 33:
            if (isScapeChar(currentChar))
            {
                dfaState = 32;
            }
            else if (currentChar == EOF)
            {
                dfaState = 34;
            }
            else
            {
                dfaState = 35;
            }
            // If not match with any of the conditions, is other and loop
            // in this state
            buildLexeme(currentChar);
            break;
        case 34:
            // ERROR: Unexpected EOF in a comment
            token = END_OF_FILE;
            done = 1;
            writeLexicalError(EOF_LITERAL_ERROR, sourceCodeLine, sourceCodeColumn);
            break;
        case 35:
            // ERROR: Invalid escape sequence character.
            // Restart automaton
            dfaState = 0;
            writeLexicalError(INVALID_ESCAPE_ERROR, sourceCodeLine, sourceCodeColumn);
            clearLexeme();
            break;
        case 36:
            if (isScapeChar(currentChar))
            {
                dfaState = 30;
            }
            else if (currentChar == EOF)
            {
                dfaState = 34;
            }
            else
            {
                dfaState = 35;
            }
            // If not match with any of the conditions, is other and loop
            // in this state
            buildLexeme(currentChar);
            break;
        case 37:
            if (currentChar == '\'')
            {
                dfaState = 31;
            }
            else
            {
                dfaState = 68;
            }
            buildLexeme(currentChar);
            break;

            //////////////////////////////////////////

        case 38:
            token = RBRACKET;
            done = 1;
            break;
        case 39:
            token = LBRACKET;
            done = 1;
            break;
        case 40:
            token = RBRACE;
            done = 1;
            break;
        case 41:
            token = LBRACE;
            done = 1;
            break;
        case 42:
            token = MULT;
            done = 1;
            break;

            /////////////// Comments /////////////////

        case 43:
            if (currentChar == '\n')
            {
                dfaState = 0;
            }
            else if (currentChar == EOF)
            {
                dfaState = 67;
            }
            // If not match with any of the conditions, is other and loop
            // in this state
            break;
        case 44:
            if (currentChar == '*')
            {
                dfaState = 46;
            }
            else if (currentChar == '/')
            {
                dfaState = 43;
            }
            else
            {
                dfaState = 45;
                notConsumeChar = 1;
            }
            break;
        case 45:
            token = DIV;
            done = 1;
            break;
        case 46:
            if (currentChar == '*')
            {
                dfaState = 48;
            }
            else if (currentChar == EOF)
            {
                dfaState = 47;
            }
            // If not match with any of the conditions, is other and loop
            // in this state
            break;
        case 47:
            // ERROR: Unexpected EOF in a comment
            token = END_OF_FILE;
            done = 1;
            writeLexicalError(EOF_COMMENT_BLOCK_ERROR, sourceCodeLine, sourceCodeColumn);
            break;
        case 48:
            if (currentChar == EOF)
            {
                dfaState = 47;
            }
            else if (currentChar == '/')
            {
                dfaState = 0;
            }
            else
            {
                dfaState = 46;
            }
            break;

            //////////////////////////////////////////

        case 49:
            token = AMP;
            done = 1;
            notConsumeChar = 1;
            break;
        case 50:
            if (currentChar == '&')
            {
                dfaState = 51;
            }
            else
            {
                dfaState = 49;
                notConsumeChar = 1;
            }
            break;
        case 51:
            token = AND;
            done = 1;
            break;
        case 52:
            token = MOD;
            done = 1;
            break;
        case 53:
            token = SUM;
            done = 1;
            break;
        case 54:
            if (currentChar == '=')
            {
                dfaState = 55;
            }
            else
            {
                dfaState = 56;
                notConsumeChar = 1;
            }
            break;
        case 55:
            token = LEQ;
            done = 1;
            break;
        case 56:
            token = LE;
            done = 1;
            break;
        case 57:
            if (currentChar == '=')
            {
                dfaState = 59;
            }
            else
            {
                dfaState = 58;
                notConsumeChar = 1;
            }
            break;
        case 58:
            token = GT;
            done = 1;
            break;
        case 59:
            token = GTE;
            done = 1;
            break;
        case 60:
            if (currentChar == '=')
            {
                dfaState = 62;
            }
            else
            {
                dfaState = 61;
                notConsumeChar = 1;
            }
            break;
        case 61:
            token = ASSIGN;
            done = 1;
            break;
        case 62:
            token = EQUAL;
            done = 1;
            break;

        case 63:
            if (currentChar == '|')
            {
                dfaState = 65;
            }
            else
            {
                dfaState = 64;
                notConsumeChar = 1;
            }
            break;
        case 64:
            token = VERBAR;
            done = 1;
            break;
        case 65:
            token = OR;
            done = 1;
            break;
        case 66:
            // ERROR: Invalid char error
            // Restart automaton
            dfaState = 0;
            writeLexicalError(INVALID_CHAR_ERROR, sourceCodeLine, sourceCodeColumn);
            clearLexeme();
            break;
        case 67:
            token = END_OF_FILE;
            done = 1;
            break;
        case 68:
            // ERROR: Char literals can have only one char
            // Restart automaton
            dfaState = 0;
            writeLexicalError(ONE_CHAR_ERROR, sourceCodeLine, sourceCodeColumn);
            clearLexeme();
            break;
        }
    }

    return token;
}

char *getLexeme()
{
    if (lexemeLength == 0)
    {
        return "";
    }
    strcpy(lexemeFoundBuffer, lexemeBuffer);
    return lexemeFoundBuffer;
}

char *getTokenName(int token)
{
    return strdup(tokenList[token]);
}