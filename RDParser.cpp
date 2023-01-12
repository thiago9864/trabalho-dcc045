#include "RDParser.h"

RDParser::RDParser()
{
     printf("********************* PARSER OUTPUT *********************\n");
}
RDParser::~RDParser() {}

void RDParser::startParser()
{
    nextToken();

    visitor = new Print_AST();

    root = Program(nullptr, nullptr, nullptr);
    root->accept(visitor);

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
        if(lookAhead == ID || lookAhead == NUM_INT || lookAhead == NUM_REAL || lookAhead==LITERAL){
            printf("MATCH: %s.%s\n", getTokenName(lookAhead), getLexeme());
        } else {
            printf("MATCH: %s\n", getTokenName(lookAhead));
        }
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
Program_Node *RDParser::Program(FunctionList_Node *functionlist, TypeList_Node *typelist, VarList_Node *varlist)
{
    printf("Program\n");
    switch (lookAhead)
    {
    case END_OF_FILE:
    {
        // Program ::= ε
        Program_Node *programNode = new Program_Node(functionlist, typelist, varlist);
        return programNode;
    }
    case ID:
    case INTEGER:
    case LONG:
    case FLOAT:
    case BOOL:
    case CHAR:
    case DOUBLE:
    {
        // Program ::= Type Pointer id FatoraPg Program
        Type_Node *type = Type();
        Pointer_Node *pointer = Pointer();

        Token_Node *id = new Token_Node(ID, getLexeme());
        matchOrSkip(ID, sync_Program);

        Root_Node *node = FatoraPg(id, type, pointer, varlist);

        if (node != nullptr && typeid(*node) == typeid(Function_Node))
        {
            Function_Node *func = (Function_Node *)node;

            functionlist = new FunctionList_Node(func, functionlist);

            Program_Node *programNode = new Program_Node(functionlist, typelist, varlist);
            return programNode;
        }

        varlist = (VarList_Node *)node;

        return Program(functionlist, typelist, varlist);
    }
    case TYPEDEF:
    {
        // Program ::= TypeDecl Program
        typelist = TypeDecl(typelist);
        return Program(functionlist, typelist, varlist);
    }
    default:
        defaultError(sync_Program);
        return Program(functionlist, typelist, varlist);
    }
    Program_Node *programNode = new Program_Node(functionlist, typelist, varlist);
    return programNode;
}

int RDParser::sync_TypeDecl[] = {TYPEDEF, ID, INTEGER, LONG, FLOAT, BOOL, CHAR, DOUBLE, END_OF_FILE};
TypeList_Node *RDParser::TypeDecl(TypeList_Node *typeDecl)
{
    printf("TypeDecl\n");
    switch (lookAhead)
    {
    case TYPEDEF:
    {
        // TypeDecl ::= typedef struct { Type IdList ; VarDecl } id ;
        matchOrSkip(TYPEDEF, sync_TypeDecl);
        matchOrSkip(STRUCT, sync_TypeDecl);
        matchOrSkip(LBRACE, sync_TypeDecl);

        Type_Node *type = Type();
        NameDecl_Node *idList = IdList();

        matchOrSkip(SEMICOLON, sync_TypeDecl);

        VarList_Node *vardecl = new VarList_Node(type, idList, VarDecl());

        matchOrSkip(RBRACE, sync_TypeDecl);

        Token_Node *id = new Token_Node(ID, getLexeme());
        matchOrSkip(ID, sync_TypeDecl);
        matchOrSkip(SEMICOLON, sync_TypeDecl);

        typeDecl = new TypeList_Node(vardecl, id, typeDecl);

        return TypeDecl(typeDecl);
    }
    default:
        defaultError(sync_TypeDecl);
        return typeDecl;
    }
}

int RDParser::sync_FatoraPg[] = {TYPEDEF, ID, INTEGER, LONG, FLOAT, BOOL, CHAR, DOUBLE, END_OF_FILE};
Root_Node *RDParser::FatoraPg(Token_Node *id, Type_Node *type, Pointer_Node *pointer, VarList_Node *varlist)
{
    printf("FatoraPg\n");
    switch (lookAhead)
    {
    case ID:
    case SEMICOLON:
    case COMMA:
    case MULT:
    case LBRACKET:
    {
        // FatoraPg ::= Array IdList ;
        Array_Node *array = Array();
        NameDecl_Node *idList = new NameDecl_Node(id, pointer, array, IdList());

        matchOrSkip(SEMICOLON, sync_FatoraPg);

        VarList_Node *varlistNode = new VarList_Node(type, idList, varlist);
        return varlistNode;
    }
    case LPAREN:
    {
        // FatoraPg ::= FunctionDecl
        Function_Node *functionlist = FunctionDecl(id, type, pointer, varlist);

        return functionlist;
    }
    default:
        defaultError(sync_FatoraPg);
        return nullptr;
    }
}

int RDParser::sync_IdList[] = {SEMICOLON, END_OF_FILE};
NameDecl_Node *RDParser::IdList()
{
    printf("IdList\n");
    switch (lookAhead)
    {
    case ID:
    case MULT:
    {
        // IdList ::= Pointer id Array IdList
        Pointer_Node *pointer = Pointer();

        Token_Node *id = new Token_Node(ID, getLexeme());
        matchOrSkip(ID, sync_IdList);

        Array_Node *array = Array();

        Type_Node *type = new Type_Node(id, getLexeme());

        NameDecl_Node *idList = new NameDecl_Node(id, pointer, array, IdList());

        return idList;
    }
    case SEMICOLON:
        // IdList ::= ε
        return nullptr;
    case COMMA:
    {
        // IdList ::= , Pointer id Array IdList
        matchOrSkip(COMMA, sync_IdList);

        Pointer_Node *pointer = Pointer();

        Token_Node *id = new Token_Node(ID, getLexeme());
        matchOrSkip(ID, sync_IdList);

        Array_Node *array = Array();

        Type_Node *type = new Type_Node(id, getLexeme());

        NameDecl_Node *idList = new NameDecl_Node(id, pointer, array, IdList());

        return idList;
    }
    default:
        defaultError(sync_IdList);
        return nullptr;
    }
}

int RDParser::sync_Pointer[] = {ID, END_OF_FILE};
Pointer_Node *RDParser::Pointer()
{
    printf("Pointer\n");
    switch (lookAhead)
    {
    case ID:
        // Pointer ::= ε
        return nullptr;
    case MULT:
    {
        // Pointer ::= *
        matchOrSkip(MULT, sync_Pointer);

        Pointer_Node *pointer = new Pointer_Node();
        return pointer;
    }
    default:
        defaultError(sync_Pointer);
        return nullptr;
    }
}

int RDParser::sync_Type[] = {ID, MULT, SEMICOLON, COMMA, END_OF_FILE};
Type_Node *RDParser::Type()
{
    printf("Type\n");
    switch (lookAhead)
    {
    case ID:
    {
        // Type ::= id
        Token_Node *token = new Token_Node(ID, getLexeme());
        token->setType(ID);
        token->setTypeLexeme(getLexeme());
        matchOrSkip(ID, sync_Type);

        Type_Node *type = new Type_Node(token, getLexeme());
        return type;
    }
    case INTEGER:
    case LONG:
    case FLOAT:
    case BOOL:
    case CHAR:
    case DOUBLE:
    {
        // Type ::= TypePure
        Type_Node *type = TypePure();
        return type;
    }
    default:
        defaultError(sync_Type);
    }

    return nullptr;
}

int RDParser::sync_TypePure[] = {ID, MULT, SEMICOLON, COMMA, END_OF_FILE};
Type_Node *RDParser::TypePure()
{
    printf("TypePure\n");
    switch (lookAhead)
    {
    case INTEGER:
    {
        // TypePure ::= int
        Token_Node *token = new Token_Node(INTEGER, getLexeme());
        token->setType(INTEGER);
        Type_Node *type = new Type_Node(token, getLexeme());

        matchOrSkip(INTEGER, sync_TypePure);

        return type;
    }
    case LONG:
    {
        // TypePure ::= long
        Token_Node *token = new Token_Node(LONG, getLexeme());
        token->setType(LONG);

        Type_Node *type = new Type_Node(token, getLexeme());

        matchOrSkip(LONG, sync_TypePure);

        return type;
    }
    case FLOAT:
    {
        // TypePure ::= float
        Token_Node *token = new Token_Node(FLOAT, getLexeme());
        token->setType(FLOAT);

        Type_Node *type = new Type_Node(token, getLexeme());
        matchOrSkip(FLOAT, sync_TypePure);

        return type;
    }
    case BOOL:
    {
        // TypePure ::= bool
        Token_Node *token = new Token_Node(BOOL, getLexeme());
        token->setType(BOOL);
        Type_Node *type = new Type_Node(token, getLexeme());

        matchOrSkip(BOOL, sync_TypePure);

        return type;
    }
    case CHAR:
    {
        // TypePure ::= char
        Token_Node *token = new Token_Node(CHAR, getLexeme());
        token->setType(CHAR);
        Type_Node *type = new Type_Node(token, getLexeme());

        matchOrSkip(CHAR, sync_TypePure);

        return type;
    }
    case DOUBLE:
    {
        // TypePure ::= double
        Token_Node *token = new Token_Node(DOUBLE, getLexeme());
        token->setType(DOUBLE);
        Type_Node *type = new Type_Node(token, getLexeme());

        matchOrSkip(DOUBLE, sync_TypePure);

        return type;
    }
    default:
        defaultError(sync_TypePure);
        return nullptr;
    }
}

int RDParser::sync_Array[] = {SEMICOLON, ID, COMMA, MULT, INTEGER, LONG, FLOAT, BOOL, CHAR, DOUBLE, RPAREN, END_OF_FILE};
Array_Node *RDParser::Array()
{
    printf("Array\n");
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
        return nullptr;
    case LBRACKET:
    {
        // Array ::= [ num_int ] Array
        matchOrSkip(LBRACKET, sync_Array);

        Token_Node *numInt = new Token_Node(NUM_INT, getLexeme());
        matchOrSkip(NUM_INT, sync_Array);
        matchOrSkip(RBRACKET, sync_Array);

        Array_Node *array = Array();
        return array;
    }
    default:
        defaultError(sync_Array);
    }
    return nullptr;
}

int RDParser::sync_VarDecl[] = {RBRACE, END_OF_FILE};
VarList_Node *RDParser::VarDecl()
{
    printf("VarDecl\n");
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
        // VarDecl ::= Type IdList ; VarDecl
        Type_Node *type = Type();
        NameDecl_Node *idList = IdList();

        matchOrSkip(SEMICOLON, sync_VarDecl);

        VarList_Node *varDecl = new VarList_Node(type, idList, VarDecl());
        return varDecl;
    }
    case RBRACE:
        // VarDecl ::= ε
        return nullptr;
    default:
        defaultError(sync_VarDecl);
    }
    return nullptr;
}

int RDParser::sync_Params[] = {RPAREN, END_OF_FILE};
Params_Node *RDParser::Params()
{
    printf("Params\n");
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
        Type_Node *type = Type();
        Pointer_Node *pointer = Pointer();

        Token_Node *id = new Token_Node(ID, getLexeme());
        matchOrSkip(ID, sync_Params);

        Array_Node *array = Array();

        Params_Node *parameters = new Params_Node(id, type, pointer, array, Params());
        return parameters;
    }
    case COMMA:
    {
        // Params ::= , Type Pointer id Array Params
        matchOrSkip(COMMA, sync_Params);

        Type_Node *type = Type();
        Pointer_Node *pointer = Pointer();

        Token_Node *id = new Token_Node(ID, getLexeme());
        matchOrSkip(ID, sync_Params);

        Array_Node *array = Array();

        Params_Node *parameters = new Params_Node(id, type, pointer, array, Params());
        return parameters;
    }
    case RPAREN:
        // Params ::= ε
        return nullptr;
    default:
        defaultError(sync_Params);
        return nullptr;
    }
}

int RDParser::sync_FunctionDecl[] = {TYPEDEF, ID, INTEGER, LONG, FLOAT, BOOL, CHAR, DOUBLE, END_OF_FILE};
Function_Node *RDParser::FunctionDecl(Token_Node *id, Type_Node *type, Pointer_Node *pointer, VarList_Node *varlist)
{
    printf("FunctionDecl\n");
    switch (lookAhead)
    {
    case LPAREN:
    {
        // FunctionDecl ::= ( Params ) { StmtList }
        matchOrSkip(LPAREN, sync_FunctionDecl);
        Params_Node *parameters = Params();
        matchOrSkip(RPAREN, sync_FunctionDecl);
        matchOrSkip(LBRACE, sync_FunctionDecl);

        Function_Node *functionlist = new Function_Node(type, id, varlist, StmtList(), parameters);

        matchOrSkip(RBRACE, sync_FunctionDecl);

        return functionlist;
    }
    default:
        defaultError(sync_FunctionDecl);
    }
    return nullptr;
}

int RDParser::sync_StmtList[] = {RBRACE, CASE, END_OF_FILE};
StmtList_Node *RDParser::StmtList()
{
    printf("StmtList\n");
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
    {
        // StmtList ::= Stmt StmtListK
        Stmt_Node *stmt = Stmt();
        StmtList_Node *stmtListK = StmtListK();
        StmtList_Node *stmtlist = new StmtList_Node(stmt, stmtListK);
        return stmtlist;
    }
    default:
        defaultError(sync_StmtList);
    }
    return nullptr;
}

int RDParser::sync_StmtListK[] = {RBRACE, CASE, END_OF_FILE};
StmtList_Node *RDParser::StmtListK()
{
    printf("StmtListK\n");
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
    {
        // StmtListK ::= StmtList
        return StmtList();
    }
    case RBRACE:
    case CASE:
        // StmtListK ::= ε
        return nullptr;
    default:
        defaultError(sync_StmtListK);
        return nullptr;
    }
}

int RDParser::sync_CaseBlock[] = {RBRACE, END_OF_FILE};
CaseBlock_Node *RDParser::CaseBlock()
{
    printf("CaseBlock\n");
    switch (lookAhead)
    {
    case CASE:
    {
        // CaseBlock ::= case num_int : CaseBlockL
        matchOrSkip(CASE, sync_CaseBlock);

        Token_Node *numInt = new Token_Node(NUM_INT, getLexeme());
        matchOrSkip(NUM_INT, sync_CaseBlock);
        matchOrSkip(COLON, sync_CaseBlock);

        return CaseBlockL(numInt);
    }
    default:
        defaultError(sync_CaseBlock);
        return nullptr;
    }
}

int RDParser::sync_CaseBlockL[] = {RBRACE, END_OF_FILE};
CaseBlock_Node *RDParser::CaseBlockL(Token_Node *token)
{
    printf("CaseBlockL\n");
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
    {
        // CaseBlockL ::= StmtList CaseBlockF
        CaseBlock_Node *caseBlockNode = new CaseBlock_Node(token, StmtList(), CaseBlockF());
        return caseBlockNode;
    }
    case CASE:
    {
        // CaseBlockL ::= CaseBlock
        CaseBlock_Node *caseBlockNode = new CaseBlock_Node(token, nullptr, CaseBlock());
        return caseBlockNode;
    }
    default:
        defaultError(sync_CaseBlockL);
    }
    return nullptr;
}

int RDParser::sync_CaseBlockF[] = {RBRACE, END_OF_FILE};
CaseBlock_Node *RDParser::CaseBlockF()
{
    printf("CaseBlockF\n");
    switch (lookAhead)
    {
    case RBRACE:
        // CaseBlockF ::= ε
        return nullptr;
    case CASE:
    {
        // CaseBlockF ::= CaseBlock
        CaseBlock_Node *caseBlockNode = CaseBlock();
        return caseBlockNode;
    }
    default:
        defaultError(sync_CaseBlockF);
    }
    return nullptr;
}

int RDParser::sync_Stmt[] = {RBRACE, IF, WHILE, SWITCH, BREAK, PRINT, READLN, RETURN, THROW, LBRACE, TRY, ID, INTEGER, LONG, FLOAT, BOOL, CHAR, DOUBLE, MULT, AMP, CATCH, CASE, END_OF_FILE};
Stmt_Node *RDParser::Stmt()
{
    printf("Stmt\n");
    switch (lookAhead)
    {
    case ID:
        // Stmt ::= id FatoraStmt
        matchOrSkip(ID, sync_Stmt);
        return FatoraStmt();
    case LBRACE:
    {
        // Stmt ::= { StmtList }
        matchOrSkip(LBRACE, sync_Stmt);
        StmtList_Node *stmtList = StmtList();

        matchOrSkip(RBRACE, sync_Stmt);

        return stmtList;
    }
    case MULT:
    {
        // Stmt ::= * id = Expr ;
        Token_Node *mult = new Token_Node(MULT, getLexeme());
        matchOrSkip(MULT, sync_Stmt);
        matchOrSkip(ID, sync_Stmt);
        matchOrSkip(ASSIGN, sync_Stmt);
        Exp_Node *exp = Expr();

        matchOrSkip(SEMICOLON, sync_Stmt);

        MultiplicationOP_Node *op = new MultiplicationOP_Node(mult, exp, nullptr);
        return op;
    }
    case INTEGER:
    case LONG:
    case FLOAT:
    case BOOL:
    case CHAR:
    case DOUBLE:
    {
        // Stmt ::= TypePure IdList ;
        Type_Node *typenode = TypePure();
        NameDecl_Node *idlist = IdList();
        matchOrSkip(SEMICOLON, sync_Stmt);

        VarList_Node *varlist = new VarList_Node(typenode, idlist, nullptr);
        return varlist;
    }
    case IF:
    {
        // Stmt ::= if ( Expr ) { StmtList } IfOpt
        matchOrSkip(IF, sync_Stmt);
        matchOrSkip(LPAREN, sync_Stmt);
        Exp_Node *exp = Expr();

        matchOrSkip(RPAREN, sync_Stmt);
        Stmt_Node *stmt = Stmt();
        Stmt_Node *elseOpt = ElseOpt();

        matchOrSkip(LBRACE, sync_Stmt);

        StmtList_Node *stmtlist = new StmtList_Node(stmt, StmtList());

        matchOrSkip(RBRACE, sync_Stmt);

        If_Node *ifOpt = new If_Node(exp, IfOpt(), elseOpt);

        return ifOpt;
    }
    case WHILE:
    {
        // Stmt ::= while ( Expr ) Stmt
        matchOrSkip(WHILE, sync_Stmt);
        matchOrSkip(LPAREN, sync_Stmt);
        Exp_Node *exp = Expr();

        matchOrSkip(RPAREN, sync_Stmt);

        While_Node *whileNode = new While_Node(exp, Stmt());
        return whileNode;
    }
    case SWITCH:
    {
        // Stmt ::= switch ( Expr ) { CaseBlock }
        matchOrSkip(SWITCH, sync_Stmt);
        matchOrSkip(LPAREN, sync_Stmt);
        Exp_Node *exp = Expr();

        matchOrSkip(RPAREN, sync_Stmt);
        matchOrSkip(LBRACE, sync_Stmt);

        CaseBlock_Node *caseBlock = CaseBlock();

        matchOrSkip(RBRACE, sync_Stmt);

        Switch_Node *switchNode = new Switch_Node(exp, caseBlock);
        return switchNode;
    }
    case BREAK:
    {
        // Stmt ::= break ;
        matchOrSkip(BREAK, sync_Stmt);
        Break_Node *breakNode = new Break_Node();

        matchOrSkip(SEMICOLON, sync_Stmt);

        return breakNode;
    }
    case PRINT:
    {
        // Stmt ::= print ( ExprList ) ;
        matchOrSkip(PRINT, sync_Stmt);
        matchOrSkip(LPAREN, sync_Stmt);
        ExpList_Node *exprList = ExprList();

        matchOrSkip(RPAREN, sync_Stmt);
        matchOrSkip(SEMICOLON, sync_Stmt);

        PrintLn_Node *printNode = new PrintLn_Node(exprList);
        return printNode;
    }
    case READLN:
    {
        // Stmt ::= readln ( Expr ) ;
        matchOrSkip(READLN, sync_Stmt);
        matchOrSkip(LPAREN, sync_Stmt);
        Exp_Node *exp = Expr();

        matchOrSkip(RPAREN, sync_Stmt);
        matchOrSkip(SEMICOLON, sync_Stmt);

        Read_Node *readNode = new Read_Node(exp);
        return readNode;
    }
    case RETURN:
    {
        // Stmt ::= return Expr ;
        matchOrSkip(RETURN, sync_Stmt);
        Exp_Node *exp = Expr();

        matchOrSkip(SEMICOLON, sync_Stmt);

        Return_Node *returnNode = new Return_Node(exp);
        return returnNode;
    }
    case THROW:
    {
        // Stmt ::= throw ;
        matchOrSkip(THROW, sync_Stmt);
        matchOrSkip(SEMICOLON, sync_Stmt);

        Throw_Node *throwNode = new Throw_Node();
        return throwNode;
    }
    case TRY:
    {
        // Stmt ::= try Stmt catch ( ... ) Stmt
        matchOrSkip(TRY, sync_Stmt);

        Stmt_Node *stmt1 = Stmt();

        matchOrSkip(CATCH, sync_Stmt);
        matchOrSkip(LPAREN, sync_Stmt);
        matchOrSkip(TRIPLE_DOT, sync_Stmt);
        matchOrSkip(RPAREN, sync_Stmt);

        Stmt_Node *stmt2 = Stmt();

        Try_Node *tryNode = new Try_Node(stmt1, stmt2);
        return tryNode;
    }
    case AMP:
    {
        // Stmt ::= & id = Expr ;
        matchOrSkip(AMP, sync_Stmt);
        matchOrSkip(ID, sync_Stmt);
        matchOrSkip(ASSIGN, sync_Stmt);
        Exp_Node *exp = Expr();
        matchOrSkip(SEMICOLON, sync_Stmt);

        AddressValue_Node *address = new AddressValue_Node(exp);
        return address;
    }
    default:
        defaultError(sync_Stmt);
    }
    return nullptr;
}

int RDParser::sync_FatoraStmt[] = {RBRACE, IF, WHILE, SWITCH, BREAK, PRINT, READLN, RETURN, THROW, LBRACE, TRY, ID, INTEGER, LONG, FLOAT, BOOL, CHAR, DOUBLE, MULT, AMP, CATCH, CASE, END_OF_FILE};
Stmt_Node *RDParser::FatoraStmt()
{
    printf("FatoraStmt\n");
    switch (lookAhead)
    {
    case ID:
    case SEMICOLON:
    case COMMA:
    case MULT:
    {
        // FatoraStmt ::= IdList ;
        NameDecl_Node *idlist = IdList();

        matchOrSkip(SEMICOLON, sync_FatoraStmt);

        return nullptr;
    }
    case LBRACKET:
    case ASSIGN:
    {
        // FatoraStmt ::= ArrayAcesso = Expr ;
        Exp_Node *array = ArrayAcesso();
        matchOrSkip(ASSIGN, sync_FatoraStmt);
        Exp_Node *exp = Expr();

        matchOrSkip(SEMICOLON, sync_FatoraStmt);

        Assign_Node *assign = new Assign_Node(array, exp);

        return array;
    }
    case LPAREN:
    {
        // FatoraStmt ::= ( ExprList ) ;
        matchOrSkip(LPAREN, sync_FatoraStmt);

        Token_Node *id = new Token_Node(ID, getLexeme());
        ExpList_Node *explist = ExprList();

        matchOrSkip(RPAREN, sync_FatoraStmt);
        matchOrSkip(SEMICOLON, sync_FatoraStmt);

        Call_Node *call = new Call_Node(id, explist);

        return call;
    }
    default:
        defaultError(sync_FatoraStmt);
    }
    return nullptr;
}

int RDParser::sync_IfOpt[] = {RBRACE, IF, WHILE, SWITCH, BREAK, PRINT, READLN, RETURN, THROW, LBRACE, TRY, ID, INTEGER, LONG, FLOAT, BOOL, CHAR, DOUBLE, MULT, AMP, CATCH, CASE, END_OF_FILE};
Stmt_Node *RDParser::IfOpt()
{
    printf("IfOpt\n");
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
        return nullptr;
    case ELSE:
    {
        // IfOpt ::= else ElseOpt
        matchOrSkip(ELSE, sync_IfOpt);

        return ElseOpt();
    }
    default:
        defaultError(sync_IfOpt);
    }
    return nullptr;
}

int RDParser::sync_ElseOpt[] = {RBRACE, IF, WHILE, SWITCH, BREAK, PRINT, READLN, RETURN, THROW, LBRACE, TRY, ID, INTEGER, LONG, FLOAT, BOOL, CHAR, DOUBLE, MULT, AMP, CATCH, CASE, END_OF_FILE};
Stmt_Node *RDParser::ElseOpt()
{
    printf("ElseOpt\n");
    switch (lookAhead)
    {
    case LBRACE:
    {
        // ElseOpt ::= { StmtList }
        matchOrSkip(LBRACE, sync_ElseOpt);

        StmtList_Node *stmtlist = StmtList();

        matchOrSkip(RBRACE, sync_ElseOpt);

        return stmtlist;
    }
    case IF:
    {
        // ElseOpt ::= if ( Expr ) { StmtList } IfOpt
        matchOrSkip(IF, sync_ElseOpt);
        matchOrSkip(LPAREN, sync_ElseOpt);
        Exp_Node *exp = Expr();

        matchOrSkip(RPAREN, sync_ElseOpt);
        matchOrSkip(LBRACE, sync_ElseOpt);

        StmtList_Node *stmtlistElse = StmtList();

        matchOrSkip(RBRACE, sync_ElseOpt);

        If_Node *ifOpt = new If_Node(exp, IfOpt(), stmtlistElse);
        return ifOpt;
    }
    default:
        defaultError(sync_ElseOpt);
        return nullptr;
    }
}

int RDParser::sync_ArrayAcesso[] = {ASSIGN, RPAREN, SEMICOLON, RBRACKET, COMMA, OR, AND, EQUAL, NOT_EQUAL, LE, LEQ, GTE, GT, SUM, MINUS, VERBAR, MULT, DIV, MOD, AMP, END_OF_FILE};
Exp_Node *RDParser::ArrayAcesso()
{
    printf("ArrayAcesso\n");
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
        return nullptr;
    case LBRACKET:
    {
        // ArrayAcesso ::= [ Expr ] ArrayAcesso
        matchOrSkip(LBRACKET, sync_ArrayAcesso);
        Exp_Node *exp = Expr();

        matchOrSkip(RBRACKET, sync_ArrayAcesso);
        Token_Node *id = new Token_Node(ID, getLexeme());
        ArrayAcesso();
        return exp;
    }
    default:
        defaultError(sync_ArrayAcesso);
        return nullptr;
    }
}

int RDParser::sync_ExprList[] = {RPAREN, END_OF_FILE};
ExpList_Node *RDParser::ExprList()
{
    printf("ExprList\n");
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
    {
        // ExprList ::= Expr ExprListTail
        ExpList_Node *explist = new ExpList_Node(Expr(), ExprListTail());
        return explist;
    }
    case RPAREN:
        // ExprList ::= ε
        return nullptr;
    default:
        defaultError(sync_ExprList);
    }
    return nullptr;
}

int RDParser::sync_ExprListTail[] = {RPAREN, END_OF_FILE};
ExpList_Node *RDParser::ExprListTail()
{
    printf("ExprListTail\n");
    switch (lookAhead)
    {
    case COMMA:
    {
        // ExprListTail ::= , Expr ExprListTail
        matchOrSkip(COMMA, sync_ExprListTail);
        ExpList_Node *explist = new ExpList_Node(Expr(), ExprListTail());
        return explist;
    }
    case RPAREN:
        // ExprListTail ::= ε
        return nullptr;
    default:
        defaultError(sync_ExprListTail);
    }
    return nullptr;
}

int RDParser::sync_Expr[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, END_OF_FILE};
Exp_Node *RDParser::Expr()
{
    printf("Expr\n");
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
    {
        // Expr ::= Expr1 ExprL
        Expr1();
        return ExprL();
    }
    default:
        defaultError(sync_Expr);
    }
    return nullptr;
}

int RDParser::sync_ExprL[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, END_OF_FILE};
Exp_Node *RDParser::ExprL()
{
    printf("ExprL\n");
    switch (lookAhead)
    {
    case SEMICOLON:
    case COMMA:
    case RBRACKET:
    case RPAREN:
        // ExprL ::= ε
        return nullptr;
    case ASSIGN:
    {
        // ExprL ::= = Expr
        matchOrSkip(ASSIGN, sync_ExprL);
        return Expr();
    }
    default:
        defaultError(sync_ExprL);
    }
    return nullptr;
}

int RDParser::sync_Expr1[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, END_OF_FILE};
Exp_Node *RDParser::Expr1()
{
    printf("Expr1\n");
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
    return nullptr;
}

int RDParser::sync_Expr1L[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, END_OF_FILE};
Exp_Node *RDParser::Expr1L()
{
    printf("Expr1L\n");
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
    return nullptr;
}

int RDParser::sync_Expr2[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, OR, END_OF_FILE};
Exp_Node *RDParser::Expr2()
{
    printf("Expr2\n");
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
    return nullptr;
}

int RDParser::sync_Expr2L[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, OR, END_OF_FILE};
Exp_Node *RDParser::Expr2L()
{
    printf("Expr2L\n");
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
    return nullptr;
}

int RDParser::sync_Expr3[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, OR, AND, END_OF_FILE};
Exp_Node *RDParser::Expr3()
{
    printf("Expr3\n");
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
    return nullptr;
}

int RDParser::sync_Expr3L[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, OR, AND, END_OF_FILE};
Exp_Node *RDParser::Expr3L()
{
    printf("Expr3L\n");
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
    return nullptr;
}

int RDParser::sync_Expr4[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, OR, AND, EQUAL, NOT_EQUAL, END_OF_FILE};
Exp_Node *RDParser::Expr4()
{
    printf("Expr4\n");
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
    return nullptr;
}

int RDParser::sync_Expr4L[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, OR, AND, EQUAL, NOT_EQUAL, END_OF_FILE};
Exp_Node *RDParser::Expr4L()
{
    printf("Expr4L\n");
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
    return nullptr;
}

int RDParser::sync_Expr5[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, OR, AND, EQUAL, NOT_EQUAL, LE, LEQ, GTE, GT, END_OF_FILE};
Exp_Node *RDParser::Expr5()
{
    printf("Expr5\n");
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
    return nullptr;
}

int RDParser::sync_Expr5L[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, OR, AND, EQUAL, NOT_EQUAL, LE, LEQ, GTE, GT, END_OF_FILE};
Exp_Node *RDParser::Expr5L()
{
    printf("Expr5L\n");
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
    return nullptr;
}

int RDParser::sync_Expr6[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, OR, AND, EQUAL, NOT_EQUAL, LE, LEQ, GTE, GT, SUM, MINUS, VERBAR, END_OF_FILE};
Exp_Node *RDParser::Expr6()
{
    printf("Expr6\n");
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
    return nullptr;
}

int RDParser::sync_Expr6L[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, OR, AND, EQUAL, NOT_EQUAL, LE, LEQ, GTE, GT, SUM, MINUS, VERBAR, END_OF_FILE};
Exp_Node *RDParser::Expr6L()
{
    printf("Expr6L\n");
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
    return nullptr;
}

int RDParser::sync_Expr7[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, OR, AND, EQUAL, NOT_EQUAL, LE, LEQ, GTE, GT, SUM, MINUS, VERBAR, MULT, DIV, MOD, AMP, END_OF_FILE};
Exp_Node *RDParser::Expr7()
{
    printf("Expr7\n");
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
    {
        // Expr7 ::= Primary
        Exp_Node *primary = Primary();
        return primary;
    }
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
    return nullptr;
}

int RDParser::sync_Primary[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, OR, AND, EQUAL, NOT_EQUAL, LE, LEQ, GTE, GT, SUM, MINUS, VERBAR, MULT, DIV, MOD, AMP, END_OF_FILE};
Exp_Node *RDParser::Primary()
{
    printf("Primary\n");
    switch (lookAhead)
    {
    case ID:
        // Primary ::= id PrimaryFatora
        matchOrSkip(ID, sync_Primary);
        return PrimaryFatora();
    case MULT:
    {
        // Primary ::= * id
        matchOrSkip(MULT, sync_Primary);

        Exp_Node *exp = new Exp_Node();
        exp->setType(ID);
        exp->setLexeme(getLexeme());
        matchOrSkip(ID, sync_Primary);
        return exp;
    }
    case NUM_INT:
    {
        // Primary ::= num_int
        Exp_Node *exp = new Exp_Node();
        exp->setType(NUM_INT);
        exp->setLexeme(getLexeme());
        matchOrSkip(NUM_INT, sync_Primary);
        return exp;
    }
    case LPAREN:
    {
        // Primary ::= ( Expr )
        matchOrSkip(LPAREN, sync_Primary);

        Exp_Node *exp = Expr();
        matchOrSkip(RPAREN, sync_Primary);
        return exp;
    }
    case AMP:
    {
        // Primary ::= & id
        matchOrSkip(AMP, sync_Primary);

        Exp_Node *exp = new Exp_Node();
        exp->setType(ID);
        exp->setLexeme(getLexeme());
        matchOrSkip(ID, sync_Primary);
        return exp;
    }
    case NUM_REAL:
    {
        // Primary ::= num_real
        Exp_Node *exp = new Exp_Node();
        exp->setType(NUM_REAL);
        exp->setLexeme(getLexeme());
        matchOrSkip(NUM_REAL, sync_Primary);
        return exp;
    }
    case LITERAL:
    {
        // Primary ::= literal
        Exp_Node *exp = new Exp_Node();
        exp->setType(LITERAL);
        exp->setLexeme(getLexeme());
        matchOrSkip(LITERAL, sync_Primary);
        return exp;
    }
    case ASCII:
    {
        // Primary ::= ascii
        Exp_Node *exp = new Exp_Node();
        exp->setType(ASCII);
        exp->setLexeme(getLexeme());
        matchOrSkip(ASCII, sync_Primary);
        return exp;
    }
    case TRUE:
    {
        // Primary ::= true
        Exp_Node *exp = new Exp_Node();
        exp->setType(TRUE);
        matchOrSkip(TRUE, sync_Primary);
        return exp;
    }
    case FALSE:
    {
        // Primary ::= false
        Exp_Node *exp = new Exp_Node();
        exp->setType(FALSE);
        matchOrSkip(FALSE, sync_Primary);
        return exp;
    }
    default:
        defaultError(sync_Primary);
    }
    return nullptr;
}

int RDParser::sync_PrimaryFatora[] = {RPAREN, SEMICOLON, RBRACKET, COMMA, ASSIGN, OR, AND, EQUAL, NOT_EQUAL, LE, LEQ, GTE, GT, SUM, MINUS, VERBAR, MULT, DIV, MOD, AMP, END_OF_FILE};
Exp_Node *RDParser::PrimaryFatora()
{
    printf("PrimaryFatora\n");
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
        return ArrayAcesso();
    case LPAREN:
    {
        // PrimaryFatora ::= ( ExprList )
        matchOrSkip(LPAREN, sync_PrimaryFatora);

        ExprList();
        matchOrSkip(RPAREN, sync_PrimaryFatora);
        return nullptr;
    }
    default:
        defaultError(sync_PrimaryFatora);
    }
    return nullptr;
}