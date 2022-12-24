#ifndef RDPARSER_H
#define RDPARSER_H

#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <string>
#include "LexicalAnalyzer.h"
#include "ErrorManager.h"

class RDParser
{
private:
    int lookAhead;

    void nextToken();
    void match(int token);
    void matchOrSkip(int token, const int *syncArr);

    void writeError(int expectedToken);
    void syncError(const int *syncArr);

    // Functions of nonterminals
    static int sync_Program[];
    void Program();
    Program_Node *Program_AST(FunctionList_Node *functionlist, TypeList_Node *typelist, VarList_Node *varlist);

    static int sync_Type[];
    void Type();
    Type_Node *Type_AST(TokenNode *id, const char *lexeme);

    static int sync_IdList[];
    void IdList();
    VarList_Node *VarList_IdList(NameDecl_Node *namedecl, VarList_Node *next);

    static int sync_IdListK2[];
    void IdListK2();
    VarList_Node *VarList_IdListK2(NameDecl_Node *namedecl, VarList_Node *next);

    static int sync_IdListK3[];
    void IdListK3();
    VarList_Node *VarList_IdListK3(NameDecl_Node *namedecl, VarList_Node *next);

    static int sync_Array[];
    void Array();
    Array_Node *Array_AST(Exp_Node *exp, ExpList_Node *explist);

    static int sync_TypeDecl[];
    void TypeDecl();
    TypeList_Node *TypeList_TypeDecl(VarList_Node *varlist, TokenNode *id, TypeList_Node *next);

    static int sync_VarFn[];
    void VarFn();
    VarList_Node *VarList_VarFn(NameDecl_Node *namedecl, VarList_Node *next);

    static int sync_VarFnK[];
    void VarFnK();
    VarList_Node *VarList_VarFnK(NameDecl_Node *namedecl, VarList_Node *next);

    static int sync_VarFnL[];
    void VarFnL();
    VarList_Node *VarList_VarFnL(NameDecl_Node *namedecl, VarList_Node *next);

    static int sync_VarDecl[];
    void VarDecl();
    VarList_Node *VarList_VarDecl(NameDecl_Node *namedecl, VarList_Node *next);

    static int sync_VarDeclK[];
    void VarDeclK();
    VarList_Node *VarList_VarDeclK(NameDecl_Node *namedecl, VarList_Node *next);

    static int sync_FunctionDecl[];
    void FunctionDecl();
    FunctionList_Node *FunctionList_Decl(Type_Node *type, TokenNode *id, VarList_Node *varlist, StmtList_Node *stmtlist, FunctionList_Node *next);

    static int sync_FunctionDeclK[];
    void FunctionDeclK();
    FunctionList_Node *FunctionList_DeclK(Type_Node *type, TokenNode *id, VarList_Node *varlist, StmtList_Node *stmtlist, FunctionList_Node *next);

    static int sync_FunctionDeclL[];
    void FunctionDeclL();
    FunctionList_Node *FunctionList_DeclL(Type_Node *type, TokenNode *id, VarList_Node *varlist, StmtList_Node *stmtlist, FunctionList_Node *next);

    static int sync_FormalRest[];
    void FormalRest();
    FunctionList_Node *FunctionList_FormalRest(Type_Node *type, TokenNode *id, VarList_Node *varlist, StmtList_Node *stmtlist, FunctionList_Node *next);

    static int sync_FormalRestK[];
    void FormalRestK();
    FunctionList_Node *FunctionList_FormalRestK(Type_Node *type, TokenNode *id, VarList_Node *varlist, StmtList_Node *stmtlist, FunctionList_Node *next);

    static int sync_FormalList[];
    void FormalList();
    FunctionList_Node *FunctionList_FormalList(Type_Node *type, TokenNode *id, VarList_Node *varlist, StmtList_Node *stmtlist, FunctionList_Node *next);

    static int sync_FormalListK[];
    void FormalListK();
    FunctionList_Node *FunctionList_FormalListK(Type_Node *type, TokenNode *id, VarList_Node *varlist, StmtList_Node *stmtlist, FunctionList_Node *next);

    static int sync_FunctionBody[];
    void FunctionBody();
    FunctionList_Node *FunctionList_Body(Type_Node *type, TokenNode *id, VarList_Node *varlist, StmtList_Node *stmtlist, FunctionList_Node *next);

    static int sync_FunctionBodyL[];
    void FunctionBodyL();
    FunctionList_Node *FunctionList_BodyL(Type_Node *type, TokenNode *id, VarList_Node *varlist, StmtList_Node *stmtlist, FunctionList_Node *next);

    static int sync_ExprList[];
    void ExprList();
    ExpList_Node *ExpList_AST(Exp_Node *exp, ExpList_Node *next);

    static int sync_ExprListTail[];
    void ExprListTail();
    ExpList_Node *ExpListTail_AST(Exp_Node *exp, ExpList_Node *next);

    static int sync_ExprListTailL[];
    void ExprListTailL();
    ExpList_Node *ExpListTailL_AST(Exp_Node *exp, ExpList_Node *next);

    static int sync_StmtList[];
    void StmtList();
    StmtList_Node *StmtList_AST(Stmt_Node *stmt, StmtList_Node *next);

    static int sync_StmtListK[];
    void StmtListK();
    StmtList_Node *StmtListK_AST(Stmt_Node *stmt, StmtList_Node *next);

    static int sync_StmtList2[];
    void StmtList2();
    StmtList_Node *StmtList2_AST(Stmt_Node *stmt, StmtList_Node *next);

    static int sync_StmtList2K[];
    void StmtList2K();
    StmtList_Node *StmtList2K_AST(Stmt_Node *stmt, StmtList_Node *next);

    static int sync_CaseBlock[];
    void CaseBlock();
    CaseBlock_Node *CaseBlock_AST(TokenNode *num, StmtList_Node *stmtlist, CaseBlock_Node *next);

    static int sync_CaseBlockL[];
    void CaseBlockL();
    CaseBlock_Node *CaseBlockL_AST(TokenNode *num, StmtList_Node *stmtlist, CaseBlock_Node *next);

    static int sync_Stmt[];
    void Stmt();
    Stmt_Node *StmtNode1();

    static int sync_Stmt2[];
    void Stmt2();
    Stmt_Node *StmtNode2();

    static int sync_IfOpt[];
    void IfOpt();
    If_Node *If_if();

    static int sync_ElseOpt[];
    void ElseOpt();
    If_Node *If_Else();

    static int sync_ExpSemID[];
    void ExpSemID();
    Exp_Node *ExpSemId();

    static int sync_ExpSemIDL[];
    void ExpSemIDL();
    Exp_Node *ExpSemIdL();

    static int sync_Expr[];
    void Expr();
    Exp_Node *ExpRoot();

    static int sync_ExprL[];
    void ExprL();
    Exp_Node *ExpAssign();

    static int sync_Expr1[];
    void Expr1();
    Exp_Node *Exp1();

    static int sync_Expr1L[];
    void Expr1L();
    Exp_Node *ExpOr();

    static int sync_Expr2[];
    void Expr2();
    Exp_Node *Exp2();

    static int sync_Expr2L[];
    void Expr2L();
    Exp_Node *ExpAnd();

    static int sync_Expr3[];
    void Expr3();
    Exp_Node *Exp3();

    static int sync_Expr3L[];
    void Expr3L();
    Exp_Node *ExpEquality();

    static int sync_Expr4[];
    void Expr4();
    Exp_Node *Exp4();

    static int sync_Expr4L[];
    void Expr4L();
    Exp_Node *ExpRelational();

    static int sync_Expr5[];
    void Expr5();
    Exp_Node *Exp5();

    static int sync_Expr5L[];
    void Expr5L();
    Exp_Node *ExpAdd_Minus();

    static int sync_Expr6[];
    void Expr6();
    Exp_Node *Exp6();

    static int sync_Expr6L[];
    void Expr6L();
    Exp_Node *ExpMult_Div();

    static int sync_Expr7[];
    void Expr7();
    Exp_Node *ExpUnary();

    static int sync_Primary[];
    void Primary();
    Exp_Node *Exp_Primary();

    static int sync_PrimaryL[];
    void PrimaryL();
    Exp_Node *Exp_PrimaryL();

public:
    Program_Node *program;
    Print_AST *visitor;

    RDParser();
    ~RDParser();

    void startParser();
};

#endif // RDPARSER_H
