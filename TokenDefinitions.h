#ifndef TOKEN_DEFINITIONS
#define TOKEN_DEFINITIONS

// Puntuaction
#define MINUS 0
#define POINTER 1 
#define COMMA 2
#define SEMICOLON 3
#define COLON 4
#define EXCLAMATION 5
#define DOT 6
#define QUOTE 7
#define LPAREN 8
#define RPAREN 9
#define LBRACKET 10
#define AMP 11
#define RBRACKET 12
#define LBRACE 13
#define RBRACE 14
#define TRIPLE_DOT 56

// Math
#define MULT 15
#define DIV 16
#define MOD 17
#define SUM 18

// BinOp
#define NOT_EQUAL 19
#define AND 20
#define LE 21
#define LEQ 22
#define EQUAL 23
#define GT 24
#define GTE 25
#define OR 26
#define VERBAR 27

// Types
#define TYPEDEF 28
#define STRUCT 29
#define BOOL 30
#define CHAR 31
#define DOUBLE 32
#define LONG 33
#define REAL 34
#define INTEGER 35

// Statements
#define IF 36
#define ELSE 37
#define BREAK 38
#define CASE 39
#define TRY 40
#define CATCH 41
#define PRINT 42
#define READLN 43
#define RETURN 44
#define SWITCH 45
#define THROW 46
#define WHILE 47

// Primary
#define ID 48
#define NUM 49
#define LITERAL 50
#define FALSE 51
#define TRUE 52
#define ASSIGN 53
#define ASCII 55

#define END_OF_FILE 54

#endif //TOKEN_DEFINITIONS