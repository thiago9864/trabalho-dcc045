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
    int size;

public:
    TokenNode(int token, const char *lexeme);

    virtual ~TokenNode() = default;

    void setToken(int token);
    void setSize(int token);

    int getToken();
    int getSize();

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

    inline FunctionList *FunctionList() { return functions; };
    inline TypeList *TypeList() { return typelist; };
    inline VarList *VarList() { return varlist; };

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
    inline VarList *Next() { return next; };

    virtual void accept(Visitor *v) = 0;
};

class FunctionList //: public Program
{
private:
    Type *type;
    TokenNode *id;
    VarList *varlist;
    StmtList *stmtlist;
    FunctionList *next;

public:
    FunctionList(Type *type, TokenNode *id, VarList *varlist, StmtList *stmtlist, FunctionList *next);

    inline Type *Type() { return type; };
    inline TokenNode *Id() { return id; };
    inline VarList *VarList() { return varlist; };
    inline StmtList *StmtList() { return stmtlist; };
    inline FunctionList *Next() { return next; };

    virtual void accept(Visitor *v) = 0;
};

class TypeList //: public Program
{
private:
    VarList *varlist;
    TokenNode *id;
    TypeList *next;

public:
    TypeList(VarList *varlist, TokenNode *id, TypeList *next);
    ~TypeList();

    inline VarList *Varlist() { return varlist; };
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
    NameDecl(Type *type, TokenNode *id);
    ~NameDecl();

    inline Type *Type() { return type; };
    inline TokenNode *Id() { return id; };

    virtual void accept(Visitor *v) = 0;
};

class Type : public FunctionList
{
private:
    TokenNode *id;
    Pointer *pointer;

public:
    Type(TokenNode *id, Pointer *pointer);
    ~Type();

    inline TokenNode *Id() { return id; };
    inline Pointer *Pointer() { return pointer; };

    virtual void accept(Visitor *v) = 0;
};

class StmtList : public FunctionList
{
private:
    Stmt *stmt;
    StmtList *next;

public:
    StmtList(Stmt *stmt, StmtList *next);
    ~StmtList();

    inline Stmt *Stmt() { return stmt; };
    inline StmtList *Next() { return next; };

    virtual void accept(Visitor *v) = 0;
};

class Pointer : public Type
{
private:
    Type *type;

public:
    Pointer(Type *type);
    ~Pointer();

    inline Type *Type() { return type; };

    virtual void accept(Visitor *v) = 0;
};

class Stmt : public StmtList
{
private:
    If *if_;
    While *while_;
    Switch *switch_;
    Break *break_;
    PrintLn *println;
    Read *read;
    Return *return_;
    Throw *throw_;
    StmtList *stmtlist;
    Call *call;
    Try *try_;
    Exp *exp;

public:
    Stmt(If *if_, While *while_, Switch *switch_, Break *break_, PrintLn *println, Read *read, Return *return_, Throw *throw_, StmtList *stmtlist, Call *call, Try *try_, Exp *exp);
    ~Stmt();

    inline If *If() { return if_; };
    inline While *While() { return while_; };
    inline Switch *Switch() { return switch_; };
    inline Break *Break() { return break_; };
    inline PrintLn *PrintLn() { return println; };
    inline Read *Read() { return read; };
    inline Return *Return() { return return_; };
    inline Throw *Throw() { return throw_; };
    inline StmtList *StmtList() { return stmtlist; };
    inline Call *Call() { return call; };
    inline Try *Try() { return try_; };
    inline Exp *Exp() { return exp; };

    virtual void accept(Visitor *v) = 0;
};

class If //: public Stmt
{
private:
    Exp *exp;
    Stmt *stmt1;
    Stmt *stmt2;

public:
    If(Exp *exp, Stmt *stmt1, Stmt *stmt2);
    ~If();

    inline Exp *Exp() { return exp; };
    inline Stmt *Stmt1() { return stmt1; };
    inline Stmt *Stmt2() { return stmt2; };

    virtual void accept(Visitor *v) = 0;
};

class While //: public Stmt
{
    Exp *exp;
    Stmt *stmt;

public:
    While(Exp *exp, Stmt *stmt);
    ~While();

    inline Exp *Exp() { return exp; };
    inline Stmt *Stmt() { return stmt; };

    virtual void accept(Visitor *v) = 0;
};

class Switch //: public Stmt
{
private:
    Exp *exp;
    CaseBlock *caseblock;

public:
    Switch(Exp *exp, CaseBlock *caseblock);
    ~Switch();

    inline Exp *Exp() { return exp; };
    inline CaseBlock *CaseBlock() { return caseblock; };

    virtual void accept(Visitor *v) = 0;
};

class Break : public Stmt
{
public:
    Break();
    ~Break();

    virtual void accept(Visitor *v) = 0;
};

class PrintLn : public Stmt
{
private:
    ExpList *explist;

public:
    PrintLn(ExpList *explist);
    ~PrintLn();

    inline ExpList *ExpList() { return explist; };

    virtual void accept(Visitor *v) = 0;
};

class Read //: public Stmt
{
private:
    Exp *exp;

public:
    Read(Exp *exp);
    ~Read();

    inline Exp *Exp() { return exp; };

    virtual void accept(Visitor *v) = 0;
};

class Return //: public Stmt
{
private:
    Exp *exp;

public:
    Return(Exp *exp);
    ~Return();

    inline Exp *Exp() { return exp; };

    virtual void accept(Visitor *v) = 0;
};

class Throw : public Stmt
{
public:
    Throw();
    ~Throw();

    virtual void accept(Visitor *v) = 0;
};

class Call : public Stmt
{
private:
    TokenNode *id;
    ExpList *explist;

public:
    Call(TokenNode *id, ExpList *explist);
    ~Call();

    inline TokenNode *Id() { return id; };
    inline ExpList *ExpList() { return explist; };

    virtual void accept(Visitor *v) = 0;
};

class Try : public Stmt
{
private:
    Stmt *stmt1;
    Stmt *stmt2;

public:
    Try(Stmt *stmt1, Stmt *stmt2);
    ~Try();

    inline Stmt *Stmt1() { return stmt1; };
    inline Stmt *Stmt2() { return stmt2; };

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
    TokenNode *num;
    StmtList *stmtlist;
    CaseBlock *next;

public:
    CaseBlock(TokenNode *num, StmtList *stmtlist, CaseBlock *next);

    inline TokenNode *Num() { return num; };
    inline StmtList *StmtList() { return stmtlist; };
    inline CaseBlock *Next() { return next; };

    virtual void accept(Visitor *v) = 0;
};

class ExpList //: public PrintLn
{
private:
    Exp *exp;
    ExpList *next;

public:
    ExpList(Exp *exp, ExpList *next);
    ~ExpList();

    inline Exp *Exp() { return exp; };
    inline ExpList *Next() { return next; };

    virtual void accept(Visitor *v) = 0;
};

class NameExp : public Exp
{
private:
    Exp *exp;
    TokenNode *id;

public:
    NameExp(Exp *exp, TokenNode *id);

    inline Exp *Exp() { return exp; };
    inline TokenNode *Id() { return id; };

    virtual void accept(Visitor *v) = 0;
};

class PointerValueExp : public Exp
{
private:
    Exp *exp;
    TokenNode *id;

public:
    PointerValueExp(Exp *exp, TokenNode *id);
    ~PointerValueExp();

    inline Exp *Exp() { return exp; };
    inline TokenNode *Id() { return id; };

    virtual void accept(Visitor *v);
};

class AddressValue : public Exp
{
private:
    Exp *exp;

public:
    AddressValue(Exp *exp);
    ~AddressValue();

    inline Exp *Exp() { return exp; };

    virtual void accept(Visitor *v) = 0;
};

class PointerValue : public Exp
{
private:
    Exp *exp;

public:
    PointerValue(Exp *exp);
    ~PointerValue();

    inline Exp *Exp() { return exp; };

    virtual void accept(Visitor *v) = 0;
};

class Array : public Exp
{
private:
    Exp *exp;
    ExpList *explist;

public:
    Array(Exp *exp, ExpList *explist);
    ~Array();

    inline Exp *Exp() { return exp; };
    inline ExpList *ExpList() { return explist; };

    virtual void accept(Visitor *v) = 0;
};

class Assign : Exp
{
private:
    Exp *exp1;
    Exp *exp2;

public:
    Assign(Exp *exp1, Exp *exp2);
    ~Assign();

    inline Exp *Exp1() { return exp1; };
    inline Exp *Exp2() { return exp2; };

    virtual void accept(Visitor *v) = 0;
};

class RelationalOP : public Exp
{
private:
    TokenNode *op;
    Exp *exp1;
    Exp *exp2;

public:
    RelationalOP(Exp *exp1, Exp *exp2);
    ~RelationalOP();

    inline TokenNode *Op() { return op; };
    inline Exp *Exp1() { return exp1; };
    inline Exp *Exp2() { return exp2; };

    virtual void accept(Visitor *v) = 0;
};

class AdditionOP : public Exp
{
private:
    TokenNode *op;
    Exp *exp1;
    Exp *exp2;

public:
    AdditionOP(Exp *exp1, Exp *exp2);
    ~AdditionOP();

    inline TokenNode *Op() { return op; };
    inline Exp *Exp1() { return exp1; };
    inline Exp *Exp2() { return exp2; };

    virtual void accept(Visitor *v) = 0;
};

class MultiplicationOP : public Exp
{
private:
    TokenNode *op;
    Exp *exp1;
    Exp *exp2;

public:
    MultiplicationOP(Exp *exp1, Exp *exp2);
    ~MultiplicationOP();

    inline TokenNode *Op() { return op; };
    inline Exp *Exp1() { return exp1; };
    inline Exp *Exp2() { return exp2; };

    virtual void accept(Visitor *v) = 0;
};

class BooleanOP : public Exp
{
private:
    TokenNode *op;
    Exp *exp1;
    Exp *exp2;

public:
    BooleanOP(Exp *exp1, Exp *exp2);
    ~BooleanOP();

    inline TokenNode *Op() { return op; };
    inline Exp *Exp1() { return exp1; };
    inline Exp *Exp2() { return exp2; };

    virtual void accept(Visitor *v) = 0;
};

class BitwiseOP : public Exp
{
private:
    TokenNode *op;
    Exp *exp1;
    Exp *exp2;

public:
    BitwiseOP(Exp *exp1, Exp *exp2);
    ~BitwiseOP();

    inline TokenNode *Op() { return op; };
    inline Exp *Exp1() { return exp1; };
    inline Exp *Exp2() { return exp2; };

    virtual void accept(Visitor *v) = 0;
};

class Not : public Exp
{
private:
    Exp *exp;

public:
    Not(Exp *exp);
    ~Not();

    inline Exp *Exp() { return exp; };

    virtual void accept(Visitor *v) = 0;
};

class Sign : public Exp
{
private:
    Exp *exp;

public:
    Sign(Exp *exp);
    ~Sign();

    inline Exp *Exp() { return exp; };

    virtual void accept(Visitor *v) = 0;
};

class True : public Exp
{
public:
    True();
    ~True();

    virtual void accept(Visitor *v) = 0;
};

class False : public Exp
{
public:
    False();
    ~False();

    virtual void accept(Visitor *v) = 0;
};

#endif // ACCEPT_H
