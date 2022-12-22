#ifndef ACCEPT_H
#define ACCEPT_H

#include "Visitor_AST.h"

class Root
{
private:
    int line;

public:
    virtual ~Root() = default;

    virtual void setLine(int line);

    int getLine();

    virtual void accept(Visitor *v) = 0;
};

class TokenNode
{
private:
    int token;

public:
    TokenNode(int token, const char *lexeme);

    virtual ~TokenNode() = default;

    void setToken(int token);

    int getToken();

    virtual void accept(Visitor *v);
};

class Program
{
private:
    FunctionList *functions;
    TypeList *typelist;
    VarList *varlist;

public:
    Program(FunctionList *functions, TypeList *typelist, VarList *varlist);
    ~Program();

    inline FunctionList *FunctionList() { return functions; }
    inline TypeList *TypeList() { return typelist; }
    inline VarList *VarList() { return varlist; }

    virtual void accept(Visitor *v) = 0;
};

class VarList : public Program
{
private:
    NameDecl *namedecl;
    VarList *next;

public:
    VarList(NameDecl *namedecl, VarList *next);
    ~VarList();

    inline NameDecl *NameDecl() { return namedecl; };
    inline VarList *Next() { return next; }

    virtual void accept(Visitor *v) = 0;
};

class FunctionList : public Program
{
private:
    Type *type;
    TokenNode *id;
    VarList *varlist;
    StmtList *stmtlist;
    FunctionList *next;

public:
    FunctionList(Type *type,
                 TokenNode *id,
                 VarList *varlist,
                 StmtList *stmtlist,
                 FunctionList *next);

    inline Type *Type() { return type; };
    inline TokenNode *Id() { return id; }
    inline VarList *VarList() { return varlist; }
    inline StmtList *StmtList() { return stmtlist; }
    inline FunctionList *Next() { return next; }

    virtual void accept(Visitor *v) = 0;
};

class TypeList : public Program
{
private:
    VarList *varlist;
    TokenNode *id;
    TypeList *type;
    TypeList *next;

public:
    TypeList(VarList *varlist,
             TokenNode *id,
             TypeList *next);
    ~TypeList();

    inline VarList *Varlist(){return varlist};
    inline TokenNode *Id() { return id; };
    inline TypeList *Next() { return next; };

    virtual void accept(Visitor *v) = 0;
};

class NameDecl : public VarList
{
private:
    Type *type;
    TokenNode *id;

public:
    NameDecl(Type *type,
             TokenNode *id);
    ~NameDecl();

    inline Type *Type(){return *type};
    inline TokenNode *Id(){return *id} ?

                                       virtual void accept(Visitor *v) = 0;
};

class Type : public FunctionList
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class StmtList : public FunctionList
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class Pointer : public Type
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class Stmt : public StmtList
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class If : public Stmt
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class While : public Stmt
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class Switch : public Stmt
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class Break : public Stmt
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class PrintLn : public Stmt
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class Read : public Stmt
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class Return : public Stmt
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class Throw : public Stmt
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class Call : public Stmt
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class Try : public Stmt
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class Exp : public Stmt
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class CaseBlock : public Switch
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class ExpList : public PrintLn
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class NameExp : public Exp
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class PointerValueExp : public Exp
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class AddressValue : public Exp
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class PointerValue : public Exp
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class Array : public Exp
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class Assign : Exp
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class RelationalOP : public Exp
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class AdditionOP : public Exp
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class MultiplicationOP : public Exp
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class BooleanOP : public Exp
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class BitwiseOP : public Exp
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class Not : public Exp
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class Sign : public Exp
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class True : public Exp
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

class False : public Exp
{
private:
public:
    virtual void accept(Visitor *v) = 0;
};

#endif // ACCEPT_H
