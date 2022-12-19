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

    void error(int expectedToken, const int *syncArr);

    // Functions of nonterminals
    static int sync_Program[];
    void Program();

    static int sync_Type[];
    void Type();

    static int sync_IdList[];
    void IdList();

    static int sync_IdListK2[];
    void IdListK2();

    static int sync_IdListK3[];
    void IdListK3();

    static int sync_Array[];
    void Array();

    static int sync_TypeDecl[];
    void TypeDecl();

    static int sync_VarFn[];
    void VarFn();

    static int sync_VarFnK[];
    void VarFnK();

    static int sync_VarFnL[];
    void VarFnL();

    static int sync_VarDecl[];
    void VarDecl();

    static int sync_VarDeclK[];
    void VarDeclK();

    static int sync_FunctionDecl[];
    void FunctionDecl();

    static int sync_FunctionDeclK[];
    void FunctionDeclK();

    static int sync_FunctionDeclL[];
    void FunctionDeclL();

    static int sync_FormalRest[];
    void FormalRest();

    static int sync_FormalRestK[];
    void FormalRestK();

    static int sync_FormalList[];
    void FormalList();

    static int sync_FormalListK[];
    void FormalListK();

    static int sync_FunctionBody[];
    void FunctionBody();

    static int sync_FunctionBodyL[];
    void FunctionBodyL();

    static int sync_ExprList[];
    void ExprList();

    static int sync_ExprListTail[];
    void ExprListTail();

    static int sync_ExprListTailL[];
    void ExprListTailL();

    static int sync_StmtList[];
    void StmtList();

    static int sync_StmtListK[];
    void StmtListK();

    static int sync_StmtList2[];
    void StmtList2();

    static int sync_StmtList2K[];
    void StmtList2K();

    static int sync_CaseBlock[];
    void CaseBlock();

    static int sync_CaseBlockL[];
    void CaseBlockL();

    static int sync_Stmt[];
    void Stmt();

    static int sync_Stmt2[];
    void Stmt2();

    static int sync_IfOpt[];
    void IfOpt();

    static int sync_ElseOpt[];
    void ElseOpt();

    static int sync_ExpSemID[];
    void ExpSemID();

    static int sync_ExpSemIDL[];
    void ExpSemIDL();

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
    void Primary();

    static int sync_PrimaryL[];
    void PrimaryL();

public:
    RDParser();
    ~RDParser();

    void startParser();
};

#endif // RDPARSER_H
