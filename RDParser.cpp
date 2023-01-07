#include "RDParser.h"

RDParser::RDParser()
{
    // printf("[DEBUG] *************** Inicializa o parser ***************\n");
}
RDParser::~RDParser() {}

void RDParser::startParser()
{
    nextToken();

    root = new Program_Node(nullptr, nullptr, nullptr);

    visitor = new Print_AST();
    program = Program(root);
    program->accept(visitor);

    delete visitor;
    delete root;
}

void RDParser::nextToken()
{
    // Aqui obtem o nextToken do analisador léxico
    lookAhead = getNextToken();
    // printf("lookAhead: %d \n", lookAhead);
    char *tokenName = getTokenName(lookAhead);
    if (tokenName)
    {
        // printf("[DEBUG] Token de lookAhead: %s\n", tokenName);
    }
}

void RDParser::matchOrSkip(int expectedToken, const int *syncArr)
{
    if (expectedToken != lookAhead)
    {
        writeError(expectedToken);
        syncError(syncArr);
    }
    else
    {
        nextToken();
    }
}

static char errorTemplate[] = "Token esperado: ";
static char errorTemplate2[] = "Token nao esperado: ";

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
    // printf("writeError %d, ", getSourceCodeLine ());
    writeSyntaxError(errStr, getSourceCodeLine(), getSourceCodeColumn());
}

void RDParser::defaultError(const int *syncArr)
{
    char *errStr = new char[100];
    int i = 0;
    for (i = 0; errorTemplate2[i] != '\0'; i++)
    {
        errStr[i] = errorTemplate2[i];
    }
    char *tokenName = getTokenName(lookAhead);
    int j = 0;
    for (; tokenName[j] != '\0'; j++)
    {
        errStr[i + j] = tokenName[j];
    }
    errStr[i + j] = '\0';
    writeSyntaxError(errStr, getSourceCodeLine(), getSourceCodeColumn());
    syncError(syncArr);
}

void RDParser::syncError(const int *syncArr)
{
    // printf("syncError %d, ", getSourceCodeLine ());
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
Program_Node *RDParser::Program(Program_Node *root)
{
    FunctionList_Node *functionlist = new FunctionList_Node(nullptr, nullptr, nullptr, nullptr, nullptr);
    TypeList_Node *typelist = new TypeList_Node(nullptr, nullptr, nullptr);
    VarList_Node *varlist = new VarList_Node();

    root = new Program_Node(FunctionDecl(functionlist), TypeDecl(typelist), IdList(varlist));

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
    {
        // Program ::= Type Pointer id FatoraPg Program
        Token_Node *double_token = new Token_Node(DOUBLE, getLexeme());

        Type_Node *type = new Type_Node(double_token);
        Type(type);

        Pointer_Node *pointer = new Pointer_Node();
        Pointer(pointer);

        matchOrSkip(ID, sync_Program);
        FatoraPg();

        root = new Program_Node(functionlist, typelist, varlist);
        return Program(root);
    }
    case TYPEDEF:
    {
        // Program ::= TypeDecl Program
        typelist = TypeDecl(typelist);

        root = new Program_Node(functionlist, typelist, varlist);
        return Program(root);
    }
    default:
        defaultError(sync_Program);
    }

    return root;
}

int RDParser::sync_TypeDecl[] = {TYPEDEF, ID, INTEGER, LONG, FLOAT, BOOL, CHAR, DOUBLE, END_OF_FILE};
TypeList_Node *RDParser::TypeDecl(TypeList_Node *typeDecl)
{
    Token_Node *id = new Token_Node(ID, getLexeme());
    Type_Node *type = new Type_Node(id, getLexeme());
    NameDecl_Node *varDecl = new NameDecl_Node(type, id);
    VarList_Node *idList = new VarList_Node(varDecl, idList);

    typeDecl = new TypeList_Node(idList, id, typeDecl);

    switch (lookAhead)
    {
    case TYPEDEF:
    {
        // TypeDecl ::= typedef struct { Type IdList ; VarDecl } id ;
        matchOrSkip(TYPEDEF, sync_TypeDecl);
        matchOrSkip(STRUCT, sync_TypeDecl);
        matchOrSkip(LBRACE, sync_TypeDecl);

        Type(type);

        IdList(idList);

        matchOrSkip(SEMICOLON, sync_TypeDecl);

        VarDecl(varDecl);

        matchOrSkip(RBRACE, sync_TypeDecl);
        matchOrSkip(ID, sync_TypeDecl);
        matchOrSkip(SEMICOLON, sync_TypeDecl);
        break;
    }
    default:
        defaultError(sync_TypeDecl);
    }
    return typeDecl;
}

int RDParser::sync_FatoraPg[] = {TYPEDEF, ID, INTEGER, LONG, FLOAT, BOOL, CHAR, DOUBLE, END_OF_FILE};
void RDParser::FatoraPg()
{
    switch (lookAhead)
    {
    case ID:
    case SEMICOLON:
    case COMMA:
    case MULT:
    case LBRACKET:
    {
        // FatoraPg ::= Array IdList ;
        Exp_Node *exp = new Exp_Node();
        ExpList_Node *expList = new ExpList_Node(exp, expList);

        Array_Node *array = new Array_Node(exp, expList);
        Array(array);

        VarList_Node *idList;
        IdList(idList);

        matchOrSkip(SEMICOLON, sync_FatoraPg);
        break;
    }
    case LPAREN:
        // FatoraPg ::= FunctionDecl
        FunctionList_Node *functionDecl;
        FunctionDecl(functionDecl);
        break;
    default:
        defaultError(sync_FatoraPg);
    }
}

int RDParser::sync_IdList[] = {SEMICOLON, END_OF_FILE};
VarList_Node *RDParser::IdList(VarList_Node *idList)
{
    switch (lookAhead)
    {
    case ID:
    case MULT:
    {
        // IdList ::= Pointer id Array IdList
        Pointer_Node *pointer = new Pointer_Node();
        Pointer(pointer);

        matchOrSkip(ID, sync_IdList);

        Array_Node *array = new Array_Node(nullptr, nullptr);
        Array(array);

        return IdList(idList);
    }
    case SEMICOLON:
        // IdList ::= ε
        break;
    case COMMA:
    {
        // IdList ::= , Pointer id Array IdList
        matchOrSkip(COMMA, sync_IdList);

        Pointer_Node *pointer = new Pointer_Node();
        Pointer(pointer);

        matchOrSkip(ID, sync_IdList);

        Array_Node *array = new Array_Node(nullptr, nullptr);
        Array(array);

        return IdList(idList);
    }
    default:
        defaultError(sync_IdList);
    }
    return idList;
}

int RDParser::sync_Pointer[] = {ID, END_OF_FILE};
Pointer_Node *RDParser::Pointer(Pointer_Node *pointer)
{
    switch (lookAhead)
    {
    case ID:
        // Pointer ::= ε
        break;
    case MULT:
        // Pointer ::= *
        matchOrSkip(MULT, sync_Pointer);
        break;
    default:
        defaultError(sync_Pointer);
    }

    return pointer;
}

int RDParser::sync_Type[] = {ID, MULT, SEMICOLON, COMMA, END_OF_FILE};
Type_Node *RDParser::Type(Type_Node *type)
{
    switch (lookAhead)
    {
    case ID:
        // Type ::= id
        matchOrSkip(ID, sync_Type);
        break;
    case INTEGER:
    case LONG:
    case FLOAT:
    case BOOL:
    case CHAR:
    case DOUBLE:
        // Type ::= TypePure
        TypePure();
        break;
    default:
        defaultError(sync_Type);
    }

    return type;
}

int RDParser::sync_TypePure[] = {ID, MULT, SEMICOLON, COMMA, END_OF_FILE};
void RDParser::TypePure()
{
    switch (lookAhead)
    {
    case INTEGER:
        // TypePure ::= int
        matchOrSkip(INTEGER, sync_TypePure);
        break;
    case LONG:
        // TypePure ::= long
        matchOrSkip(LONG, sync_TypePure);
        break;
    case FLOAT:
        // TypePure ::= float
        matchOrSkip(FLOAT, sync_TypePure);
        break;
    case BOOL:
        // TypePure ::= bool
        matchOrSkip(BOOL, sync_TypePure);
        break;
    case CHAR:
        // TypePure ::= char
        matchOrSkip(CHAR, sync_TypePure);
        break;
    case DOUBLE:
        // TypePure ::= double
        matchOrSkip(DOUBLE, sync_TypePure);
        break;
    default:
        defaultError(sync_TypePure);
    }
}

int RDParser::sync_Array[] = {SEMICOLON, ID, COMMA, MULT, INTEGER, LONG, FLOAT, BOOL, CHAR, DOUBLE, RPAREN, END_OF_FILE};
Array_Node *RDParser::Array(Array_Node *array)
{
    switch (lookAhead)
    {
    case ID:
    case SEMICOLON:
    case COMMA:
    case MULT:
    case INTEGER:
    case LONG:
    case FLOAT:
    case BOOL:
    case CHAR:
    case DOUBLE:
    case RPAREN:
        // Array ::= ε
        break;
    case LBRACKET:
        // Array ::= [ num_int ] Array
        matchOrSkip(LBRACKET, sync_Array);
        matchOrSkip(NUM_INT, sync_Array);
        matchOrSkip(RBRACKET, sync_Array);

        Array(array);
        break;
    default:
        defaultError(sync_Array);
    }

    return array;
}

int RDParser::sync_VarDecl[] = {RBRACE, END_OF_FILE};
NameDecl_Node *RDParser::VarDecl(NameDecl_Node *varDecl)
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
        // VarDecl ::= Type IdList ; VarDecl
        Type_Node *type;
        Type(type);

        VarList_Node *idList;
        IdList(idList);

        matchOrSkip(SEMICOLON, sync_VarDecl);

        VarDecl(varDecl);
        break;
    case RBRACE:
        // VarDecl ::= ε
        break;
    default:
        defaultError(sync_VarDecl);
    }

    return varDecl;
}

int RDParser::sync_Params[] = {RPAREN, END_OF_FILE};
void RDParser::Params()
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
    {
        // Params ::= Type Pointer id Array Params
        Type_Node *type;
        Type(type);

        Pointer_Node *pointer;
        Pointer(pointer);

        matchOrSkip(ID, sync_Params);

        Array_Node *array;
        Array(array);

        Params();
        break;
    }
    case COMMA:
    {
        // Params ::= , Type Pointer id Array Params
        matchOrSkip(COMMA, sync_Params);

        Type_Node *type;
        Type(type);

        Pointer_Node *pointer;
        Pointer(pointer);

        matchOrSkip(ID, sync_Params);

        Array_Node *array;
        Array(array);

        Params();
        break;
    }
    case RPAREN:
        // Params ::= ε
        break;
    default:
        defaultError(sync_Params);
    }
}

int RDParser::sync_FunctionDecl[] = {TYPEDEF, ID, INTEGER, LONG, FLOAT, BOOL, CHAR, DOUBLE, END_OF_FILE};
FunctionList_Node *RDParser::FunctionDecl(FunctionList_Node *functionDecl)
{
    switch (lookAhead)
    {
    case LPAREN:
    {
        // FunctionDecl ::= ( Params ) { StmtList }
        matchOrSkip(LPAREN, sync_FunctionDecl);
        Params();
        matchOrSkip(RPAREN, sync_FunctionDecl);
        matchOrSkip(LBRACE, sync_FunctionDecl);

        StmtList_Node *stmtList = new StmtList_Node(nullptr, nullptr);
        StmtList(stmtList);

        matchOrSkip(RBRACE, sync_FunctionDecl);
    }
    default:
        defaultError(sync_FunctionDecl);
    }

    return functionDecl;
}

int RDParser::sync_StmtList[] = {RBRACE, CASE, END_OF_FILE};
StmtList_Node *RDParser::StmtList(StmtList_Node *stmtList)
{
    switch (lookAhead)
    {
    case ID:
    case LBRACE:
    case MULT:
    case INTEGER:
    case LONG:
    case FLOAT:
    case BOOL:
    case CHAR:
    case DOUBLE:
    case IF:
    case WHILE:
    case SWITCH:
    case BREAK:
    case PRINT:
    case READLN:
    case RETURN:
    case THROW:
    case TRY:
    case AMP:
        // StmtList ::= Stmt StmtListK
        Stmt_Node *stmt;
        Stmt(stmt);

        StmtListK();
        break;
    default:
        defaultError(sync_StmtList);
    }

    return stmtList;
}

int RDParser::sync_StmtListK[] = {RBRACE, CASE, END_OF_FILE};
void RDParser::StmtListK()
{
    switch (lookAhead)
    {
    case ID:
    case LBRACE:
    case MULT:
    case INTEGER:
    case LONG:
    case FLOAT:
    case BOOL:
    case CHAR:
    case DOUBLE:
    case IF:
    case WHILE:
    case SWITCH:
    case BREAK:
    case PRINT:
    case READLN:
    case RETURN:
    case THROW:
    case TRY:
    case AMP:
        // StmtListK ::= StmtList
        StmtList_Node *stmtList;
        StmtList(stmtList);
        break;
    case RBRACE:
    case CASE:
        // StmtListK ::= ε
        break;
    default:
        defaultError(sync_StmtListK);
    }
}

int RDParser::sync_CaseBlock[] = {RBRACE, END_OF_FILE};
CaseBlock_Node *RDParser::CaseBlock(CaseBlock_Node *caseBlock)
{
    switch (lookAhead)
    {
    case CASE:
        // CaseBlock ::= case num_int : CaseBlockL
        matchOrSkip(CASE, sync_CaseBlock);
        matchOrSkip(NUM_INT, sync_CaseBlock);
        matchOrSkip(COLON, sync_CaseBlock);
        CaseBlockL();
        break;
    default:
        defaultError(sync_CaseBlock);
    }

    return caseBlock;
}

int RDParser::sync_CaseBlockL[] = {RBRACE, END_OF_FILE};
void RDParser::CaseBlockL()
{
    switch (lookAhead)
    {
    case ID:
    case LBRACE:
    case MULT:
    case INTEGER:
    case LONG:
    case FLOAT:
    case BOOL:
    case CHAR:
    case DOUBLE:
    case IF:
    case WHILE:
    case SWITCH:
    case BREAK:
    case PRINT:
    case READLN:
    case RETURN:
    case THROW:
    case TRY:
    case AMP:
        // CaseBlockL ::= StmtList CaseBlockF
        StmtList_Node *stmtList;
        StmtList(stmtList);

        CaseBlockF();
        break;
    case CASE:
        // CaseBlockL ::= CaseBlock
        CaseBlock_Node *caseBlock;
        CaseBlock(caseBlock);
        break;
    default:
        defaultError(sync_CaseBlockL);
    }
}

int RDParser::sync_CaseBlockF[] = {RBRACE, END_OF_FILE};
void RDParser::CaseBlockF()
{
    switch (lookAhead)
    {
    case RBRACE:
        // CaseBlockF ::= ε
        break;
    case CASE:
        // CaseBlockF ::= CaseBlock
        CaseBlock_Node *caseBlock;
        CaseBlock(caseBlock);
        break;
    default:
        defaultError(sync_CaseBlockF);
    }
}

int RDParser::sync_Stmt[] = {RBRACE, IF, WHILE, SWITCH, BREAK, PRINT, READLN, RETURN, THROW, LBRACE, TRY, ID, INTEGER, LONG, FLOAT, BOOL, CHAR, DOUBLE, MULT, AMP, CATCH, CASE, END_OF_FILE};
Stmt_Node *RDParser::Stmt(Stmt_Node *stmt)
{
    switch (lookAhead)
    {
    case ID:
        // Stmt ::= id FatoraStmt
        matchOrSkip(ID, sync_Stmt);
        FatoraStmt();
        break;
    case LBRACE:
    {
        // Stmt ::= { StmtList }
        matchOrSkip(LBRACE, sync_Stmt);

        StmtList_Node *stmtList;
        StmtList(stmtList);

        matchOrSkip(RBRACE, sync_Stmt);
        break;
    }
    case MULT:
        // Stmt ::= * id = Expr ;
        matchOrSkip(MULT, sync_Stmt);
        matchOrSkip(ID, sync_Stmt);
        matchOrSkip(ASSIGN, sync_Stmt);
        Expr();
        matchOrSkip(SEMICOLON, sync_Stmt);
        break;
    case INTEGER:
    case LONG:
    case FLOAT:
    case BOOL:
    case CHAR:
    case DOUBLE:
        // Stmt ::= TypePure IdList ;
        TypePure();

        VarList_Node *idList;
        IdList(idList);

        matchOrSkip(SEMICOLON, sync_Stmt);
        break;
    case IF:
    {
        // Stmt ::= if ( Expr ) { StmtList } IfOpt
        matchOrSkip(IF, sync_Stmt);
        matchOrSkip(LPAREN, sync_Stmt);
        Expr();
        matchOrSkip(RPAREN, sync_Stmt);
        matchOrSkip(LBRACE, sync_Stmt);

        StmtList_Node *stmtList;
        StmtList(stmtList);

        matchOrSkip(RBRACE, sync_Stmt);

        If_Node *ifOpt;
        IfOpt(ifOpt);
        break;
    }
    case WHILE:
        // Stmt ::= while ( Expr ) Stmt
        matchOrSkip(WHILE, sync_Stmt);
        matchOrSkip(LPAREN, sync_Stmt);
        Expr();
        matchOrSkip(RPAREN, sync_Stmt);

        Stmt(stmt);
        break;
    case SWITCH:
        // Stmt ::= switch ( Expr ) { CaseBlock }
        matchOrSkip(SWITCH, sync_Stmt);
        matchOrSkip(LPAREN, sync_Stmt);
        Expr();
        matchOrSkip(RPAREN, sync_Stmt);
        matchOrSkip(LBRACE, sync_Stmt);

        CaseBlock_Node *caseBlock;
        CaseBlock(caseBlock);

        matchOrSkip(RBRACE, sync_Stmt);
        break;
    case BREAK:
        // Stmt ::= break ;
        matchOrSkip(BREAK, sync_Stmt);
        matchOrSkip(SEMICOLON, sync_Stmt);
        break;
    case PRINT:
        // Stmt ::= print ( ExprList ) ;
        matchOrSkip(PRINT, sync_Stmt);
        matchOrSkip(LPAREN, sync_Stmt);

        ExpList_Node *exprList;
        ExprList(exprList);

        matchOrSkip(RPAREN, sync_Stmt);
        matchOrSkip(SEMICOLON, sync_Stmt);
        break;
    case READLN:
        // Stmt ::= readln ( Expr ) ;
        matchOrSkip(READLN, sync_Stmt);
        matchOrSkip(LPAREN, sync_Stmt);
        Expr();
        matchOrSkip(RPAREN, sync_Stmt);
        matchOrSkip(SEMICOLON, sync_Stmt);
        break;
    case RETURN:
        // Stmt ::= return Expr ;
        matchOrSkip(RETURN, sync_Stmt);
        Expr();
        matchOrSkip(SEMICOLON, sync_Stmt);
        break;
    case THROW:
        // Stmt ::= throw ;
        matchOrSkip(THROW, sync_Stmt);
        matchOrSkip(SEMICOLON, sync_Stmt);
        break;
    case TRY:
        // Stmt ::= try Stmt catch ( ... ) Stmt
        matchOrSkip(TRY, sync_Stmt);

        Stmt(stmt);

        matchOrSkip(CATCH, sync_Stmt);
        matchOrSkip(LPAREN, sync_Stmt);
        matchOrSkip(TRIPLE_DOT, sync_Stmt);
        matchOrSkip(RPAREN, sync_Stmt);

        Stmt(stmt);
        break;
    case AMP:
        // Stmt ::= & id = Expr ;
        matchOrSkip(AMP, sync_Stmt);
        matchOrSkip(ID, sync_Stmt);
        matchOrSkip(ASSIGN, sync_Stmt);
        Expr();
        matchOrSkip(SEMICOLON, sync_Stmt);
        break;
    default:
        defaultError(sync_Stmt);
    }

    return stmt;
}

int RDParser::sync_FatoraStmt[] = {RBRACE, IF, WHILE, SWITCH, BREAK, PRINT, READLN, RETURN, THROW, LBRACE, TRY, ID, INTEGER, LONG, FLOAT, BOOL, CHAR, DOUBLE, MULT, AMP, CATCH, CASE, END_OF_FILE};
void RDParser::FatoraStmt()
{
    switch (lookAhead)
    {
    case ID:
    case SEMICOLON:
    case COMMA:
    case MULT:
        // FatoraStmt ::= IdList ;
        VarList_Node *idList;
        IdList(idList);

        matchOrSkip(SEMICOLON, sync_FatoraStmt);
        break;
    case LBRACKET:
    case ASSIGN:
        // FatoraStmt ::= ArrayAcesso = Expr ;
        ArrayAcesso();
        matchOrSkip(ASSIGN, sync_FatoraStmt);
        Expr();
        matchOrSkip(SEMICOLON, sync_FatoraStmt);
        break;
    case LPAREN:
        // FatoraStmt ::= ( ExprList ) ;
        matchOrSkip(LPAREN, sync_FatoraStmt);

        ExpList_Node *exprList;
        ExprList(exprList);

        matchOrSkip(RPAREN, sync_FatoraStmt);
        matchOrSkip(SEMICOLON, sync_FatoraStmt);
        break;
    default:
        defaultError(sync_FatoraStmt);
    }
}

int RDParser::sync_IfOpt[] = {RBRACE, IF, WHILE, SWITCH, BREAK, PRINT, READLN, RETURN, THROW, LBRACE, TRY, ID, INTEGER, LONG, FLOAT, BOOL, CHAR, DOUBLE, MULT, AMP, CATCH, CASE, END_OF_FILE};
If_Node *RDParser::IfOpt(If_Node *ifOpt)
{
    switch (lookAhead)
    {
    case ID:
    case LBRACE:
    case RBRACE:
    case MULT:
    case INTEGER:
    case LONG:
    case FLOAT:
    case BOOL:
    case CHAR:
    case DOUBLE:
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
    case AMP:
        // IfOpt ::= ε
        break;
    case ELSE:
        // IfOpt ::= else ElseOpt
        matchOrSkip(ELSE, sync_IfOpt);

        ElseOpt(ifOpt);
        break;
    default:
        defaultError(sync_IfOpt);
    }

    return ifOpt;
}

int RDParser::sync_ElseOpt[] = {RBRACE, IF, WHILE, SWITCH, BREAK, PRINT, READLN, RETURN, THROW, LBRACE, TRY, ID, INTEGER, LONG, FLOAT, BOOL, CHAR, DOUBLE, MULT, AMP, CATCH, CASE, END_OF_FILE};
If_Node *RDParser::ElseOpt(If_Node *elseOpt)
{
    switch (lookAhead)
    {
    case LBRACE:
    {
        // ElseOpt ::= { StmtList }
        matchOrSkip(LBRACE, sync_ElseOpt);

        StmtList_Node *stmtList;
        StmtList(stmtList);

        matchOrSkip(RBRACE, sync_ElseOpt);
        break;
    }
    case IF:
    {
        // ElseOpt ::= if ( Expr ) { StmtList } IfOpt
        matchOrSkip(IF, sync_ElseOpt);
        matchOrSkip(LPAREN, sync_ElseOpt);
        Expr();
        matchOrSkip(RPAREN, sync_ElseOpt);
        matchOrSkip(LBRACE, sync_ElseOpt);

        StmtList_Node *stmtList;
        StmtList(stmtList);

        matchOrSkip(RBRACE, sync_ElseOpt);

        IfOpt(elseOpt);
        break;
    }
    default:
        defaultError(sync_ElseOpt);
    }

    return elseOpt;
}

int RDParser::sync_ArrayAcesso[] = {ASSIGN, RPAREN, SEMICOLON, RBRACKET, COMMA, OR, AND, EQUAL, NOT_EQUAL, LE, LEQ, GTE, GT, SUM, MINUS, VERBAR, MULT, DIV, MOD, AMP, END_OF_FILE};
void RDParser::ArrayAcesso()
{
    switch (lookAhead)
    {
    case SEMICOLON:
    case COMMA:
    case MULT:
    case RBRACKET:
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
        // ArrayAcesso ::= ε
        break;
    case LBRACKET:
        // ArrayAcesso ::= [ Expr ] ArrayAcesso
        matchOrSkip(LBRACKET, sync_ArrayAcesso);
        Expr();
        matchOrSkip(RBRACKET, sync_ArrayAcesso);
        ArrayAcesso();
        break;
    default:
        defaultError(sync_ArrayAcesso);
    }
}

int RDParser::sync_ExprList[] = {RPAREN, END_OF_FILE};
ExpList_Node *RDParser::ExprList(ExpList_Node *exprList)
{
    switch (lookAhead)
    {
    case ID:
    case MULT:
    case NUM_INT:
    case LPAREN:
    case AMP:
    case SUM:
    case MINUS:
    case EXCLAMATION:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
        // ExprList ::= Expr ExprListTail
        Expr();
        ExprListTail();
        break;
    case RPAREN:
        // ExprList ::= ε
        break;
    default:
        defaultError(sync_ExprList);
    }

    return exprList;
}

int RDParser::sync_ExprListTail[] = {RPAREN, END_OF_FILE};
void RDParser::ExprListTail()
{
    switch (lookAhead)
    {
    case COMMA:
        // ExprListTail ::= , Expr ExprListTail
        matchOrSkip(COMMA, sync_ExprListTail);
        Expr();
        ExprListTail();
        break;
    case RPAREN:
        // ExprListTail ::= ε
        break;
    default:
        defaultError(sync_ExprListTail);
    }
}

int RDParser::sync_Expr[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, END_OF_FILE};
void RDParser::Expr()
{
    switch (lookAhead)
    {
    case ID:
    case MULT:
    case NUM_INT:
    case LPAREN:
    case AMP:
    case SUM:
    case MINUS:
    case EXCLAMATION:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
        // Expr ::= Expr1 ExprL
        Expr1();
        ExprL();
        break;
    default:
        defaultError(sync_Expr);
    }
}

int RDParser::sync_ExprL[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, END_OF_FILE};
void RDParser::ExprL()
{
    switch (lookAhead)
    {
    case SEMICOLON:
    case COMMA:
    case RBRACKET:
    case RPAREN:
        // ExprL ::= ε
        break;
    case ASSIGN:
        // ExprL ::= = Expr
        matchOrSkip(ASSIGN, sync_ExprL);
        Expr();
        break;
    default:
        defaultError(sync_ExprL);
    }
}

int RDParser::sync_Expr1[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, END_OF_FILE};
void RDParser::Expr1()
{
    switch (lookAhead)
    {
    case ID:
    case MULT:
    case NUM_INT:
    case LPAREN:
    case AMP:
    case SUM:
    case MINUS:
    case EXCLAMATION:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
        // Expr1 ::= Expr2 Expr1L
        Expr2();
        Expr1L();
        break;
    default:
        defaultError(sync_Expr1);
    }
}

int RDParser::sync_Expr1L[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, END_OF_FILE};
void RDParser::Expr1L()
{
    switch (lookAhead)
    {
    case SEMICOLON:
    case COMMA:
    case RBRACKET:
    case RPAREN:
    case ASSIGN:
        // Expr1L ::= ε
        break;
    case OR:
        // Expr1L ::= || Expr1
        matchOrSkip(OR, sync_Expr1L);
        Expr1();
        break;
    default:
        defaultError(sync_Expr1L);
    }
}

int RDParser::sync_Expr2[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, OR, END_OF_FILE};
void RDParser::Expr2()
{
    switch (lookAhead)
    {
    case ID:
    case MULT:
    case NUM_INT:
    case LPAREN:
    case AMP:
    case SUM:
    case MINUS:
    case EXCLAMATION:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
        // Expr2 ::= Expr3 Expr2L
        Expr3();
        Expr2L();
        break;
    default:
        defaultError(sync_Expr2);
    }
}

int RDParser::sync_Expr2L[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, OR, END_OF_FILE};
void RDParser::Expr2L()
{
    switch (lookAhead)
    {
    case SEMICOLON:
    case COMMA:
    case RBRACKET:
    case RPAREN:
    case ASSIGN:
    case OR:
        // Expr2L ::= ε
        break;
    case AND:
        // Expr2L ::= && Expr2
        matchOrSkip(AND, sync_Expr2L);
        Expr2();
        break;
    default:
        defaultError(sync_Expr2L);
    }
}

int RDParser::sync_Expr3[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, OR, AND, END_OF_FILE};
void RDParser::Expr3()
{
    switch (lookAhead)
    {
    case ID:
    case MULT:
    case NUM_INT:
    case LPAREN:
    case AMP:
    case SUM:
    case MINUS:
    case EXCLAMATION:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
        // Expr3 ::= Expr4 Expr3L
        Expr4();
        Expr3L();
        break;
    default:
        defaultError(sync_Expr3);
    }
}

int RDParser::sync_Expr3L[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, OR, AND, END_OF_FILE};
void RDParser::Expr3L()
{
    switch (lookAhead)
    {
    case SEMICOLON:
    case COMMA:
    case RBRACKET:
    case RPAREN:
    case ASSIGN:
    case OR:
    case AND:
        // Expr3L ::= ε
        break;
    case EQUAL:
        // Expr3L ::= == Expr3
        matchOrSkip(EQUAL, sync_Expr3L);
        Expr3();
        break;
    case NOT_EQUAL:
        // Expr3L ::= != Expr3
        matchOrSkip(NOT_EQUAL, sync_Expr3L);
        Expr3();
        break;
    default:
        defaultError(sync_Expr3L);
    }
}

int RDParser::sync_Expr4[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, OR, AND, EQUAL, NOT_EQUAL, END_OF_FILE};
void RDParser::Expr4()
{
    switch (lookAhead)
    {
    case ID:
    case MULT:
    case NUM_INT:
    case LPAREN:
    case AMP:
    case SUM:
    case MINUS:
    case EXCLAMATION:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
        // Expr4 ::= Expr5 Expr4L
        Expr5();
        Expr4L();
        break;
    default:
        defaultError(sync_Expr4);
    }
}

int RDParser::sync_Expr4L[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, OR, AND, EQUAL, NOT_EQUAL, END_OF_FILE};
void RDParser::Expr4L()
{
    switch (lookAhead)
    {
    case SEMICOLON:
    case COMMA:
    case RBRACKET:
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
        matchOrSkip(LE, sync_Expr4L);
        Expr4();
        break;
    case LEQ:
        // Expr4L ::= <= Expr4
        matchOrSkip(LEQ, sync_Expr4L);
        Expr4();
        break;
    case GTE:
        // Expr4L ::= >= Expr4
        matchOrSkip(GTE, sync_Expr4L);
        Expr4();
        break;
    case GT:
        // Expr4L ::= > Expr4
        matchOrSkip(GT, sync_Expr4L);
        Expr4();
        break;
    default:
        defaultError(sync_Expr4L);
    }
}

int RDParser::sync_Expr5[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, OR, AND, EQUAL, NOT_EQUAL, LE, LEQ, GTE, GT, END_OF_FILE};
void RDParser::Expr5()
{
    switch (lookAhead)
    {
    case ID:
    case MULT:
    case NUM_INT:
    case LPAREN:
    case AMP:
    case SUM:
    case MINUS:
    case EXCLAMATION:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
        // Expr5 ::= Expr6 Expr5L
        Expr6();
        Expr5L();
        break;
    default:
        defaultError(sync_Expr5);
    }
}

int RDParser::sync_Expr5L[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, OR, AND, EQUAL, NOT_EQUAL, LE, LEQ, GTE, GT, END_OF_FILE};
void RDParser::Expr5L()
{
    switch (lookAhead)
    {
    case SEMICOLON:
    case COMMA:
    case RBRACKET:
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
        matchOrSkip(SUM, sync_Expr5L);
        Expr5();
        break;
    case MINUS:
        // Expr5L ::= - Expr5
        matchOrSkip(MINUS, sync_Expr5L);
        Expr5();
        break;
    case VERBAR:
        // Expr5L ::= | Expr5
        matchOrSkip(VERBAR, sync_Expr5L);
        Expr5();
        break;
    default:
        defaultError(sync_Expr5L);
    }
}

int RDParser::sync_Expr6[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, OR, AND, EQUAL, NOT_EQUAL, LE, LEQ, GTE, GT, SUM, MINUS, VERBAR, END_OF_FILE};
void RDParser::Expr6()
{
    switch (lookAhead)
    {
    case ID:
    case MULT:
    case NUM_INT:
    case LPAREN:
    case AMP:
    case SUM:
    case MINUS:
    case EXCLAMATION:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
        // Expr6 ::= Expr7 Expr6L
        Expr7();
        Expr6L();
        break;
    default:
        defaultError(sync_Expr6);
    }
}

int RDParser::sync_Expr6L[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, OR, AND, EQUAL, NOT_EQUAL, LE, LEQ, GTE, GT, SUM, MINUS, VERBAR, END_OF_FILE};
void RDParser::Expr6L()
{
    switch (lookAhead)
    {
    case SEMICOLON:
    case COMMA:
    case RBRACKET:
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
        matchOrSkip(MULT, sync_Expr6L);
        Expr6();
        break;
    case AMP:
        // Expr6L ::= & Expr6
        matchOrSkip(AMP, sync_Expr6L);
        Expr6();
        break;
    case DIV:
        // Expr6L ::= / Expr6
        matchOrSkip(DIV, sync_Expr6L);
        Expr6();
        break;
    case MOD:
        // Expr6L ::= % Expr6
        matchOrSkip(MOD, sync_Expr6L);
        Expr6();
        break;
    default:
        defaultError(sync_Expr6L);
    }
}

int RDParser::sync_Expr7[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, OR, AND, EQUAL, NOT_EQUAL, LE, LEQ, GTE, GT, SUM, MINUS, VERBAR, MULT, DIV, MOD, AMP, END_OF_FILE};
void RDParser::Expr7()
{
    switch (lookAhead)
    {
    case ID:
    case MULT:
    case NUM_INT:
    case LPAREN:
    case AMP:
    case NUM_REAL:
    case LITERAL:
    case ASCII:
    case TRUE:
    case FALSE:
        // Expr7 ::= Primary
        Exp_Node *primary;
        Primary(primary);
        break;
    case SUM:
        // Expr7 ::= + Expr7
        matchOrSkip(SUM, sync_Expr7);
        Expr7();
        break;
    case MINUS:
        // Expr7 ::= - Expr7
        matchOrSkip(MINUS, sync_Expr7);
        Expr7();
        break;
    case EXCLAMATION:
        // Expr7 ::= ! Expr7
        matchOrSkip(EXCLAMATION, sync_Expr7);
        Expr7();
        break;
    default:
        defaultError(sync_Expr7);
    }
}

int RDParser::sync_Primary[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, OR, AND, EQUAL, NOT_EQUAL, LE, LEQ, GTE, GT, SUM, MINUS, VERBAR, MULT, DIV, MOD, AMP, END_OF_FILE};
Exp_Node *RDParser::Primary(Exp_Node *primary)
{
    switch (lookAhead)
    {
    case ID:
        // Primary ::= id PrimaryFatora
        matchOrSkip(ID, sync_Primary);
        PrimaryFatora();
        break;
    case MULT:
        // Primary ::= * id
        matchOrSkip(MULT, sync_Primary);
        matchOrSkip(ID, sync_Primary);
        break;
    case NUM_INT:
        // Primary ::= num_int
        matchOrSkip(NUM_INT, sync_Primary);
        break;
    case LPAREN:
        // Primary ::= ( Expr )
        matchOrSkip(LPAREN, sync_Primary);
        Expr();
        matchOrSkip(RPAREN, sync_Primary);
        break;
    case AMP:
        // Primary ::= & id
        matchOrSkip(AMP, sync_Primary);
        matchOrSkip(ID, sync_Primary);
        break;
    case NUM_REAL:
        // Primary ::= num_real
        matchOrSkip(NUM_REAL, sync_Primary);
        break;
    case LITERAL:
        // Primary ::= literal
        matchOrSkip(LITERAL, sync_Primary);
        break;
    case ASCII:
        // Primary ::= ascii
        matchOrSkip(ASCII, sync_Primary);
        break;
    case TRUE:
        // Primary ::= true
        matchOrSkip(TRUE, sync_Primary);
        break;
    case FALSE:
        // Primary ::= false
        matchOrSkip(FALSE, sync_Primary);
        break;
    default:
        defaultError(sync_Primary);
    }

    return primary;
}

int RDParser::sync_PrimaryFatora[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, OR, AND, EQUAL, NOT_EQUAL, LE, LEQ, GTE, GT, SUM, MINUS, VERBAR, MULT, DIV, MOD, AMP, END_OF_FILE};
void RDParser::PrimaryFatora()
{
    switch (lookAhead)
    {
    case SEMICOLON:
    case COMMA:
    case MULT:
    case LBRACKET:
    case RBRACKET:
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
        // PrimaryFatora ::= ArrayAcesso
        ArrayAcesso();
        break;
    case LPAREN:
        // PrimaryFatora ::= ( ExprList )
        matchOrSkip(LPAREN, sync_PrimaryFatora);

        ExpList_Node *exprList;
        ExprList(exprList);
        matchOrSkip(RPAREN, sync_PrimaryFatora);
        break;
    default:
        defaultError(sync_PrimaryFatora);
    }
}