#include "RDParser.h"

RDParser::RDParser()
{
    printf("[DEBUG] *************** Inicializa o parser ***************\n");
}
RDParser::~RDParser() {}

void RDParser::startParser()
{
    nextToken();
    Program();

    program = Program_AST(nullptr, nullptr, nullptr);
    visitor = new Print_AST();
    program->accept(visitor);
    delete (visitor);
}

void RDParser::nextToken()
{
    // Aqui obtem o nextToken do analisador léxico
    lookAhead = getNextToken();
    // printf("lookAhead: %d \n", lookAhead);
    char *tokenName = getTokenName(lookAhead);
    if (tokenName)
    {
        printf("[DEBUG] Token de lookAhead: %s\n", tokenName);
    }
}

void RDParser::match(int token)
{
    if (token != lookAhead)
    {
        writeError(token);
    }
    else
    {
        nextToken();
    }
}

void RDParser::matchOrSkip(int token, const int *syncArr)
{
    if (token != lookAhead)
    {
        writeError(token);
        syncError(syncArr);
    }
    else
    {
        nextToken();
    }
}

static char errorTemplate[] = "Token esperado: ";

void RDParser::writeError(int expectedToken)
{
    char *tokenName = getTokenName(expectedToken);
    int templateLen = 0;
    for (; errorTemplate[templateLen] != '\0'; templateLen++)
        ;
    char *errStr = new char[templateLen + strlen(tokenName)];
    errStr[0] = '\0';
    strcat(errStr, errorTemplate);
    // strcat(errStr, tokenName);
    for (int i = 0; tokenName[i] != '\0'; i++)
    {
        errStr[i + templateLen] = tokenName[i];
    }

    writeSyntaxError(errStr, getSourceCodeLine(), getSourceCodeColumn());
}

void RDParser::syncError(const int *syncArr)
{
    printf("syncError\n");
    int i = 0;
    while (lookAhead != END_OF_FILE)
    {
        while (syncArr[i] != END_OF_FILE)
        {
            if (lookAhead != syncArr[i])
            {
                i++;
            }
            else
            {
                return;
            }
        }
        i = 0;
        nextToken();
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
        writeError(lookAhead);
        syncError(sync_Program);
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
        writeError(lookAhead);
        syncError(sync_Type);
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
        writeError(lookAhead);
        syncError(sync_IdList);
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
        matchOrSkip(NUM_INT, sync_IdListK2);
        matchOrSkip(RBRACKET, sync_IdListK2);
        Array();
        IdListK3();
        break;
    case SEMICOLON:
        // IdListK2 ::= ε
        break;
    default:
        writeError(lookAhead);
        syncError(sync_IdListK2);
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
        writeError(lookAhead);
        syncError(sync_IdListK3);
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
        matchOrSkip(NUM_INT, sync_Array);
        matchOrSkip(RBRACKET, sync_Array);
        Array();
        break;
    default:
        writeError(lookAhead);
        syncError(sync_Array);
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
        matchOrSkip(STRUCT, sync_TypeDecl);
        matchOrSkip(LBRACE, sync_TypeDecl);
        Type();
        IdList();
        matchOrSkip(SEMICOLON, sync_TypeDecl);
        VarDecl();
        matchOrSkip(RBRACE, sync_TypeDecl);
        matchOrSkip(ID, sync_TypeDecl);
        matchOrSkip(SEMICOLON, sync_TypeDecl);
        break;
    default:
        writeError(lookAhead);
        syncError(sync_TypeDecl);
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
        writeError(lookAhead);
        syncError(sync_VarFn);
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
        matchOrSkip(ID, sync_VarFnK);
        VarFnL();
        break;
    default:
        writeError(lookAhead);
        syncError(sync_VarFnK);
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
        writeError(lookAhead);
        syncError(sync_VarFnL);
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
        writeError(lookAhead);
        syncError(sync_VarDecl);
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
        matchOrSkip(SEMICOLON, sync_VarDeclK);
        VarDecl();
        break;
    default:
        writeError(lookAhead);
        syncError(sync_VarDeclK);
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
        writeError(lookAhead);
        syncError(sync_FunctionDecl);
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
        matchOrSkip(ID, sync_FunctionDeclK);
        FunctionDeclL();
        break;
    default:
        writeError(lookAhead);
        syncError(sync_FunctionDeclK);
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
        matchOrSkip(RPAREN, sync_FunctionDeclL);
        matchOrSkip(LBRACE, sync_FunctionDeclL);
        FunctionBody();
        matchOrSkip(RBRACE, sync_FunctionDeclL);
        break;
    default:
        writeError(lookAhead);
        syncError(sync_FunctionDeclL);
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
        writeError(lookAhead);
        syncError(sync_FormalRest);
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
        matchOrSkip(ID, sync_FormalRestK);
        Array();
        FormalRest();
        break;
    default:
        writeError(lookAhead);
        syncError(sync_FormalRestK);
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
        writeError(lookAhead);
        syncError(sync_FormalList);
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
        matchOrSkip(ID, sync_FormalListK);
        Array();
        FormalRest();
        break;
    default:
        writeError(lookAhead);
        syncError(sync_FormalListK);
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
        matchOrSkip(SEMICOLON, sync_FunctionBody);
        FunctionBody();
        break;
    case LONG:
        // FunctionBody ::= long IdList ; FunctionBody
        match(LONG);
        IdList();
        matchOrSkip(SEMICOLON, sync_FunctionBody);
        FunctionBody();
        break;
    case FLOAT:
        // FunctionBody ::= float IdList ; FunctionBody
        match(FLOAT);
        IdList();
        matchOrSkip(SEMICOLON, sync_FunctionBody);
        FunctionBody();
        break;
    case BOOL:
        // FunctionBody ::= bool IdList ; FunctionBody
        match(BOOL);
        IdList();
        matchOrSkip(SEMICOLON, sync_FunctionBody);
        FunctionBody();
        break;
    case CHAR:
        // FunctionBody ::= char IdList ; FunctionBody
        match(CHAR);
        IdList();
        matchOrSkip(SEMICOLON, sync_FunctionBody);
        FunctionBody();
        break;
    case DOUBLE:
        // FunctionBody ::= double IdList ; FunctionBody
        match(DOUBLE);
        IdList();
        matchOrSkip(SEMICOLON, sync_FunctionBody);
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
        writeError(lookAhead);
        syncError(sync_FunctionBody);
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
        matchOrSkip(RBRACKET, sync_FunctionBodyL);
        matchOrSkip(SEMICOLON, sync_FunctionBodyL);
        FunctionBody();
        break;
    case RBRACE:
        // FunctionBodyL ::= ε
        break;
    case LPAREN:
        // FunctionBodyL ::= ( ExprList ) ; FunctionBody
        match(LPAREN);
        ExprList();
        matchOrSkip(RPAREN, sync_FunctionBodyL);
        matchOrSkip(SEMICOLON, sync_FunctionBodyL);
        FunctionBody();
        break;
    case DOT:
        // FunctionBodyL ::= . Expr ; FunctionBody
        match(DOT);
        Expr();
        matchOrSkip(SEMICOLON, sync_FunctionBodyL);
        FunctionBody();
        break;
    case POINTER:
        // FunctionBodyL ::= -> Expr ; FunctionBody
        match(POINTER);
        Expr();
        matchOrSkip(SEMICOLON, sync_FunctionBodyL);
        FunctionBody();
        break;
    case ASSIGN:
        // FunctionBodyL ::= = StmtList2K ; FunctionBody
        match(ASSIGN);
        StmtList2K();
        matchOrSkip(SEMICOLON, sync_FunctionBodyL);
        FunctionBody();
        break;
    default:
        writeError(lookAhead);
        syncError(sync_FunctionBodyL);
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
        writeError(lookAhead);
        syncError(sync_ExprList);
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
        writeError(lookAhead);
        syncError(sync_ExprListTail);
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
        writeError(lookAhead);
        syncError(sync_ExprListTailL);
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
        writeError(lookAhead);
        syncError(sync_StmtList);
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
        writeError(lookAhead);
        syncError(sync_StmtListK);
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
        writeError(lookAhead);
        syncError(sync_StmtList2);
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
        writeError(lookAhead);
        syncError(sync_StmtList2K);
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
        matchOrSkip(NUM_INT, sync_CaseBlock);
        matchOrSkip(COLON, sync_CaseBlock);
        CaseBlockL();
        break;
    default:
        writeError(lookAhead);
        syncError(sync_CaseBlock);
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
        writeError(lookAhead);
        syncError(sync_CaseBlockL);
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
        matchOrSkip(SEMICOLON, sync_Stmt);
        break;
    case LBRACE:
        // Stmt ::= { StmtList2 }
        match(LBRACE);
        StmtList2();
        matchOrSkip(RBRACE, sync_Stmt);
        break;
    case IF:
        // Stmt ::= if ( Expr ) { Stmt2 } IfOpt
        match(IF);
        matchOrSkip(LPAREN, sync_Stmt);
        Expr();
        matchOrSkip(RPAREN, sync_Stmt);
        matchOrSkip(LBRACE, sync_Stmt);
        Stmt2();
        matchOrSkip(RBRACE, sync_Stmt);
        IfOpt();
        break;
    case WHILE:
        // Stmt ::= while ( Expr ) Stmt2
        match(WHILE);
        matchOrSkip(LPAREN, sync_Stmt);
        Expr();
        matchOrSkip(RPAREN, sync_Stmt);
        Stmt2();
        break;
    case SWITCH:
        // Stmt ::= switch ( Expr ) { CaseBlock }
        match(SWITCH);
        matchOrSkip(LPAREN, sync_Stmt);
        Expr();
        matchOrSkip(RPAREN, sync_Stmt);
        matchOrSkip(LBRACE, sync_Stmt);
        CaseBlock();
        matchOrSkip(RBRACE, sync_Stmt);
        break;
    case BREAK:
        // Stmt ::= break ;
        match(BREAK);
        match(SEMICOLON);
        break;
    case PRINT:
        // Stmt ::= print ( ExprList ) ;
        match(PRINT);
        matchOrSkip(LPAREN, sync_Stmt);
        ExprList();
        matchOrSkip(RPAREN, sync_Stmt);
        matchOrSkip(SEMICOLON, sync_Stmt);
        break;
    case READLN:
        // Stmt ::= readln ( Expr ) ;
        match(READLN);
        matchOrSkip(LPAREN, sync_Stmt);
        Expr();
        matchOrSkip(RPAREN, sync_Stmt);
        matchOrSkip(SEMICOLON, sync_Stmt);
        break;
    case RETURN:
        // Stmt ::= return Expr ;
        match(RETURN);
        Expr();
        // matchOrSkip(SEMICOLON, sync_Stmt);
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
        matchOrSkip(CATCH, sync_Stmt);
        matchOrSkip(LPAREN, sync_Stmt);
        matchOrSkip(TRIPLE_DOT, sync_Stmt);
        matchOrSkip(RPAREN, sync_Stmt);
        Stmt2();
        break;
    default:
        writeError(lookAhead);
        syncError(sync_Stmt);
    }
}

int RDParser::sync_Stmt2[] = {IF, RBRACE, WHILE, SWITCH, BREAK, PRINT, READLN, RETURN, THROW, LBRACE, TRY, MINUS, SUM, EXCLAMATION, ID, NUM_INT, NUM_REAL, LITERAL, ASCII, LPAREN, TRUE, FALSE, AMP, MULT, RBRACE, CATCH, SEMICOLON, CASE, END_OF_FILE};
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
        matchOrSkip(SEMICOLON, sync_Stmt2);
        break;
    case LBRACE:
        // Stmt2 ::= { StmtList2 }
        match(LBRACE);
        StmtList2();
        matchOrSkip(RBRACE, sync_Stmt2);
        break;
    case IF:
        // Stmt2 ::= if ( Expr ) { Stmt2 } IfOpt
        match(IF);
        matchOrSkip(LPAREN, sync_Stmt2);
        Expr();
        matchOrSkip(RPAREN, sync_Stmt2);
        matchOrSkip(LBRACE, sync_Stmt2);
        Stmt2();
        matchOrSkip(RBRACE, sync_Stmt2);
        IfOpt();
        break;
    case WHILE:
        // Stmt2 ::= while ( Expr ) Stmt2
        match(WHILE);
        matchOrSkip(LPAREN, sync_Stmt2);
        Expr();
        matchOrSkip(RPAREN, sync_Stmt2);
        Stmt2();
        break;
    case SWITCH:
        // Stmt2 ::= switch ( Expr ) { CaseBlock }
        match(SWITCH);
        matchOrSkip(LPAREN, sync_Stmt2);
        Expr();
        matchOrSkip(RPAREN, sync_Stmt2);
        matchOrSkip(LBRACE, sync_Stmt2);
        CaseBlock();
        matchOrSkip(RBRACE, sync_Stmt2);
        break;
    case BREAK:
        // Stmt2 ::= break ;
        match(BREAK);
        matchOrSkip(SEMICOLON, sync_Stmt2);
        break;
    case PRINT:
        // Stmt2 ::= print ( ExprList ) ;
        match(PRINT);
        matchOrSkip(LPAREN, sync_Stmt2);
        ExprList();
        matchOrSkip(RPAREN, sync_Stmt2);
        matchOrSkip(SEMICOLON, sync_Stmt2);
        break;
    case READLN:
        // Stmt2 ::= readln ( Expr ) ;
        match(READLN);
        matchOrSkip(LPAREN, sync_Stmt2);
        Expr();
        matchOrSkip(RPAREN, sync_Stmt2);
        matchOrSkip(SEMICOLON, sync_Stmt2);
        break;
    case RETURN:
        // Stmt2 ::= return Expr ;
        match(RETURN);
        Expr();
        // matchOrSkip(SEMICOLON, sync_Stmt2);
        break;
    case THROW:
        // Stmt2 ::= throw ;
        match(THROW);
        matchOrSkip(SEMICOLON, sync_Stmt2);
        break;
    case TRY:
        // Stmt2 ::= try Stmt2 catch ( ... ) Stmt2
        match(TRY);
        Stmt2();
        matchOrSkip(CATCH, sync_Stmt2);
        matchOrSkip(LPAREN, sync_Stmt2);
        matchOrSkip(TRIPLE_DOT, sync_Stmt2);
        matchOrSkip(RPAREN, sync_Stmt2);
        Stmt2();
        break;
    default:
        writeError(lookAhead);
        syncError(sync_Stmt2);
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
        writeError(lookAhead);
        syncError(sync_IfOpt);
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
        matchOrSkip(RBRACE, sync_ElseOpt);
        break;
    case IF:
        // ElseOpt ::= if ( Expr ) { Stmt2 } IfOpt
        match(IF);
        matchOrSkip(LPAREN, sync_ElseOpt);
        Expr();
        matchOrSkip(RPAREN, sync_ElseOpt);
        matchOrSkip(LBRACE, sync_ElseOpt);
        Stmt2();
        matchOrSkip(RBRACE, sync_ElseOpt);
        IfOpt();
        break;
    default:
        writeError(lookAhead);
        syncError(sync_ElseOpt);
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
        matchOrSkip(ID, sync_ExpSemID);
        ExpSemIDL();
        break;
    case LPAREN:
        // ExpSemID ::= ( Expr ) ExpSemIDL
        match(LPAREN);
        Expr();
        matchOrSkip(RPAREN, sync_ExpSemID);
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
        matchOrSkip(ID, sync_ExpSemID);
        ExpSemIDL();
        break;
    default:
        writeError(lookAhead);
        syncError(sync_ExpSemID);
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
        writeError(lookAhead);
        syncError(sync_ExpSemIDL);
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
        writeError(lookAhead);
        syncError(sync_Expr);
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
        writeError(lookAhead);
        syncError(sync_ExprL);
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
        writeError(lookAhead);
        syncError(sync_Expr1);
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
        writeError(lookAhead);
        syncError(sync_Expr1L);
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
        writeError(lookAhead);
        syncError(sync_Expr2);
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
        writeError(lookAhead);
        syncError(sync_Expr2L);
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
        writeError(lookAhead);
        syncError(sync_Expr3);
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
        writeError(lookAhead);
        syncError(sync_Expr3L);
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
        writeError(lookAhead);
        syncError(sync_Expr4);
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
        writeError(lookAhead);
        syncError(sync_Expr4L);
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
        writeError(lookAhead);
        syncError(sync_Expr5);
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
        writeError(lookAhead);
        syncError(sync_Expr5L);
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
        writeError(lookAhead);
        syncError(sync_Expr6);
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
        writeError(lookAhead);
        syncError(sync_Expr6L);
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
        writeError(lookAhead);
        syncError(sync_Expr7);
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
        matchOrSkip(ID, sync_Primary);
        break;
    case LPAREN:
        // Primary ::= ( Expr )
        match(LPAREN);
        Expr();
        matchOrSkip(RPAREN, sync_Primary);
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
        matchOrSkip(ID, sync_Primary);
        break;
    default:
        writeError(lookAhead);
        syncError(sync_Primary);
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
        matchOrSkip(RBRACKET, sync_PrimaryL);
        break;
    default:
        writeError(lookAhead);
        syncError(sync_PrimaryL);
    }
}
