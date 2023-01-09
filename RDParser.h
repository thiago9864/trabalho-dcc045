#ifndef RDPARSER_H
#define RDPARSER_H

#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <string>
#include "LexicalAnalyzer.h"
#include "ErrorManager.h"
#include "VisitorAST.h"

class RDParser
{
private:
    int lookAhead;

    void nextToken();
    void matchOrSkip(int token, const int *syncArr);

    void writeError(int expectedToken);
    void defaultError(const int *syncArr);
    void syncError(const int *syncArr);

    // Functions of nonterminals
    static int sync_Program[];
    Program_Node *Program(FunctionList_Node *functionlist, TypeList_Node *typelist, VarList_Node *varlist);

    static int sync_TypeDecl[];
    TypeList_Node *TypeDecl(TypeList_Node *typeDecl);

    static int sync_FatoraPg[];
    Program_Node *FatoraPg(Type_Node *type, Token_Node *id);

    static int sync_IdList[];
    VarList_Node *IdList();

    static int sync_Pointer[];
    Pointer_Node *Pointer();

    static int sync_Type[];
    Type_Node *Type();

    static int sync_TypePure[];
    Type_Node *TypePure();

    static int sync_Array[];
    Array_Node *Array();

    static int sync_VarDecl[];
    NameDecl_Node *VarDecl();

    static int sync_Params[];
    void Params();

    static int sync_FunctionDecl[];
    FunctionList_Node *FunctionDecl();

    static int sync_StmtList[];
    StmtList_Node *StmtList();

    static int sync_StmtListK[];
    StmtList_Node *StmtListK();

    static int sync_CaseBlock[];
    CaseBlock_Node *CaseBlock();

    static int sync_CaseBlockL[];
    CaseBlock_Node *CaseBlockL(Token_Node *token);

    static int sync_CaseBlockF[];
    CaseBlock_Node *CaseBlockF();

    static int sync_Stmt[];
    Stmt_Node *Stmt();

    static int sync_FatoraStmt[];
    Stmt_Node *FatoraStmt();

    static int sync_IfOpt[];
    If_Node *IfOpt();

    static int sync_ElseOpt[];
    If_Node *ElseOpt();

    static int sync_ArrayAcesso[];
    void ArrayAcesso();

    static int sync_ExprList[];
    ExpList_Node *ExprList();

    static int sync_ExprListTail[];
    ExpList_Node *ExprListTail();

    static int sync_Expr[];
    Exp_Node *Expr();

    static int sync_ExprL[];
    Exp_Node *ExprL();

    static int sync_Expr1[];
    Exp_Node *Expr1();

    static int sync_Expr1L[];
    Exp_Node *Expr1L();

    static int sync_Expr2[];
    Exp_Node *Expr2();

    static int sync_Expr2L[];
    Exp_Node *Expr2L();

    static int sync_Expr3[];
    Exp_Node *Expr3();

    static int sync_Expr3L[];
    Exp_Node *Expr3L();

    static int sync_Expr4[];
    Exp_Node *Expr4();

    static int sync_Expr4L[];
    Exp_Node *Expr4L();

    static int sync_Expr5[];
    Exp_Node *Expr5();

    static int sync_Expr5L[];
    Exp_Node *Expr5L();

    static int sync_Expr6[];
    Exp_Node *Expr6();

    static int sync_Expr6L[];
    Exp_Node *Expr6L();

    static int sync_Expr7[];
    Exp_Node *Expr7();

    static int sync_Primary[];
    Exp_Node *Primary();

    static int sync_PrimaryFatora[];
    Exp_Node *PrimaryFatora();

public:
    Program_Node *root;
    Print_AST *visitor;

    RDParser();
    ~RDParser();

    void startParser();
};

#endif // RDPARSER_H
