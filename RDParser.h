#ifndef RDPARSER_H
#define RDPARSER_H

#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <string>
#include "LexicalAnalyzer.h"

class RDParser
{
private:
    int lookAhead;

    void nextToken();
    void match(int token);

    // Functions of nonterminals
    void Program();
    void Type();
    void IdList();
    void IdListK2();
    void IdListK3();
    void Array();
    void TypeDecl();
    void VarFn();
    void VarFnK();
    void VarFnL();
    void VarDecl();
    void VarDeclK();
    void FunctionDecl();
    void FunctionDeclK();
    void FunctionDeclL();
    void FormalRest();
    void FormalRestK();
    void FormalList();
    void FormalListK();
    void FunctionBody();
    void FunctionBodyL();
    void FunctionBody2L();
    void ExprList();
    void ExprListTail();
    void ExprListTailL();
    void StmtList();
    void StmtListK();
    void CaseBlock();
    void CaseBlockL();
    void Stmt();
    void IfOpt();
    void ElseOpt();
    void Expr();
    void ExprL();
    void Expr1();
    void Expr1L();
    void Expr2();
    void Expr2L();
    void Expr3();
    void Expr3L();
    void Expr4();
    void Expr4L();
    void Expr5();
    void Expr5L();
    void Expr6();
    void Expr6L();
    void Expr7();
    void Primary();
    void ExpSemID();
    void ExpSemIDL();
    void ExpSemID1();
    void ExpSemID1L();
    void ExpSemID2();
    void ExpSemID2L();
    void ExpSemID3();
    void ExpSemID3L();
    void ExpSemID4();
    void ExpSemID4L();
    void ExpSemID5();
    void ExpSemID5L();
    void ExpSemID6();
    void ExpSemID6L();
    void ExpSemID7();
    void PrimarySemID();

public:
    RDParser();
    ~RDParser();

    void startParser();
};

#endif // RDPARSER_H
