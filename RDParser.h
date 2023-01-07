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
    Program_Node *Program(Program_Node *root);

    static int sync_TypeDecl[];
    TypeList_Node *TypeDecl(TypeList_Node *typeDecl);

    static int sync_FatoraPg[];
    void FatoraPg();

    static int sync_IdList[];
    VarList_Node *IdList(VarList_Node *idList);

    static int sync_Pointer[];
    Pointer_Node *Pointer(Pointer_Node *pointer);

    static int sync_Type[];
    Type_Node *Type(Type_Node *type);

    static int sync_TypePure[];
    void TypePure();

    static int sync_Array[];
    Array_Node *Array(Array_Node *array);

    static int sync_VarDecl[];
    NameDecl_Node *VarDecl(NameDecl_Node *varDecl);

    static int sync_Params[];
    void Params();

    static int sync_FunctionDecl[];
    FunctionList_Node *FunctionDecl(FunctionList_Node *functionDecl);

    static int sync_StmtList[];
    StmtList_Node *StmtList(StmtList_Node *stmtList);

    static int sync_StmtListK[];
    void StmtListK();

    static int sync_CaseBlock[];
    CaseBlock_Node *CaseBlock(CaseBlock_Node *caseBlock);

    static int sync_CaseBlockL[];
    void CaseBlockL();

    static int sync_CaseBlockF[];
    void CaseBlockF();

    static int sync_Stmt[];
    Stmt_Node *Stmt(Stmt_Node *stmt);

    static int sync_FatoraStmt[];
    void FatoraStmt();

    static int sync_IfOpt[];
    If_Node *IfOpt(If_Node *ifOpt);

    static int sync_ElseOpt[];
    If_Node *ElseOpt(If_Node *elseOpt);

    static int sync_ArrayAcesso[];
    void ArrayAcesso();

    static int sync_ExprList[];
    ExpList_Node *ExprList(ExpList_Node *exprList);

    static int sync_ExprListTail[];
    void ExprListTail();

    static int sync_Expr[];
    void Expr();

    static int sync_ExprL[];
    void ExprL();

    static int sync_Expr1[];
    void Expr1();

    static int sync_Expr1L[];
    void Expr1L();

    static int sync_Expr2[];
    void Expr2();

    static int sync_Expr2L[];
    void Expr2L();

    static int sync_Expr3[];
    void Expr3();

    static int sync_Expr3L[];
    void Expr3L();

    static int sync_Expr4[];
    void Expr4();

    static int sync_Expr4L[];
    void Expr4L();

    static int sync_Expr5[];
    void Expr5();

    static int sync_Expr5L[];
    void Expr5L();

    static int sync_Expr6[];
    void Expr6();

    static int sync_Expr6L[];
    void Expr6L();

    static int sync_Expr7[];
    void Expr7();

    static int sync_Primary[];
    Exp_Node *Primary(Exp_Node *primary);

    static int sync_PrimaryFatora[];
    void PrimaryFatora();

public:
    Program_Node *root;
    Program_Node *program;
    Print_AST *visitor;

    RDParser();
    ~RDParser();

    void startParser();
};

#endif // RDPARSER_H
