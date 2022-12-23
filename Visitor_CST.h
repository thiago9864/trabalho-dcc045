#ifndef VISITOR_CST_H
#define VISITOR_CST_H

#include <iostream>

class Program ;
class Type ;
class IdList ;
class Array ;
class TypeDecl ;
class VarFn ;
class VarDecl ;
class FunctionDecl ;
class FormalRest ;
class FormalList ;
class FunctionBody ;
class ExprList ;
class StmtList ;
class CaseBlock ;
class Stmt ;
class IfOpt ;
class ElseOpt ;
class ExpSemID ;
class ExpSemIDL ;
class Primary ;
class PrimaryL ;

class VisitorCST{
    public:
        virtual ~VisitorCST() = default;
        virtual void visit(Program *node) = 0;
        virtual void visit(Type *node) = 0;
        virtual void visit(IdList *node) = 0;
        virtual void visit(Array *node) = 0;
        virtual void visit(TypeDecl *node) = 0;
        virtual void visit(VarFn *node) = 0;
        virtual void visit(VarDecl *node) = 0;
        virtual void visit(FunctionDecl *node) = 0;
        virtual void visit(FormalRest *node) = 0;
        virtual void visit(FormalList *node) = 0;
        virtual void visit(FunctionBody *node) = 0;
        virtual void visit(ExprList *node) = 0;
        virtual void visit(StmtList *node) = 0;
        virtual void visit(CaseBlock *node) = 0;
        virtual void visit(Stmt *node) = 0;
        virtual void visit(IfOpt *node) = 0;
        virtual void visit(ElseOpt *node) = 0;
        virtual void visit(ExpSemID *node) = 0;
        virtual void visit(ExpSemIDL *node) = 0;
        virtual void visit(Primary *node) = 0;
        virtual void visit(PrimaryL *node) = 0;
};

class PrintCST : public VisitorCST {
private:
    unsigned int level;

    void printIR(const char *node_name);

    void printLexemeIR(const char *node_name, const char *aux);

    void up_level();

    void down_level();

public:
    PrintCST();
    ~PrintCST() override;
    void visit(Program *node) override;
    void visit(Type *node) override;
    void visit(IdList *node) override;
    void visit(Array *node) override;
    void visit(TypeDecl *node) override;
    void visit(VarFn *node) override;
    void visit(VarDecl *node) override;
    void visit(FunctionDecl *node) override;
    void visit(FormalRest *node) override;
    void visit(FormalList *node) override;
    void visit(FunctionBody *node) override;
    void visit(ExprList *node) override;
    void visit(StmtList *node) override;
    void visit(CaseBlock *node) override;
    void visit(Stmt *node) override;
    void visit(IfOpt *node) override;
    void visit(ElseOpt *node) override;
    void visit(ExpSemID *node) override;
    void visit(ExpSemIDL *node) override;
    void visit(Primary *node) override;
    void visit(PrimaryL *node) override;
};

#endif // VISITOR_CST_H