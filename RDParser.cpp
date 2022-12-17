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
    printf("Token de lookAhead: %s\n", tokenName);
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



void RDParser::Program()
{
    switch (lookAhead)
    {
        case END_OF_FILE:
            //Program ::= ε
            break;
        case ID:
        case INTEGER:
        case LONG:
        case REAL:
        case BOOL:
        case CHAR:
        case DOUBLE:
            //Program ::= VarFn Program
            VarFn();
            Program();
            break;
        case TYPEDEF:
            //Program ::= TypeDecl Program
            TypeDecl();
            Program();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::Type()
{
    switch (lookAhead)
    {
        case ID:
            //Type ::= id
            match(ID);
            break;
        case INTEGER:
            //Type ::= int
            match(INTEGER);
            break;
        case LONG:
            //Type ::= long
            match(LONG);
            break;
        case REAL:
            //Type ::= float
            match(REAL);
            break;
        case BOOL:
            //Type ::= bool
            match(BOOL);
            break;
        case CHAR:
            //Type ::= char
            match(CHAR);
            break;
        case DOUBLE:
            //Type ::= double
            match(DOUBLE);
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::IdList()
{
    switch (lookAhead)
    {
        case ID:
            //IdList ::= id IdListK2
            match(ID);
            IdListK2();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::IdListK2()
{
    switch (lookAhead)
    {
        case COMMA:
            //IdListK2 ::= , IdList
            match(COMMA);
            IdList();
            break;
        case LBRACKET:
            //IdListK2 ::= [ num ] Array IdListK3
            match(LBRACKET);
            match(NUM);
            match(RBRACKET);
            Array();
            IdListK3();
            break;
        case SEMICOLON:
            //IdListK2 ::= ε
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::IdListK3()
{
    switch (lookAhead)
    {
        case COMMA:
            //IdListK3 ::= , IdList
            match(COMMA);
            IdList();
            break;
        case SEMICOLON:
            //IdListK3 ::= ε
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::Array()
{
    switch (lookAhead)
    {
        case COMMA:
        case SEMICOLON:
        case RPAREN:
            //Array ::= ε
            break;
        case LBRACKET:
            //Array ::= [ num ] Array
            match(LBRACKET);
            match(NUM);
            match(RBRACKET);
            Array();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::TypeDecl()
{
    switch (lookAhead)
    {
        case TYPEDEF:
            //TypeDecl ::= typedef struct { Type IdList ; VarDecl } id ;
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
            printf("Syntax Error\n");
    }
}
void RDParser::VarFn()
{
    switch (lookAhead)
    {
        case ID:
        case INTEGER:
        case LONG:
        case REAL:
        case BOOL:
        case CHAR:
        case DOUBLE:
            //VarFn ::= Type VarFnK
            Type();
            VarFnK();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::VarFnK()
{
    switch (lookAhead)
    {
        case ID:
            //VarFnK ::= id VarFnL
            match(ID);
            VarFnL();
            break;
        case MULT:
            //VarFnK ::= * id VarFnL
            match(MULT);
            match(ID);
            VarFnL();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::VarFnL()
{
    switch (lookAhead)
    {
        case COMMA:
        case LBRACKET:
        case SEMICOLON:
            //VarFnL ::= IdListK2 ;
            IdListK2();
            match(SEMICOLON);
            break;
        case LPAREN:
            //VarFnL ::= FunctionDeclL
            FunctionDeclL();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::VarDecl()
{
    switch (lookAhead)
    {
        case ID:
        case INTEGER:
        case LONG:
        case REAL:
        case BOOL:
        case CHAR:
        case DOUBLE:
            //VarDecl ::= Type VarDeclK
            Type();
            VarDeclK();
            break;
        case RBRACE:
            //VarDecl ::= ε
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::VarDeclK()
{
    switch (lookAhead)
    {
        case ID:
            //VarDeclK ::= IdList ; VarDecl
            IdList();
            match(SEMICOLON);
            VarDecl();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::FunctionDecl()
{
    switch (lookAhead)
    {
        case ID:
        case INTEGER:
        case LONG:
        case REAL:
        case BOOL:
        case CHAR:
        case DOUBLE:
            //FunctionDecl ::= Type FunctionDeclK
            Type();
            FunctionDeclK();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::FunctionDeclK()
{
    switch (lookAhead)
    {
        case ID:
            //FunctionDeclK ::= id FunctionDeclL
            match(ID);
            FunctionDeclL();
            break;
        case MULT:
            //FunctionDeclK ::= * id FunctionDeclL
            match(MULT);
            match(ID);
            FunctionDeclL();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::FunctionDeclL()
{
    switch (lookAhead)
    {
        case LPAREN:
            //FunctionDeclL ::= ( FormalList ) { FunctionBody }
            match(LPAREN);
            FormalList();
            match(RPAREN);
            match(LBRACE);
            FunctionBody();
            match(RBRACE);
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::FormalRest()
{
    switch (lookAhead)
    {
        case COMMA:
            //FormalRest ::= , Type FormalRestK
            match(COMMA);
            Type();
            FormalRestK();
            break;
        case RPAREN:
            //FormalRest ::= ε
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::FormalRestK()
{
    switch (lookAhead)
    {
        case ID:
            //FormalRestK ::= id Array FormalRest
            match(ID);
            Array();
            FormalRest();
            break;
        case MULT:
            //FormalRestK ::= * id Array FormalRest
            match(MULT);
            match(ID);
            Array();
            FormalRest();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::FormalList()
{
    switch (lookAhead)
    {
        case ID:
        case INTEGER:
        case LONG:
        case REAL:
        case BOOL:
        case CHAR:
        case DOUBLE:
            //FormalList ::= Type FormalListK
            Type();
            FormalListK();
            break;
        case RPAREN:
            //FormalList ::= ε
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::FormalListK()
{
    switch (lookAhead)
    {
        case ID:
            //FormalListK ::= id Array FormalRest
            match(ID);
            Array();
            FormalRest();
            break;
        case MULT:
            //FormalListK ::= * id Array FormalRest
            match(MULT);
            match(ID);
            Array();
            FormalRest();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::FunctionBody()
{
    switch (lookAhead)
    {
        case ID:
            //FunctionBody ::= id FunctionBodyL
            match(ID);
            FunctionBodyL();
            break;
        case NUM:
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
        case SUM:
        case MINUS:
        case AMP:
        case EXCLAMATION:
        case LITERAL:
        case ASCII:
        case TRUE:
        case FALSE:
            //FunctionBody ::= StmtList
            StmtList();
            break;
        case RBRACE:
            //FunctionBody ::= ε
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::FunctionBodyL()
{
    switch (lookAhead)
    {
        case ID:
            //FunctionBodyL ::= IdList ; FunctionBody
            IdList();
            match(SEMICOLON);
            FunctionBody();
            break;
        case LBRACKET:
        case RBRACE:
        case DOT:
        case POINTER:
        case ASSIGN:
            //FunctionBodyL ::= FunctionBody2L
            FunctionBody2L();
            break;
        case LPAREN:
            //FunctionBodyL ::= ( ExprList ) ; FunctionBody
            match(LPAREN);
            ExprList();
            match(RPAREN);
            match(SEMICOLON);
            FunctionBody();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::FunctionBody2L()
{
    switch (lookAhead)
    {
        case LBRACKET:
            //FunctionBody2L ::= [ Expr ] FunctionBody2L
            match(LBRACKET);
            Expr();
            match(RBRACKET);
            FunctionBody2L();
            break;
        case RBRACE:
            //FunctionBody2L ::= ε
            break;
        case DOT:
            //FunctionBody2L ::= . Expr
            match(DOT);
            Expr();
            break;
        case POINTER:
            //FunctionBody2L ::= -> Expr
            match(POINTER);
            Expr();
            break;
        case ASSIGN:
            //FunctionBody2L ::= = Expr ;
            match(ASSIGN);
            Expr();
            match(SEMICOLON);
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::ExprList()
{
    switch (lookAhead)
    {
        case ID:
        case NUM:
        case MULT:
        case LPAREN:
        case SUM:
        case MINUS:
        case AMP:
        case EXCLAMATION:
        case LITERAL:
        case ASCII:
        case TRUE:
        case FALSE:
            //ExprList ::= ExprListTail
            ExprListTail();
            break;
        case RPAREN:
            //ExprList ::= ε
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::ExprListTail()
{
    switch (lookAhead)
    {
        case ID:
        case NUM:
        case MULT:
        case LPAREN:
        case SUM:
        case MINUS:
        case AMP:
        case EXCLAMATION:
        case LITERAL:
        case ASCII:
        case TRUE:
        case FALSE:
            //ExprListTail ::= Expr ExprListTailL
            Expr();
            ExprListTailL();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::ExprListTailL()
{
    switch (lookAhead)
    {
        case COMMA:
            //ExprListTailL ::= , ExprListTail
            match(COMMA);
            ExprListTail();
            break;
        case RPAREN:
            //ExprListTailL ::= ε
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::StmtList()
{
    switch (lookAhead)
    {
        case NUM:
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
        case SUM:
        case MINUS:
        case AMP:
        case EXCLAMATION:
        case LITERAL:
        case ASCII:
        case TRUE:
        case FALSE:
            //StmtList ::= Stmt StmtListK
            Stmt();
            StmtListK();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::StmtListK()
{
    switch (lookAhead)
    {
        case NUM:
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
        case SUM:
        case MINUS:
        case AMP:
        case EXCLAMATION:
        case LITERAL:
        case ASCII:
        case TRUE:
        case FALSE:
            //StmtListK ::= StmtList
            StmtList();
            break;
        case RBRACE:
        case CASE:
            //StmtListK ::= ε
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::CaseBlock()
{
    switch (lookAhead)
    {
        case CASE:
            //CaseBlock ::= case num : CaseBlockL
            match(CASE);
            match(NUM);
            match(COLON);
            CaseBlockL();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::CaseBlockL()
{
    switch (lookAhead)
    {
        case NUM:
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
        case SUM:
        case MINUS:
        case AMP:
        case EXCLAMATION:
        case LITERAL:
        case ASCII:
        case TRUE:
        case FALSE:
            //CaseBlockL ::= StmtList CaseBlock
            StmtList();
            CaseBlock();
            break;
        case CASE:
            //CaseBlockL ::= CaseBlock
            CaseBlock();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::Stmt()
{
    switch (lookAhead)
    {
        case NUM:
        case MULT:
        case LPAREN:
        case SUM:
        case MINUS:
        case AMP:
        case EXCLAMATION:
        case LITERAL:
        case ASCII:
        case TRUE:
        case FALSE:
            //Stmt ::= ExpSemID ;
            ExpSemID();
            match(SEMICOLON);
            break;
        case LBRACE:
            //Stmt ::= { StmtList }
            match(LBRACE);
            StmtList();
            match(RBRACE);
            break;
        case IF:
            //Stmt ::= if ( Expr ) { Stmt } IfOpt
            match(IF);
            match(LPAREN);
            Expr();
            match(RPAREN);
            match(LBRACE);
            Stmt();
            match(RBRACE);
            IfOpt();
            break;
        case WHILE:
            //Stmt ::= while ( Expr ) Stmt
            match(WHILE);
            match(LPAREN);
            Expr();
            match(RPAREN);
            Stmt();
            break;
        case SWITCH:
            //Stmt ::= switch ( Expr ) { CaseBlock }
            match(SWITCH);
            match(LPAREN);
            Expr();
            match(RPAREN);
            match(LBRACE);
            CaseBlock();
            match(RBRACE);
            break;
        case BREAK:
            //Stmt ::= break ;
            match(BREAK);
            match(SEMICOLON);
            break;
        case PRINT:
            //Stmt ::= print ( ExprList ) ;
            match(PRINT);
            match(LPAREN);
            ExprList();
            match(RPAREN);
            match(SEMICOLON);
            break;
        case READLN:
            //Stmt ::= readln ( Expr ) ;
            match(READLN);
            match(LPAREN);
            Expr();
            match(RPAREN);
            match(SEMICOLON);
            break;
        case RETURN:
            //Stmt ::= return Expr ;
            match(RETURN);
            Expr();
            match(SEMICOLON);
            break;
        case THROW:
            //Stmt ::= throw ;
            match(THROW);
            match(SEMICOLON);
            break;
        case TRY:
            //Stmt ::= try Stmt catch ( ... ) Stmt
            match(TRY);
            Stmt();
            match(CATCH);
            match(LPAREN);
            //match(ERROR [...]);
            match(RPAREN);
            Stmt();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::IfOpt()
{
    switch (lookAhead)
    {
        case NUM:
        case LBRACE:
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
        case SUM:
        case MINUS:
        case AMP:
        case EXCLAMATION:
        case LITERAL:
        case ASCII:
        case TRUE:
        case FALSE:
            //IfOpt ::= ε
            break;
        case ELSE:
            //IfOpt ::= else ElseOpt
            match(ELSE);
            ElseOpt();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::ElseOpt()
{
    switch (lookAhead)
    {
        case LBRACE:
            //ElseOpt ::= { Stmt }
            match(LBRACE);
            Stmt();
            match(RBRACE);
            break;
        case IF:
            //ElseOpt ::= if ( Expr ) { Stmt } IfOpt
            match(IF);
            match(LPAREN);
            Expr();
            match(RPAREN);
            match(LBRACE);
            Stmt();
            match(RBRACE);
            IfOpt();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::Expr()
{
    switch (lookAhead)
    {
        case ID:
        case NUM:
        case MULT:
        case LPAREN:
        case SUM:
        case MINUS:
        case AMP:
        case EXCLAMATION:
        case LITERAL:
        case ASCII:
        case TRUE:
        case FALSE:
            //Expr ::= Expr1 ExprL
            Expr1();
            ExprL();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::ExprL()
{
    switch (lookAhead)
    {
        case COMMA:
        case RBRACKET:
        case SEMICOLON:
        case RBRACE:
        case RPAREN:
            //ExprL ::= ε
            break;
        case ASSIGN:
            //ExprL ::= = Expr
            match(ASSIGN);
            Expr();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::Expr1()
{
    switch (lookAhead)
    {
        case ID:
        case NUM:
        case MULT:
        case LPAREN:
        case SUM:
        case MINUS:
        case AMP:
        case EXCLAMATION:
        case LITERAL:
        case ASCII:
        case TRUE:
        case FALSE:
            //Expr1 ::= Expr2 Expr1L
            Expr2();
            Expr1L();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::Expr1L()
{
    switch (lookAhead)
    {
        case COMMA:
        case RBRACKET:
        case SEMICOLON:
        case RBRACE:
        case RPAREN:
        case ASSIGN:
            //Expr1L ::= ε
            break;
        case OR:
            //Expr1L ::= || Expr1
            match(OR);
            Expr1();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::Expr2()
{
    switch (lookAhead)
    {
        case ID:
        case NUM:
        case MULT:
        case LPAREN:
        case SUM:
        case MINUS:
        case AMP:
        case EXCLAMATION:
        case LITERAL:
        case ASCII:
        case TRUE:
        case FALSE:
            //Expr2 ::= Expr3 Expr2L
            Expr3();
            Expr2L();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::Expr2L()
{
    switch (lookAhead)
    {
        case COMMA:
        case RBRACKET:
        case SEMICOLON:
        case RBRACE:
        case RPAREN:
        case ASSIGN:
        case OR:
            //Expr2L ::= ε
            break;
        case AND:
            //Expr2L ::= && Expr2
            match(AND);
            Expr2();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::Expr3()
{
    switch (lookAhead)
    {
        case ID:
        case NUM:
        case MULT:
        case LPAREN:
        case SUM:
        case MINUS:
        case AMP:
        case EXCLAMATION:
        case LITERAL:
        case ASCII:
        case TRUE:
        case FALSE:
            //Expr3 ::= Expr4 Expr3L
            Expr4();
            Expr3L();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::Expr3L()
{
    switch (lookAhead)
    {
        case COMMA:
        case RBRACKET:
        case SEMICOLON:
        case RBRACE:
        case RPAREN:
        case ASSIGN:
        case OR:
        case AND:
            //Expr3L ::= ε
            break;
        case EQUAL:
            //Expr3L ::= == Expr3
            match(EQUAL);
            Expr3();
            break;
        case NOT_EQUAL:
            //Expr3L ::= != Expr3
            match(NOT_EQUAL);
            Expr3();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::Expr4()
{
    switch (lookAhead)
    {
        case ID:
        case NUM:
        case MULT:
        case LPAREN:
        case SUM:
        case MINUS:
        case AMP:
        case EXCLAMATION:
        case LITERAL:
        case ASCII:
        case TRUE:
        case FALSE:
            //Expr4 ::= Expr5 Expr4L
            Expr5();
            Expr4L();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::Expr4L()
{
    switch (lookAhead)
    {
        case COMMA:
        case RBRACKET:
        case SEMICOLON:
        case RBRACE:
        case RPAREN:
        case ASSIGN:
        case OR:
        case AND:
        case EQUAL:
        case NOT_EQUAL:
            //Expr4L ::= ε
            break;
        case LE:
            //Expr4L ::= < Expr4
            match(LE);
            Expr4();
            break;
        case LEQ:
            //Expr4L ::= <= Expr4
            match(LEQ);
            Expr4();
            break;
        case GTE:
            //Expr4L ::= >= Expr4
            match(GTE);
            Expr4();
            break;
        case GT:
            //Expr4L ::= > Expr4
            match(GT);
            Expr4();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::Expr5()
{
    switch (lookAhead)
    {
        case ID:
        case NUM:
        case MULT:
        case LPAREN:
        case SUM:
        case MINUS:
        case AMP:
        case EXCLAMATION:
        case LITERAL:
        case ASCII:
        case TRUE:
        case FALSE:
            //Expr5 ::= Expr6 Expr5L
            Expr6();
            Expr5L();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::Expr5L()
{
    switch (lookAhead)
    {
        case COMMA:
        case RBRACKET:
        case SEMICOLON:
        case RBRACE:
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
            //Expr5L ::= ε
            break;
        case SUM:
            //Expr5L ::= + Expr5
            match(SUM);
            Expr5();
            break;
        case MINUS:
            //Expr5L ::= - Expr5
            match(MINUS);
            Expr5();
            break;
        case VERBAR:
            //Expr5L ::= | Expr5
            match(VERBAR);
            Expr5();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::Expr6()
{
    switch (lookAhead)
    {
        case ID:
        case NUM:
        case MULT:
        case LPAREN:
        case SUM:
        case MINUS:
        case AMP:
        case EXCLAMATION:
        case LITERAL:
        case ASCII:
        case TRUE:
        case FALSE:
            //Expr6 ::= Expr7 Expr6L
            Expr7();
            Expr6L();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::Expr6L()
{
    switch (lookAhead)
    {
        case COMMA:
        case RBRACKET:
        case SEMICOLON:
        case RBRACE:
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
            //Expr6L ::= ε
            break;
        case MULT:
            //Expr6L ::= * Expr6
            match(MULT);
            Expr6();
            break;
        case DIV:
            //Expr6L ::= / Expr6
            match(DIV);
            Expr6();
            break;
        case MOD:
            //Expr6L ::= % Expr6
            match(MOD);
            Expr6();
            break;
        case AMP:
            //Expr6L ::= & Expr6
            match(AMP);
            Expr6();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::Expr7()
{
    switch (lookAhead)
    {
        case ID:
        case NUM:
        case MULT:
        case LPAREN:
        case AMP:
        case LITERAL:
        case ASCII:
        case TRUE:
        case FALSE:
            //Expr7 ::= Primary
            Primary();
            break;
        case SUM:
            //Expr7 ::= + Expr7
            match(SUM);
            Expr7();
            break;
        case MINUS:
            //Expr7 ::= - Expr7
            match(MINUS);
            Expr7();
            break;
        case EXCLAMATION:
            //Expr7 ::= ! Expr7
            match(EXCLAMATION);
            Expr7();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::Primary()
{
    switch (lookAhead)
    {
        case ID:
            //Primary ::= id
            match(ID);
            break;
        case NUM:
            //Primary ::= num
            match(NUM);
            break;
        case MULT:
            //Primary ::= * id
            match(MULT);
            match(ID);
            break;
        case LPAREN:
            //Primary ::= ( Expr )
            match(LPAREN);
            Expr();
            match(RPAREN);
            break;
        case AMP:
            //Primary ::= & id
            match(AMP);
            match(ID);
            break;
        case LITERAL:
            //Primary ::= literal
            match(LITERAL);
            break;
        case ASCII:
            //Primary ::= ascii
            match(ASCII);
            break;
        case TRUE:
            //Primary ::= true
            match(TRUE);
            break;
        case FALSE:
            //Primary ::= false
            match(FALSE);
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::ExpSemID()
{
    switch (lookAhead)
    {
        case NUM:
        case MULT:
        case LPAREN:
        case SUM:
        case MINUS:
        case AMP:
        case EXCLAMATION:
        case LITERAL:
        case ASCII:
        case TRUE:
        case FALSE:
            //ExpSemID ::= ExpSemID1 ExpSemIDL
            ExpSemID1();
            ExpSemIDL();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::ExpSemIDL()
{
    switch (lookAhead)
    {
        case SEMICOLON:
        case RPAREN:
            //ExpSemIDL ::= ε
            break;
        case ASSIGN:
            //ExpSemIDL ::= = ExpSemID
            match(ASSIGN);
            ExpSemID();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::ExpSemID1()
{
    switch (lookAhead)
    {
        case NUM:
        case MULT:
        case LPAREN:
        case SUM:
        case MINUS:
        case AMP:
        case EXCLAMATION:
        case LITERAL:
        case ASCII:
        case TRUE:
        case FALSE:
            //ExpSemID1 ::= ExpSemID2 ExpSemID1L
            ExpSemID2();
            ExpSemID1L();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::ExpSemID1L()
{
    switch (lookAhead)
    {
        case SEMICOLON:
        case RPAREN:
        case ASSIGN:
            //ExpSemID1L ::= ε
            break;
        case OR:
            //ExpSemID1L ::= || ExpSemID1
            match(OR);
            ExpSemID1();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::ExpSemID2()
{
    switch (lookAhead)
    {
        case NUM:
        case MULT:
        case LPAREN:
        case SUM:
        case MINUS:
        case AMP:
        case EXCLAMATION:
        case LITERAL:
        case ASCII:
        case TRUE:
        case FALSE:
            //ExpSemID2 ::= ExpSemID3 ExpSemID2L
            ExpSemID3();
            ExpSemID2L();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::ExpSemID2L()
{
    switch (lookAhead)
    {
        case SEMICOLON:
        case RPAREN:
        case ASSIGN:
        case OR:
            //ExpSemID2L ::= ε
            break;
        case AND:
            //ExpSemID2L ::= && ExpSemID2
            match(AND);
            ExpSemID2();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::ExpSemID3()
{
    switch (lookAhead)
    {
        case NUM:
        case MULT:
        case LPAREN:
        case SUM:
        case MINUS:
        case AMP:
        case EXCLAMATION:
        case LITERAL:
        case ASCII:
        case TRUE:
        case FALSE:
            //ExpSemID3 ::= ExpSemID4 ExpSemID3L
            ExpSemID4();
            ExpSemID3L();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::ExpSemID3L()
{
    switch (lookAhead)
    {
        case SEMICOLON:
        case RPAREN:
        case ASSIGN:
        case OR:
        case AND:
            //ExpSemID3L ::= ε
            break;
        case EQUAL:
            //ExpSemID3L ::= == ExpSemID3
            match(EQUAL);
            ExpSemID3();
            break;
        case NOT_EQUAL:
            //ExpSemID3L ::= != ExpSemID3
            match(NOT_EQUAL);
            ExpSemID3();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::ExpSemID4()
{
    switch (lookAhead)
    {
        case NUM:
        case MULT:
        case LPAREN:
        case SUM:
        case MINUS:
        case AMP:
        case EXCLAMATION:
        case LITERAL:
        case ASCII:
        case TRUE:
        case FALSE:
            //ExpSemID4 ::= ExpSemID5 ExpSemID4L
            ExpSemID5();
            ExpSemID4L();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::ExpSemID4L()
{
    switch (lookAhead)
    {
        case SEMICOLON:
        case RPAREN:
        case ASSIGN:
        case OR:
        case AND:
        case EQUAL:
        case NOT_EQUAL:
            //ExpSemID4L ::= ε
            break;
        case LE:
            //ExpSemID4L ::= < ExpSemID4
            match(LE);
            ExpSemID4();
            break;
        case LEQ:
            //ExpSemID4L ::= <= ExpSemID4
            match(LEQ);
            ExpSemID4();
            break;
        case GTE:
            //ExpSemID4L ::= >= ExpSemID4
            match(GTE);
            ExpSemID4();
            break;
        case GT:
            //ExpSemID4L ::= > ExpSemID4
            match(GT);
            ExpSemID4();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::ExpSemID5()
{
    switch (lookAhead)
    {
        case NUM:
        case MULT:
        case LPAREN:
        case SUM:
        case MINUS:
        case AMP:
        case EXCLAMATION:
        case LITERAL:
        case ASCII:
        case TRUE:
        case FALSE:
            //ExpSemID5 ::= ExpSemID6 ExpSemID5L
            ExpSemID6();
            ExpSemID5L();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::ExpSemID5L()
{
    switch (lookAhead)
    {
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
            //ExpSemID5L ::= ε
            break;
        case SUM:
            //ExpSemID5L ::= + ExpSemID5
            match(SUM);
            ExpSemID5();
            break;
        case MINUS:
            //ExpSemID5L ::= - ExpSemID5
            match(MINUS);
            ExpSemID5();
            break;
        case VERBAR:
            //ExpSemID5L ::= | ExpSemID5
            match(VERBAR);
            ExpSemID5();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::ExpSemID6()
{
    switch (lookAhead)
    {
        case NUM:
        case MULT:
        case LPAREN:
        case SUM:
        case MINUS:
        case AMP:
        case EXCLAMATION:
        case LITERAL:
        case ASCII:
        case TRUE:
        case FALSE:
            //ExpSemID6 ::= ExpSemID7 ExpSemID6L
            ExpSemID7();
            ExpSemID6L();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::ExpSemID6L()
{
    switch (lookAhead)
    {
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
            //ExpSemID6L ::= ε
            break;
        case MULT:
            //ExpSemID6L ::= * ExpSemID6
            match(MULT);
            ExpSemID6();
            break;
        case DIV:
            //ExpSemID6L ::= / ExpSemID6
            match(DIV);
            ExpSemID6();
            break;
        case MOD:
            //ExpSemID6L ::= % ExpSemID6
            match(MOD);
            ExpSemID6();
            break;
        case AMP:
            //ExpSemID6L ::= & ExpSemID6
            match(AMP);
            ExpSemID6();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::ExpSemID7()
{
    switch (lookAhead)
    {
        case NUM:
        case MULT:
        case LPAREN:
        case AMP:
        case LITERAL:
        case ASCII:
        case TRUE:
        case FALSE:
            //ExpSemID7 ::= PrimarySemID
            PrimarySemID();
            break;
        case SUM:
            //ExpSemID7 ::= + ExpSemID7
            match(SUM);
            ExpSemID7();
            break;
        case MINUS:
            //ExpSemID7 ::= - ExpSemID7
            match(MINUS);
            ExpSemID7();
            break;
        case EXCLAMATION:
            //ExpSemID7 ::= ! ExpSemID7
            match(EXCLAMATION);
            ExpSemID7();
            break;
        default:
            printf("Syntax Error\n");
    }
}
void RDParser::PrimarySemID()
{
    switch (lookAhead)
    {
        case NUM:
            //PrimarySemID ::= num
            match(NUM);
            break;
        case MULT:
            //PrimarySemID ::= * id
            match(MULT);
            match(ID);
            break;
        case LPAREN:
            //PrimarySemID ::= ( ExpSemID )
            match(LPAREN);
            ExpSemID();
            match(RPAREN);
            break;
        case AMP:
            //PrimarySemID ::= & id
            match(AMP);
            match(ID);
            break;
        case LITERAL:
            //PrimarySemID ::= literal
            match(LITERAL);
            break;
        case ASCII:
            //PrimarySemID ::= ascii
            match(ASCII);
            break;
        case TRUE:
            //PrimarySemID ::= true
            match(TRUE);
            break;
        case FALSE:
            //PrimarySemID ::= false
            match(FALSE);
            break;
        default:
            printf("Syntax Error\n");
    }
}