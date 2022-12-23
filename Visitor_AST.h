#ifndef VISITOR_AST_H
#define VISITOR_AST_H

#include "LexicalAnalyzer.h"
#include "Accept_AST.h"
#include <iostream>

class Root_Node;
class TokenNode_Node;
class Program_Node;
class VarList_Node;
class NameDecl_Node;
class FunctionList_Node;
class TypeList_Node;
class Type_Node;
class Pointer_Node;
class StmtList_Node;
class Stmt_Node;
class If_Node;
class While_Node;
class Switch_Node;
class Break_Node;
class PrintLn_Node;
class Read_Node;
class Return_Node;
class CaseBlock_Node;
class Throw_Node;
class ExpList_Node;
class Try_Node;
class Exp_Node;
class Assign_Node;
class NameExp_Node;
class PointerValueExp_Node;
class AddressValue_Node;
class PointerValue_Node;
class Array_Node;
class Call_Node;
class RelationalOP_Node;
class AdditionOP_Node;
class MultiplicationOP_Node;
class BooleanOP_Node;
class BitwiseOP_Node;
class True_Node;
class False_Node;
class Not_Node;
class Sign_Node;

class Visitor
{

public:
    virtual ~Visitor() = default;
    virtual void visit(TokenNode *node) = 0;
    virtual void visit(Program_Node *node) = 0;
    virtual void visit(VarList_Node *node) = 0;
    virtual void visit(NameDecl_Node *node) = 0;
    virtual void visit(FunctionList_Node *node) = 0;
    virtual void visit(TypeList_Node *node) = 0;
    virtual void visit(Type_Node *node) = 0;
    virtual void visit(Pointer_Node *node) = 0;
    virtual void visit(StmtList_Node *node) = 0;
    virtual void visit(Stmt_Node *node) = 0;
    virtual void visit(If_Node *node) = 0;
    virtual void visit(While_Node *node) = 0;
    virtual void visit(Switch_Node *node) = 0;
    virtual void visit(Break_Node *node) = 0;
    virtual void visit(PrintLn_Node *node) = 0;
    virtual void visit(Read_Node *node) = 0;
    virtual void visit(Return_Node *node) = 0;
    virtual void visit(CaseBlock_Node *node) = 0;
    virtual void visit(Throw_Node *node) = 0;
    virtual void visit(ExpList_Node *node) = 0;
    virtual void visit(Try_Node *node) = 0;
    virtual void visit(Exp_Node *node) = 0;
    virtual void visit(Assign_Node *node) = 0;
    virtual void visit(NameExp_Node *node) = 0;
    virtual void visit(PointerValueExp_Node *node) = 0;
    virtual void visit(AddressValue_Node *node) = 0;
    virtual void visit(PointerValue_Node *node) = 0;
    virtual void visit(Array_Node *node) = 0;
    virtual void visit(Call_Node *node) = 0;
    virtual void visit(RelationalOP_Node *node) = 0;
    virtual void visit(AdditionOP_Node *node) = 0;
    virtual void visit(MultiplicationOP_Node *node) = 0;
    virtual void visit(BooleanOP_Node *node) = 0;
    virtual void visit(BitwiseOP_Node *node) = 0;
    virtual void visit(True_Node *node) = 0;
    virtual void visit(False_Node *node) = 0;
    virtual void visit(Not_Node *node) = 0;
    virtual void visit(Sign_Node *node) = 0;
};

class Print_AST : public Visitor
{
private:
    int height;

    void up_height();
    void down_height();

    void printNode(const char *node);
    void printLexeme(const char *node, const char *lexeme);

public:
    Print_AST();

    void visit(TokenNode *node) override;
    void visit(Program_Node *node) override;
    void visit(VarList_Node *node) override;
    void visit(NameDecl_Node *node) override;
    void visit(FunctionList_Node *node) override;
    void visit(TypeList_Node *node) override;
    void visit(Type_Node *node) override;
    void visit(Pointer_Node *node) override;
    void visit(StmtList_Node *node) override;
    void visit(Stmt_Node *node) override;
    void visit(If_Node *node) override;
    void visit(While_Node *node) override;
    void visit(Switch_Node *node) override;
    void visit(Break_Node *node) override;
    void visit(PrintLn_Node *node) override;
    void visit(Read_Node *node) override;
    void visit(Return_Node *node) override;
    void visit(CaseBlock_Node *node) override;
    void visit(Throw_Node *node) override;
    void visit(ExpList_Node *node) override;
    void visit(Try_Node *node) override;
    void visit(Exp_Node *node) override;
    void visit(Assign_Node *node) override;
    void visit(NameExp_Node *node) override;
    void visit(PointerValueExp_Node *node) override;
    void visit(AddressValue_Node *node) override;
    void visit(PointerValue_Node *node) override;
    void visit(Array_Node *node) override;
    void visit(Call_Node *node) override;
    void visit(RelationalOP_Node *node) override;
    void visit(AdditionOP_Node *node) override;
    void visit(MultiplicationOP_Node *node) override;
    void visit(BooleanOP_Node *node) override;
    void visit(BitwiseOP_Node *node) override;
    void visit(True_Node *node) override;
    void visit(False_Node *node) override;
    void visit(Not_Node *node) override;
    void visit(Sign_Node *node) override;
};

#endif // VISITOR_H