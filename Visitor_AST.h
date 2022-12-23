#ifndef VISITOR_AST_H
#define VISITOR_AST_H

#include <iostream>

class Root;
class TokenNode;
class Program;
class VarList;
class NameDecl;
class FunctionList;
class TypeList;
class Type;
class Pointer;
class StmtList;
class Stmt;
class If;
class While;
class Switch;
class Break;
class PrintLn;
class Read;
class Return;
class CaseBlock;
class Throw;
class ExpList;
class Try;
class Exp;
class Assign;
class NameExp;
class PointerValueExp;
class AddressValue;
class PointerValue;
class Array;
class Call;
class RelationalOP;
class AdditionOP;
class MultiplicationOP;
class BooleanOP;
class BitwiseOP;
class True;
class False;
class Not;
class Sign;

class Visitor
{

public:
    virtual ~Visitor() = default;
    virtual void visit(TokenNode *node) = 0;
    virtual void visit(Program *node) = 0;
    virtual void visit(VarList *node) = 0;
    virtual void visit(NameDecl *node) = 0;
    virtual void visit(FunctionList *node) = 0;
    virtual void visit(TypeList *node) = 0;
    virtual void visit(Type *node) = 0;
    virtual void visit(Pointer *node) = 0;
    virtual void visit(StmtList *node) = 0;
    virtual void visit(Stmt *node) = 0;
    virtual void visit(If *node) = 0;
    virtual void visit(While *node) = 0;
    virtual void visit(Switch *node) = 0;
    virtual void visit(Break *node) = 0;
    virtual void visit(PrintLn *node) = 0;
    virtual void visit(Read *node) = 0;
    virtual void visit(Return *node) = 0;
    virtual void visit(CaseBlock *node) = 0;
    virtual void visit(Throw *node) = 0;
    virtual void visit(ExpList *node) = 0;
    virtual void visit(Try *node) = 0;
    virtual void visit(Exp *node) = 0;
    virtual void visit(Assign *node) = 0;
    virtual void visit(NameExp *node) = 0;
    virtual void visit(PointerValueExp *node) = 0;
    virtual void visit(AddressValue *node) = 0;
    virtual void visit(PointerValue *node) = 0;
    virtual void visit(Array *node) = 0;
    virtual void visit(Call *node) = 0;
    virtual void visit(RelationalOP *node) = 0;
    virtual void visit(AdditionOP *node) = 0;
    virtual void visit(MultiplicationOP *node) = 0;
    virtual void visit(BooleanOP *node) = 0;
    virtual void visit(BitwiseOP *node) = 0;
    virtual void visit(True *node) = 0;
    virtual void visit(False *node) = 0;
    virtual void visit(Not *node) = 0;
    virtual void visit(Sign *node) = 0;
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
    void visit(Program *node) override;
    void visit(VarList *node) override;
    void visit(NameDecl *node) override;
    void visit(FunctionList *node) override;
    void visit(TypeList *node) override;
    void visit(Type *node) override;
    void visit(Pointer *node) override;
    void visit(StmtList *node) override;
    void visit(Stmt *node) override;
    void visit(If *node) override;
    void visit(While *node) override;
    void visit(Switch *node) override;
    void visit(Break *node) override;
    void visit(PrintLn *node) override;
    void visit(Read *node) override;
    void visit(Return *node) override;
    void visit(CaseBlock *node) override;
    void visit(Throw *node) override;
    void visit(ExpList *node) override;
    void visit(Try *node) override;
    void visit(Exp *node) override;
    void visit(Assign *node) override;
    void visit(NameExp *node) override;
    void visit(PointerValueExp *node) override;
    void visit(AddressValue *node) override;
    void visit(PointerValue *node) override;
    void visit(Array *node) override;
    void visit(Call *node) override;
    void visit(RelationalOP *node) override;
    void visit(AdditionOP *node) override;
    void visit(MultiplicationOP *node) override;
    void visit(BooleanOP *node) override;
    void visit(BitwiseOP *node) override;
    void visit(True *node) override;
    void visit(False *node) override;
    void visit(Not *node) override;
    void visit(Sign *node) override;
};

#endif // VISITOR_H