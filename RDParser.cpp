#include "RDParser.h"

RDParser::RDParser()
{
    printf("*************** Inicializa o parser ***************\n");
}
RDParser::~RDParser() {}

void RDParser::startParser()
{
    nextToken();
    Program();
}

void RDParser::nextToken()
{
    // Aqui obtem o nextToken do analisador léxico
    lookAhead = getNextToken();
    char *tokenName = getTokenName(lookAhead);
    printf("[DEBUG] Token de lookAhead: %s\n", tokenName);
}

void RDParser::match(int token)
{
    if (token != lookAhead)
    {
        // Erro sintático
    }
    else
    {
        nextToken();
    }
}

static char errorTemplate[] = "Token Error: ";

void RDParser::error(int expectedToken, const int *syncArr)
{
    char *tokenName = getTokenName(expectedToken);
    int templateLen = 0;
    for (; errorTemplate[templateLen] != '\0'; templateLen++);
    char *errStr = new char[templateLen + strlen(tokenName)];
    errStr[0] = '\0';
    strcat(errStr, errorTemplate);
    strcat(errStr, tokenName);

    writeSyntaxError(errStr, getSourceCodeLine(), getSourceCodeColumn());

    int i = 0;
    while (lookAhead != END_OF_FILE)
    {
        while (syncArr[i] != END_OF_FILE)
        {
            if (lookAhead != syncArr[i])
            {
                i++;
            }
            return;
        }
        i = 0;
        getNextToken();
    }
}

int RDParser::sync_Program[] = {END_OF_FILE};
void RDParser::Program()
{
    switch (lookAhead)
    {
    case END_OF_FILE:
        // Program ::= ε
        break;
    case ID:
    case INTEGER:
    case LONG:
    case FLOAT:
    case BOOL:
    case CHAR:
    case DOUBLE:
        // Program ::= VarFn Program
        VarFn();
        Program();
        break;
    case TYPEDEF:
        // Program ::= TypeDecl Program
        TypeDecl();
        Program();
        break;
    default:
        error(lookAhead, sync_Program);
    }
}

int RDParser::sync_Type[] = {ID, MULT, END_OF_FILE};
void RDParser::Type()
{
    switch (lookAhead)
    {
    case ID:
        // Type ::= id
        match(ID);
        break;
    case INTEGER:
        // Type ::= int
        match(INTEGER);
        break;
    case LONG:
        // Type ::= long
        match(LONG);
        break;
    case FLOAT:
        // Type ::= float
        match(FLOAT);
        break;
    case BOOL:
        // Type ::= bool
        match(BOOL);
        break;
    case CHAR:
        // Type ::= char
        match(CHAR);
        break;
    case DOUBLE:
        // Type ::= double
        match(DOUBLE);
        break;
    default:
        error(lookAhead, sync_Type);
    }
}

int RDParser::sync_IdList[] = {SEMICOLON, END_OF_FILE};
void RDParser::IdList()
{
    switch (lookAhead)
    {
    case ID:
        // IdList ::= id IdListK2
        match(ID);
        IdListK2();
        break;
    default:
        error(lookAhead, sync_IdList);
    }
}

int RDParser::sync_IdListK2[] = {SEMICOLON, END_OF_FILE};
void RDParser::IdListK2()
{
    switch (lookAhead)
    {
    case COMMA:
        // IdListK2 ::= , IdList
        match(COMMA);
        IdList();
        break;
    case LBRACKET:
        // IdListK2 ::= [ integer ] Array IdListK3
        match(LBRACKET);
        match(NUM_INT);
        match(RBRACKET);
        Array();
        IdListK3();
        break;
    case SEMICOLON:
        // IdListK2 ::= ε
        break;
    default:
        error(lookAhead, sync_IdListK2);
    }
}

int RDParser::sync_IdListK3[] = {SEMICOLON, END_OF_FILE};
void RDParser::IdListK3()
{
    switch (lookAhead)
    {
    case COMMA:
        // IdListK3 ::= , IdList
        match(COMMA);
        IdList();
        break;
    case SEMICOLON:
        // IdListK3 ::= ε
        break;
    default:
        error(lookAhead, sync_IdListK3);
    }
}

int RDParser::sync_Array[] = {COMMA, RPAREN, SEMICOLON, END_OF_FILE};
void RDParser::Array()
{
    switch (lookAhead)
    {
    case COMMA:
    case SEMICOLON:
    case RPAREN:
        // Array ::= ε
        break;
    case LBRACKET:
        // Array ::= [ integer ] Array
        match(LBRACKET);
        match(NUM_INT);
        match(RBRACKET);
        Array();
        break;
    default:
        error(lookAhead, sync_Array);
    }
}

int RDParser::sync_TypeDecl[] = {TYPEDEF, ID, INTEGER, LONG, FLOAT, BOOL, CHAR, DOUBLE, END_OF_FILE};
void RDParser::TypeDecl()
{
    switch (lookAhead)
    {
    case TYPEDEF:
        // TypeDecl ::= typedef struct { Type IdList ; VarDecl } id ;
        match(TYPEDEF);
        match(STRUCT);
        match(LBRACE);
        Type();
        IdList();
        match(SEMICOLON);
        VarDecl();
        match(RBRACE);
        match(ID);
        match(SEMICOLON);
        break;
    default:
        error(lookAhead, sync_TypeDecl);
    }
}

int RDParser::sync_VarFn[] = {TYPEDEF, ID, INTEGER, LONG, FLOAT, BOOL, CHAR, DOUBLE, END_OF_FILE};
void RDParser::VarFn()
{
    switch (lookAhead)
    {
    case ID:
    case INTEGER:
    case LONG:
    case FLOAT:
    case BOOL:
    case CHAR:
    case DOUBLE:
        // VarFn ::= Type VarFnK
        Type();
        VarFnK();
        break;
    default:
        error(lookAhead, sync_VarFn);
    }
}

int RDParser::sync_VarFnK[] = {TYPEDEF, ID, INTEGER, LONG, FLOAT, BOOL, CHAR, DOUBLE, END_OF_FILE};
void RDParser::VarFnK()
{
    switch (lookAhead)
    {
    case ID:
        // VarFnK ::= id VarFnL
        match(ID);
        VarFnL();
        break;
    case MULT:
        // VarFnK ::= * id VarFnL
        match(MULT);
        match(ID);
        VarFnL();
        break;
    default:
        error(lookAhead, sync_VarFnK);
    }
}

int RDParser::sync_VarFnL[] = {TYPEDEF, ID, INTEGER, LONG, FLOAT, BOOL, CHAR, DOUBLE, END_OF_FILE};
void RDParser::VarFnL()
{
    switch (lookAhead)
    {
    case COMMA:
    case LBRACKET:
    case SEMICOLON:
        // VarFnL ::= IdListK2 ;
        IdListK2();
        match(SEMICOLON);
        break;
    case LPAREN:
        // VarFnL ::= FunctionDeclL
        FunctionDeclL();
        break;
    default:
        error(lookAhead, sync_VarFnL);
    }
}

int RDParser::sync_VarDecl[] = {RBRACE, END_OF_FILE};
void RDParser::VarDecl()
{
    switch (lookAhead)
    {
    case ID:
    case INTEGER:
    case LONG:
    case FLOAT:
    case BOOL:
    case CHAR:
    case DOUBLE:
        // VarDecl ::= Type VarDeclK
        Type();
        VarDeclK();
        break;
    case RBRACE:
        // VarDecl ::= ε
        break;
    default:
        error(lookAhead, sync_VarDecl);
    }
}

int RDParser::sync_VarDeclK[] = {RBRACE, END_OF_FILE};
void RDParser::VarDeclK()
{
    switch (lookAhead)
    {
    case ID:
        // VarDeclK ::= IdList ; VarDecl
        IdList();
        match(SEMICOLON);
        VarDecl();
        break;
    default:
        error(lookAhead, sync_VarDeclK);
    }
}

int RDParser::sync_FunctionDecl[] = {END_OF_FILE};
void RDParser::FunctionDecl()
{
    switch (lookAhead)
    {
    case ID:
    case INTEGER:
    case LONG:
    case FLOAT:
    case BOOL:
    case CHAR:
    case DOUBLE:
        // FunctionDecl ::= Type FunctionDeclK
        Type();
        FunctionDeclK();
        break;
    default:
        error(lookAhead, sync_FunctionDecl);
    }
}

int RDParser::sync_FunctionDeclK[] = {END_OF_FILE};
void RDParser::FunctionDeclK()
{
    switch (lookAhead)
    {
    case ID:
        // FunctionDeclK ::= id FunctionDeclL
        match(ID);
        FunctionDeclL();
        break;
    case MULT:
        // FunctionDeclK ::= * id FunctionDeclL
        match(MULT);
        match(ID);
        FunctionDeclL();
        break;
    default:
        error(lookAhead, sync_FunctionDeclK);
    }
}

int RDParser::sync_FunctionDeclL[] = {TYPEDEF, ID, INTEGER, LONG, FLOAT, BOOL, CHAR, DOUBLE, END_OF_FILE};
void RDParser::FunctionDeclL()
{
    switch (lookAhead)
    {
    case LPAREN:
        // FunctionDeclL ::= ( FormalList ) { FunctionBody }
        match(LPAREN);
        FormalList();
        match(RPAREN);
        match(LBRACE);
        FunctionBody();
        match(RBRACE);
        break;
    default:
        error(lookAhead, sync_FunctionDeclL);
    }
}

int RDParser::sync_FormalRest[] = {RPAREN, END_OF_FILE};
void RDParser::FormalRest()
{
    switch (lookAhead)
    {
    case COMMA:
        // FormalRest ::= , Type FormalRestK
        match(COMMA);
        Type();
        FormalRestK();
        break;
    case RPAREN:
        // FormalRest ::= ε
        break;
    default:
        error(lookAhead, sync_FormalRest);
    }
}

int RDParser::sync_FormalRestK[] = {RPAREN, END_OF_FILE};
void RDParser::FormalRestK()
{
    switch (lookAhead)
    {
    case ID:
        // FormalRestK ::= id Array FormalRest
        match(ID);
        Array();
        FormalRest();
        break;
    case MULT:
        // FormalRestK ::= * id Array FormalRest
        match(MULT);
        match(ID);
        Array();
        FormalRest();
        break;
    default:
        error(lookAhead, sync_FormalRestK);
    }
}

int RDParser::sync_FormalList[] = {RPAREN, END_OF_FILE};
void RDParser::FormalList()
{
    switch (lookAhead)
    {
    case ID:
    case INTEGER:
    case LONG:
    case FLOAT:
    case BOOL:
    case CHAR:
    case DOUBLE:
        // FormalList ::= Type FormalListK
        Type();
        FormalListK();
        break;
    case RPAREN:
        // FormalList ::= ε
        break;
    default:
        error(lookAhead, sync_FormalList);
    }
}

int RDParser::sync_FormalListK[] = {RPAREN, END_OF_FILE};
void RDParser::FormalListK()
{
    switch (lookAhead)
    {
    case ID:
        // FormalListK ::= id Array FormalRest
        match(ID);
        Array();
        FormalRest();
        break;
    case MULT:
        // FormalListK ::= * id Array FormalRest
        match(MULT);
        match(ID);
        Array();
        FormalRest();
        break;
    default:
        error(lookAhead, sync_FormalListK);
    }
}

int RDParser::sync_FunctionBody[] = {RBRACE, END_OF_FILE};
void RDParser::FunctionBody()
{
    switch (lookAhead)
    {
    case ID:
        // FunctionBody ::= id FunctionBodyL
        match(ID);
        FunctionBodyL();
        break;
    case INTEGER:
        // FunctionBody ::= int IdList ; FunctionBody
        match(INTEGER);
        IdList();
        match(SEMICOLON);
        FunctionBody();
        break;
    case LONG:
        // FunctionBody ::= long IdList ; FunctionBody
        match(LONG);
        IdList();
        match(SEMICOLON);
        FunctionBody();
        break;
    case FLOAT:
        // FunctionBody ::= float IdList ; FunctionBody
        match(FLOAT);
        IdList();
        match(SEMICOLON);
        FunctionBody();
        break;
    case BOOL:
        // FunctionBody ::= bool IdList ; FunctionBody
        match(BOOL);
        IdList();
        match(SEMICOLON);
        FunctionBody();
        break;
    case CHAR:
        // FunctionBody ::= char IdList ; FunctionBody
        match(CHAR);
        IdList();
        match(SEMICOLON);
        FunctionBody();
        break;
    case DOUBLE:
        // FunctionBody ::= double IdList ; FunctionBody
        match(DOUBLE);
        IdList();
        match(SEMICOLON);
        FunctionBody();
        break;
    case NUM_INT:
    case LBRACE:
    case MULT:
    case LPAREN:
    case IF:
    case WHILE:
    case SWITCH:
    case BREAK:
    case PRINT:
    case READLN:
    case RETURN:
    case THROW:
    case TRY:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
    case AMP:
        // FunctionBody ::= StmtList
        StmtList();
        break;
    case RBRACE:
        // FunctionBody ::= ε
        break;
    default:
        error(lookAhead, sync_FunctionBody);
    }
}

int RDParser::sync_FunctionBodyL[] = {RBRACE, END_OF_FILE};
void RDParser::FunctionBodyL()
{
    switch (lookAhead)
    {
    case ID:
        // FunctionBodyL ::= IdList ; FunctionBody
        IdList();
        match(SEMICOLON);
        FunctionBody();
        break;
    case LBRACKET:
        // FunctionBodyL ::= [ Expr ] ; FunctionBody
        match(LBRACKET);
        Expr();
        match(RBRACKET);
        match(SEMICOLON);
        FunctionBody();
        break;
    case RBRACE:
        // FunctionBodyL ::= ε
        break;
    case LPAREN:
        // FunctionBodyL ::= ( ExprList ) ; FunctionBody
        match(LPAREN);
        ExprList();
        match(RPAREN);
        match(SEMICOLON);
        FunctionBody();
        break;
    case DOT:
        // FunctionBodyL ::= . Expr ; FunctionBody
        match(DOT);
        Expr();
        match(SEMICOLON);
        FunctionBody();
        break;
    case POINTER:
        // FunctionBodyL ::= -> Expr ; FunctionBody
        match(POINTER);
        Expr();
        match(SEMICOLON);
        FunctionBody();
        break;
    case ASSIGN:
        // FunctionBodyL ::= = StmtList2K ; FunctionBody
        match(ASSIGN);
        StmtList2K();
        match(SEMICOLON);
        FunctionBody();
        break;
    default:
        error(lookAhead, sync_FunctionBodyL);
    }
}

int RDParser::sync_ExprList[] = {RPAREN, END_OF_FILE};
void RDParser::ExprList()
{
    switch (lookAhead)
    {
    case ID:
    case NUM_INT:
    case MULT:
    case LPAREN:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
    case AMP:
    case SUM:
    case MINUS:
    case EXCLAMATION:
        // ExprList ::= ExprListTail
        ExprListTail();
        break;
    case RPAREN:
        // ExprList ::= ε
        break;
    default:
        error(lookAhead, sync_ExprList);
    }
}

int RDParser::sync_ExprListTail[] = {RPAREN, END_OF_FILE};
void RDParser::ExprListTail()
{
    switch (lookAhead)
    {
    case ID:
    case NUM_INT:
    case MULT:
    case LPAREN:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
    case AMP:
    case SUM:
    case MINUS:
    case EXCLAMATION:
        // ExprListTail ::= Expr ExprListTailL
        Expr();
        ExprListTailL();
        break;
    default:
        error(lookAhead, sync_ExprListTail);
    }
}

int RDParser::sync_ExprListTailL[] = {RPAREN, END_OF_FILE};
void RDParser::ExprListTailL()
{
    switch (lookAhead)
    {
    case COMMA:
        // ExprListTailL ::= , ExprListTail
        match(COMMA);
        ExprListTail();
        break;
    case RPAREN:
        // ExprListTailL ::= ε
        break;
    default:
        error(lookAhead, sync_ExprListTailL);
    }
}

int RDParser::sync_StmtList[] = {RBRACE, CASE, END_OF_FILE};
void RDParser::StmtList()
{
    switch (lookAhead)
    {
    case NUM_INT:
    case LBRACE:
    case MULT:
    case LPAREN:
    case IF:
    case WHILE:
    case SWITCH:
    case BREAK:
    case PRINT:
    case READLN:
    case RETURN:
    case THROW:
    case TRY:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
    case AMP:
        // StmtList ::= Stmt StmtListK
        Stmt();
        StmtListK();
        break;
    default:
        error(lookAhead, sync_StmtList);
    }
}

int RDParser::sync_StmtListK[] = {RBRACE, CASE, END_OF_FILE};
void RDParser::StmtListK()
{
    switch (lookAhead)
    {
    case NUM_INT:
    case LBRACE:
    case MULT:
    case LPAREN:
    case IF:
    case WHILE:
    case SWITCH:
    case BREAK:
    case PRINT:
    case READLN:
    case RETURN:
    case THROW:
    case TRY:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
    case AMP:
        // StmtListK ::= StmtList
        StmtList();
        break;
    case RBRACE:
    case CASE:
        // StmtListK ::= ε
        break;
    default:
        error(lookAhead, sync_StmtListK);
    }
}

int RDParser::sync_StmtList2[] = {SEMICOLON, RBRACE, END_OF_FILE};
void RDParser::StmtList2()
{
    switch (lookAhead)
    {
    case ID:
    case NUM_INT:
    case LBRACE:
    case MULT:
    case LPAREN:
    case IF:
    case WHILE:
    case SWITCH:
    case BREAK:
    case PRINT:
    case READLN:
    case RETURN:
    case THROW:
    case TRY:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
    case AMP:
    case SUM:
    case MINUS:
    case EXCLAMATION:
        // StmtList2 ::= Stmt2 StmtList2K
        Stmt2();
        StmtList2K();
        break;
    default:
        error(lookAhead, sync_StmtList2);
    }
}

int RDParser::sync_StmtList2K[] = {SEMICOLON, RBRACE, END_OF_FILE};
void RDParser::StmtList2K()
{
    switch (lookAhead)
    {
    case ID:
    case NUM_INT:
    case LBRACE:
    case MULT:
    case LPAREN:
    case IF:
    case WHILE:
    case SWITCH:
    case BREAK:
    case PRINT:
    case READLN:
    case RETURN:
    case THROW:
    case TRY:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
    case AMP:
    case SUM:
    case MINUS:
    case EXCLAMATION:
        // StmtList2K ::= StmtList2
        StmtList2();
        break;
    case SEMICOLON:
    case RBRACE:
        // StmtList2K ::= ε
        break;
    default:
        error(lookAhead, sync_StmtList2K);
    }
}

int RDParser::sync_CaseBlock[] = {RBRACE, END_OF_FILE};
void RDParser::CaseBlock()
{
    switch (lookAhead)
    {
    case CASE:
        // CaseBlock ::= case integer : CaseBlockL
        match(CASE);
        match(NUM_INT);
        match(COLON);
        CaseBlockL();
        break;
    default:
        error(lookAhead, sync_CaseBlock);
    }
}

int RDParser::sync_CaseBlockL[] = {RBRACE, END_OF_FILE};
void RDParser::CaseBlockL()
{
    switch (lookAhead)
    {
    case NUM_INT:
    case LBRACE:
    case MULT:
    case LPAREN:
    case IF:
    case WHILE:
    case SWITCH:
    case BREAK:
    case PRINT:
    case READLN:
    case RETURN:
    case THROW:
    case TRY:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
    case AMP:
        // CaseBlockL ::= StmtList CaseBlock
        StmtList();
        CaseBlock();
        break;
    case CASE:
        // CaseBlockL ::= CaseBlock
        CaseBlock();
        break;
    default:
        error(lookAhead, sync_CaseBlockL);
    }
}

int RDParser::sync_Stmt[] = {RBRACE, IF, WHILE, SWITCH, BREAK, PRINT, READLN, RETURN, THROW, LBRACE, TRY, NUM_INT, NUM_REAL, LITERAL, ASCII, LPAREN, TRUE, FALSE, AMP, MULT, CASE, END_OF_FILE};
void RDParser::Stmt()
{
    switch (lookAhead)
    {
    case NUM_INT:
    case MULT:
    case LPAREN:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
    case AMP:
        // Stmt ::= ExpSemID ;
        ExpSemID();
        match(SEMICOLON);
        break;
    case LBRACE:
        // Stmt ::= { StmtList2 }
        match(LBRACE);
        StmtList2();
        match(RBRACE);
        break;
    case IF:
        // Stmt ::= if ( Expr ) { Stmt2 } IfOpt
        match(IF);
        match(LPAREN);
        Expr();
        match(RPAREN);
        match(LBRACE);
        Stmt2();
        match(RBRACE);
        IfOpt();
        break;
    case WHILE:
        // Stmt ::= while ( Expr ) Stmt2
        match(WHILE);
        match(LPAREN);
        Expr();
        match(RPAREN);
        Stmt2();
        break;
    case SWITCH:
        // Stmt ::= switch ( Expr ) { CaseBlock }
        match(SWITCH);
        match(LPAREN);
        Expr();
        match(RPAREN);
        match(LBRACE);
        CaseBlock();
        match(RBRACE);
        break;
    case BREAK:
        // Stmt ::= break ;
        match(BREAK);
        match(SEMICOLON);
        break;
    case PRINT:
        // Stmt ::= print ( ExprList ) ;
        match(PRINT);
        match(LPAREN);
        ExprList();
        match(RPAREN);
        match(SEMICOLON);
        break;
    case READLN:
        // Stmt ::= readln ( Expr ) ;
        match(READLN);
        match(LPAREN);
        Expr();
        match(RPAREN);
        match(SEMICOLON);
        break;
    case RETURN:
        // Stmt ::= return Expr ;
        match(RETURN);
        Expr();
        match(SEMICOLON);
        break;
    case THROW:
        // Stmt ::= throw ;
        match(THROW);
        match(SEMICOLON);
        break;
    case TRY:
        // Stmt ::= try Stmt2 catch ( ... ) Stmt2
        match(TRY);
        Stmt2();
        match(CATCH);
        match(LPAREN);
        match(TRIPLE_DOT);
        match(RPAREN);
        Stmt2();
        break;
    default:
        error(lookAhead, sync_Stmt);
    }
}

int RDParser::sync_Stmt2[] = {IF, WHILE, SWITCH, BREAK, PRINT, READLN, RETURN, THROW, LBRACE, TRY, MINUS, SUM, EXCLAMATION, ID, NUM_INT, NUM_REAL, LITERAL, ASCII, LPAREN, TRUE, FALSE, AMP, MULT, RBRACE, CATCH, SEMICOLON, CASE, END_OF_FILE};
void RDParser::Stmt2()
{
    switch (lookAhead)
    {
    case ID:
    case NUM_INT:
    case MULT:
    case LPAREN:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
    case AMP:
    case SUM:
    case MINUS:
    case EXCLAMATION:
        // Stmt2 ::= Expr ;
        Expr();
        match(SEMICOLON);
        break;
    case LBRACE:
        // Stmt2 ::= { StmtList2 }
        match(LBRACE);
        StmtList2();
        match(RBRACE);
        break;
    case IF:
        // Stmt2 ::= if ( Expr ) { Stmt2 } IfOpt
        match(IF);
        match(LPAREN);
        Expr();
        match(RPAREN);
        match(LBRACE);
        Stmt2();
        match(RBRACE);
        IfOpt();
        break;
    case WHILE:
        // Stmt2 ::= while ( Expr ) Stmt2
        match(WHILE);
        match(LPAREN);
        Expr();
        match(RPAREN);
        Stmt2();
        break;
    case SWITCH:
        // Stmt2 ::= switch ( Expr ) { CaseBlock }
        match(SWITCH);
        match(LPAREN);
        Expr();
        match(RPAREN);
        match(LBRACE);
        CaseBlock();
        match(RBRACE);
        break;
    case BREAK:
        // Stmt2 ::= break ;
        match(BREAK);
        match(SEMICOLON);
        break;
    case PRINT:
        // Stmt2 ::= print ( ExprList ) ;
        match(PRINT);
        match(LPAREN);
        ExprList();
        match(RPAREN);
        match(SEMICOLON);
        break;
    case READLN:
        // Stmt2 ::= readln ( Expr ) ;
        match(READLN);
        match(LPAREN);
        Expr();
        match(RPAREN);
        match(SEMICOLON);
        break;
    case RETURN:
        // Stmt2 ::= return Expr ;
        match(RETURN);
        Expr();
        match(SEMICOLON);
        break;
    case THROW:
        // Stmt2 ::= throw ;
        match(THROW);
        match(SEMICOLON);
        break;
    case TRY:
        // Stmt2 ::= try Stmt2 catch ( ... ) Stmt2
        match(TRY);
        Stmt2();
        match(CATCH);
        match(LPAREN);
        match(TRIPLE_DOT);
        match(RPAREN);
        Stmt2();
        break;
    default:
        error(lookAhead, sync_Stmt2);
    }
}

int RDParser::sync_IfOpt[] = {RBRACE, IF, WHILE, SWITCH, BREAK, PRINT, READLN, RETURN, THROW, LBRACE, TRY, NUM_INT, NUM_REAL, LITERAL, ASCII, LPAREN, TRUE, FALSE, AMP, MULT, MINUS, SUM, EXCLAMATION, ID, CATCH, CASE, SEMICOLON, END_OF_FILE};
void RDParser::IfOpt()
{
    switch (lookAhead)
    {
    case ID:
    case NUM_INT:
    case LBRACE:
    case SEMICOLON:
    case RBRACE:
    case MULT:
    case LPAREN:
    case CASE:
    case IF:
    case WHILE:
    case SWITCH:
    case BREAK:
    case PRINT:
    case READLN:
    case RETURN:
    case THROW:
    case TRY:
    case CATCH:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
    case AMP:
    case SUM:
    case MINUS:
    case EXCLAMATION:
        // IfOpt ::= ε
        break;
    case ELSE:
        // IfOpt ::= else ElseOpt
        match(ELSE);
        ElseOpt();
        break;
    default:
        error(lookAhead, sync_IfOpt);
    }
}

int RDParser::sync_ElseOpt[] = {RBRACE, IF, WHILE, SWITCH, BREAK, PRINT, READLN, RETURN, THROW, LBRACE, TRY, NUM_INT, NUM_REAL, LITERAL, ASCII, LPAREN, TRUE, FALSE, AMP, MULT, MINUS, SUM, EXCLAMATION, ID, CATCH, CASE, SEMICOLON, END_OF_FILE};
void RDParser::ElseOpt()
{
    switch (lookAhead)
    {
    case LBRACE:
        // ElseOpt ::= { Stmt2 }
        match(LBRACE);
        Stmt2();
        match(RBRACE);
        break;
    case IF:
        // ElseOpt ::= if ( Expr ) { Stmt2 } IfOpt
        match(IF);
        match(LPAREN);
        Expr();
        match(RPAREN);
        match(LBRACE);
        Stmt2();
        match(RBRACE);
        IfOpt();
        break;
    default:
        error(lookAhead, sync_ElseOpt);
    }
}

int RDParser::sync_ExpSemID[] = {SEMICOLON, END_OF_FILE};
void RDParser::ExpSemID()
{
    switch (lookAhead)
    {
    case NUM_INT:
        // ExpSemID ::= integer ExpSemIDL
        match(NUM_INT);
        ExpSemIDL();
        break;
    case MULT:
        // ExpSemID ::= * id ExpSemIDL
        match(MULT);
        match(ID);
        ExpSemIDL();
        break;
    case LPAREN:
        // ExpSemID ::= ( Expr ) ExpSemIDL
        match(LPAREN);
        Expr();
        match(RPAREN);
        ExpSemIDL();
        break;
    case NUM_REAL:
        // ExpSemID ::= real ExpSemIDL
        match(NUM_REAL);
        ExpSemIDL();
        break;
    case LITERAL:
        // ExpSemID ::= literal ExpSemIDL
        match(LITERAL);
        ExpSemIDL();
        break;
    case ASCII:
        // ExpSemID ::= ascii ExpSemIDL
        match(ASCII);
        ExpSemIDL();
        break;
    case TRUE:
        // ExpSemID ::= true ExpSemIDL
        match(TRUE);
        ExpSemIDL();
        break;
    case FALSE:
        // ExpSemID ::= false ExpSemIDL
        match(FALSE);
        ExpSemIDL();
        break;
    case AMP:
        // ExpSemID ::= & id ExpSemIDL
        match(AMP);
        match(ID);
        ExpSemIDL();
        break;
    default:
        error(lookAhead, sync_ExpSemID);
    }
}

int RDParser::sync_ExpSemIDL[] = {SEMICOLON, END_OF_FILE};
void RDParser::ExpSemIDL()
{
    switch (lookAhead)
    {
    case ID:
    case NUM_INT:
    case MULT:
    case LPAREN:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
    case AMP:
    case SUM:
    case MINUS:
    case EXCLAMATION:
        // ExpSemIDL ::= Expr
        Expr();
        break;
    case SEMICOLON:
        // ExpSemIDL ::= ε
        break;
    default:
        error(lookAhead, sync_ExpSemIDL);
    }
}

int RDParser::sync_Expr[] = {SEMICOLON, RBRACKET, RPAREN, COMMA, END_OF_FILE};
void RDParser::Expr()
{
    switch (lookAhead)
    {
    case ID:
    case NUM_INT:
    case MULT:
    case LPAREN:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
    case AMP:
    case SUM:
    case MINUS:
    case EXCLAMATION:
        // Expr ::= Expr1 ExprL
        Expr1();
        ExprL();
        break;
    default:
        error(lookAhead, sync_Expr);
    }
}

int RDParser::sync_ExprL[] = {SEMICOLON, RBRACKET, RPAREN, COMMA, END_OF_FILE};
void RDParser::ExprL()
{
    switch (lookAhead)
    {
    case COMMA:
    case RBRACKET:
    case SEMICOLON:
    case RPAREN:
        // ExprL ::= ε
        break;
    case ASSIGN:
        // ExprL ::= = Expr
        match(ASSIGN);
        Expr();
        break;
    default:
        error(lookAhead, sync_ExprL);
    }
}

int RDParser::sync_Expr1[] = {SEMICOLON, RBRACKET, RPAREN, COMMA, ASSIGN, END_OF_FILE};
void RDParser::Expr1()
{
    switch (lookAhead)
    {
    case ID:
    case NUM_INT:
    case MULT:
    case LPAREN:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
    case AMP:
    case SUM:
    case MINUS:
    case EXCLAMATION:
        // Expr1 ::= Expr2 Expr1L
        Expr2();
        Expr1L();
        break;
    default:
        error(lookAhead, sync_Expr1);
    }
}

int RDParser::sync_Expr1L[] = {SEMICOLON, RBRACKET, RPAREN, COMMA, ASSIGN, END_OF_FILE};
void RDParser::Expr1L()
{
    switch (lookAhead)
    {
    case COMMA:
    case RBRACKET:
    case SEMICOLON:
    case RPAREN:
    case ASSIGN:
        // Expr1L ::= ε
        break;
    case OR:
        // Expr1L ::= || Expr1
        match(OR);
        Expr1();
        break;
    default:
        error(lookAhead, sync_Expr1L);
    }
}

int RDParser::sync_Expr2[] = {SEMICOLON, RBRACKET, RPAREN, COMMA, ASSIGN, OR, END_OF_FILE};
void RDParser::Expr2()
{
    switch (lookAhead)
    {
    case ID:
    case NUM_INT:
    case MULT:
    case LPAREN:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
    case AMP:
    case SUM:
    case MINUS:
    case EXCLAMATION:
        // Expr2 ::= Expr3 Expr2L
        Expr3();
        Expr2L();
        break;
    default:
        error(lookAhead, sync_Expr2);
    }
}

int RDParser::sync_Expr2L[] = {SEMICOLON, RBRACKET, RPAREN, COMMA, ASSIGN, OR, END_OF_FILE};
void RDParser::Expr2L()
{
    switch (lookAhead)
    {
    case COMMA:
    case RBRACKET:
    case SEMICOLON:
    case RPAREN:
    case ASSIGN:
    case OR:
        // Expr2L ::= ε
        break;
    case AND:
        // Expr2L ::= && Expr2
        match(AND);
        Expr2();
        break;
    default:
        error(lookAhead, sync_Expr2L);
    }
}

int RDParser::sync_Expr3[] = {SEMICOLON, RBRACKET, RPAREN, COMMA, ASSIGN, OR, AND, END_OF_FILE};
void RDParser::Expr3()
{
    switch (lookAhead)
    {
    case ID:
    case NUM_INT:
    case MULT:
    case LPAREN:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
    case AMP:
    case SUM:
    case MINUS:
    case EXCLAMATION:
        // Expr3 ::= Expr4 Expr3L
        Expr4();
        Expr3L();
        break;
    default:
        error(lookAhead, sync_Expr3);
    }
}

int RDParser::sync_Expr3L[] = {SEMICOLON, RBRACKET, RPAREN, COMMA, ASSIGN, OR, AND, END_OF_FILE};
void RDParser::Expr3L()
{
    switch (lookAhead)
    {
    case COMMA:
    case RBRACKET:
    case SEMICOLON:
    case RPAREN:
    case ASSIGN:
    case OR:
    case AND:
        // Expr3L ::= ε
        break;
    case EQUAL:
        // Expr3L ::= == Expr3
        match(EQUAL);
        Expr3();
        break;
    case NOT_EQUAL:
        // Expr3L ::= != Expr3
        match(NOT_EQUAL);
        Expr3();
        break;
    default:
        error(lookAhead, sync_Expr3L);
    }
}

int RDParser::sync_Expr4[] = {SEMICOLON, RBRACKET, RPAREN, COMMA, ASSIGN, OR, AND, EQUAL, NOT_EQUAL, END_OF_FILE};
void RDParser::Expr4()
{
    switch (lookAhead)
    {
    case ID:
    case NUM_INT:
    case MULT:
    case LPAREN:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
    case AMP:
    case SUM:
    case MINUS:
    case EXCLAMATION:
        // Expr4 ::= Expr5 Expr4L
        Expr5();
        Expr4L();
        break;
    default:
        error(lookAhead, sync_Expr4);
    }
}

int RDParser::sync_Expr4L[] = {SEMICOLON, RBRACKET, RPAREN, COMMA, ASSIGN, OR, AND, EQUAL, NOT_EQUAL, END_OF_FILE};
void RDParser::Expr4L()
{
    switch (lookAhead)
    {
    case COMMA:
    case RBRACKET:
    case SEMICOLON:
    case RPAREN:
    case ASSIGN:
    case OR:
    case AND:
    case EQUAL:
    case NOT_EQUAL:
        // Expr4L ::= ε
        break;
    case LE:
        // Expr4L ::= < Expr4
        match(LE);
        Expr4();
        break;
    case LEQ:
        // Expr4L ::= <= Expr4
        match(LEQ);
        Expr4();
        break;
    case GTE:
        // Expr4L ::= >= Expr4
        match(GTE);
        Expr4();
        break;
    case GT:
        // Expr4L ::= > Expr4
        match(GT);
        Expr4();
        break;
    default:
        error(lookAhead, sync_Expr4L);
    }
}

int RDParser::sync_Expr5[] = {SEMICOLON, RBRACKET, RPAREN, COMMA, ASSIGN, OR, AND, EQUAL, NOT_EQUAL, LE, LEQ, GTE, GT, END_OF_FILE};
void RDParser::Expr5()
{
    switch (lookAhead)
    {
    case ID:
    case NUM_INT:
    case MULT:
    case LPAREN:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
    case AMP:
    case SUM:
    case MINUS:
    case EXCLAMATION:
        // Expr5 ::= Expr6 Expr5L
        Expr6();
        Expr5L();
        break;
    default:
        error(lookAhead, sync_Expr5);
    }
}

int RDParser::sync_Expr5L[] = {SEMICOLON, RBRACKET, RPAREN, COMMA, ASSIGN, OR, AND, EQUAL, NOT_EQUAL, LE, LEQ, GTE, GT, END_OF_FILE};
void RDParser::Expr5L()
{
    switch (lookAhead)
    {
    case COMMA:
    case RBRACKET:
    case SEMICOLON:
    case RPAREN:
    case ASSIGN:
    case OR:
    case AND:
    case EQUAL:
    case NOT_EQUAL:
    case LE:
    case LEQ:
    case GTE:
    case GT:
        // Expr5L ::= ε
        break;
    case SUM:
        // Expr5L ::= + Expr5
        match(SUM);
        Expr5();
        break;
    case MINUS:
        // Expr5L ::= - Expr5
        match(MINUS);
        Expr5();
        break;
    case VERBAR:
        // Expr5L ::= | Expr5
        match(VERBAR);
        Expr5();
        break;
    default:
        error(lookAhead, sync_Expr5L);
    }
}

int RDParser::sync_Expr6[] = {SEMICOLON, RBRACKET, RPAREN, COMMA, ASSIGN, OR, AND, EQUAL, NOT_EQUAL, LE, LEQ, GTE, GT, SUM, MINUS, VERBAR, END_OF_FILE};
void RDParser::Expr6()
{
    switch (lookAhead)
    {
    case ID:
    case NUM_INT:
    case MULT:
    case LPAREN:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
    case AMP:
    case SUM:
    case MINUS:
    case EXCLAMATION:
        // Expr6 ::= Expr7 Expr6L
        Expr7();
        Expr6L();
        break;
    default:
        error(lookAhead, sync_Expr6);
    }
}

int RDParser::sync_Expr6L[] = {SEMICOLON, RBRACKET, RPAREN, COMMA, ASSIGN, OR, AND, EQUAL, NOT_EQUAL, LE, LEQ, GTE, GT, SUM, MINUS, VERBAR, END_OF_FILE};
void RDParser::Expr6L()
{
    switch (lookAhead)
    {
    case COMMA:
    case RBRACKET:
    case SEMICOLON:
    case RPAREN:
    case ASSIGN:
    case OR:
    case AND:
    case EQUAL:
    case NOT_EQUAL:
    case LE:
    case LEQ:
    case GTE:
    case GT:
    case SUM:
    case MINUS:
    case VERBAR:
        // Expr6L ::= ε
        break;
    case MULT:
        // Expr6L ::= * Expr6
        match(MULT);
        Expr6();
        break;
    case AMP:
        // Expr6L ::= & Expr6
        match(AMP);
        Expr6();
        break;
    case DIV:
        // Expr6L ::= / Expr6
        match(DIV);
        Expr6();
        break;
    case MOD:
        // Expr6L ::= % Expr6
        match(MOD);
        Expr6();
        break;
    default:
        error(lookAhead, sync_Expr6L);
    }
}

int RDParser::sync_Expr7[] = {SEMICOLON, RBRACKET, RPAREN, COMMA, ASSIGN, OR, AND, EQUAL, NOT_EQUAL, LE, LEQ, GTE, GT, SUM, MINUS, VERBAR, MULT, DIV, MOD, AMP, END_OF_FILE};
void RDParser::Expr7()
{
    switch (lookAhead)
    {
    case ID:
    case NUM_INT:
    case MULT:
    case LPAREN:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
    case AMP:
        // Expr7 ::= Primary
        Primary();
        break;
    case SUM:
        // Expr7 ::= + Expr7
        match(SUM);
        Expr7();
        break;
    case MINUS:
        // Expr7 ::= - Expr7
        match(MINUS);
        Expr7();
        break;
    case EXCLAMATION:
        // Expr7 ::= ! Expr7
        match(EXCLAMATION);
        Expr7();
        break;
    default:
        error(lookAhead, sync_Expr7);
    }
}

int RDParser::sync_Primary[] = {SEMICOLON, RBRACKET, RPAREN, COMMA, ASSIGN, OR, AND, EQUAL, NOT_EQUAL, LE, LEQ, GTE, GT, SUM, MINUS, VERBAR, MULT, DIV, MOD, AMP, END_OF_FILE};
void RDParser::Primary()
{
    switch (lookAhead)
    {
    case ID:
        // Primary ::= id PrimaryL
        match(ID);
        PrimaryL();
        break;
    case NUM_INT:
        // Primary ::= integer
        match(NUM_INT);
        break;
    case MULT:
        // Primary ::= * id
        match(MULT);
        match(ID);
        break;
    case LPAREN:
        // Primary ::= ( Expr )
        match(LPAREN);
        Expr();
        match(RPAREN);
        break;
    case NUM_REAL:
        // Primary ::= real
        match(NUM_REAL);
        break;
    case LITERAL:
        // Primary ::= literal
        match(LITERAL);
        break;
    case ASCII:
        // Primary ::= ascii
        match(ASCII);
        break;
    case TRUE:
        // Primary ::= true
        match(TRUE);
        break;
    case FALSE:
        // Primary ::= false
        match(FALSE);
        break;
    case AMP:
        // Primary ::= & id
        match(AMP);
        match(ID);
        break;
    default:
        error(lookAhead, sync_Primary);
    }
}

int RDParser::sync_PrimaryL[] = {SEMICOLON, RBRACKET, RPAREN, COMMA, ASSIGN, OR, AND, EQUAL, NOT_EQUAL, LE, LEQ, GTE, GT, SUM, MINUS, VERBAR, MULT, DIV, MOD, AMP, END_OF_FILE};
void RDParser::PrimaryL()
{
    switch (lookAhead)
    {
    case COMMA:
    case RBRACKET:
    case SEMICOLON:
    case MULT:
    case RPAREN:
    case ASSIGN:
    case AMP:
    case OR:
    case AND:
    case EQUAL:
    case NOT_EQUAL:
    case LE:
    case LEQ:
    case GTE:
    case GT:
    case SUM:
    case MINUS:
    case VERBAR:
    case DIV:
    case MOD:
        // PrimaryL ::= ε
        break;
    case LBRACKET:
        // PrimaryL ::= [ Expr ]
        match(LBRACKET);
        Expr();
        match(RBRACKET);
        break;
    default:
        error(lookAhead, sync_PrimaryL);
    }
}
