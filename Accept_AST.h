#ifndef ACCEPT_H
#define ACCEPT_H

#include "Visitor_AST.h"

class Root
{
private:
public:
    virtual ~Root() = default;

    virtual void accept(Visitor *v) = 0;
};

class TokenNode : public Exp
{
private:
    int token;
    int size;

public:
    TokenNode(int token, const char *lexeme);

    void setToken(int token);
    void setSize(int token);

    int getToken();
    int getSize();

    virtual void accept(Visitor *v) override { v->visit(this); };
};

class Program : public Root
{
private:
    FunctionList *functionlist;
    TypeList *typelist;
    VarList *varlist;

public:
    Program(FunctionList *functionlist, TypeList *typelist, VarList *varlist);
    ~Program() override;

    inline FunctionList *getFunctionList() { return functionlist; };
    inline TypeList *getTypeList() { return typelist; };
    inline VarList *getVarList() { return varlist; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class VarList : public Root //: public Program
{
private:
    NameDecl *namedecl;
    VarList *next;

public:
    VarList(NameDecl *namedecl, VarList *next);
    VarList();
    ~VarList();

    inline NameDecl *getNameDecl() { return namedecl; };
    inline VarList *Next() { return next; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class FunctionList : public Root //: public Program
{
private:
    Type *type;
    TokenNode *id;
    VarList *varlist;
    StmtList *stmtlist;
    FunctionList *next;

public:
    FunctionList(Type *type, TokenNode *id, VarList *varlist, StmtList *stmtlist, FunctionList *next);
    FunctionList();

    inline Type *getType() { return type; };
    inline TokenNode *Id() { return id; };
    inline VarList *getVarList() { return varlist; };
    inline StmtList *getStmtList() { return stmtlist; };
    inline FunctionList *Next() { return next; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class TypeList : public Root //: public Program
{
private:
    VarList *varlist;
    TokenNode *id;
    TypeList *next;

public:
    TypeList(VarList *varlist, TokenNode *id, TypeList *next);
    ~TypeList();

    inline VarList *getVarlist() { return varlist; };
    inline TokenNode *Id() { return id; };
    inline TypeList *Next() { return next; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class NameDecl : public VarList
{
private:
    Type *type;
    TokenNode *id;

public:
    NameDecl(Type *type, TokenNode *id);
    ~NameDecl();

    inline Type *getType() { return type; };
    inline TokenNode *Id() { return id; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class Type : public FunctionList
{
private:
    TokenNode *id;
    const char *lexeme;

public:
    explicit Type(TokenNode *id) { this->id = id; }

    Type(TokenNode *id, const char *lexeme) : id(id), lexeme(lexeme) {}
    ~Type() override { delete this->id; }

    inline void setId(TokenNode *id) { this->id = id; }
    inline void setLexeme(const char *lexeme) { this->lexeme = lexeme; }

    inline TokenNode *Id() { return id; }
    inline const char *getLexeme() const { return lexeme; }

    inline int getType() { return id->getToken(); }
    inline const char *getTypeLexeme() { return id->getTypeLexeme(); }

    inline void accept(Visitor *v) override { v->visit(this); };
};

class StmtList : public FunctionList
{
private:
    Stmt *stmt;
    StmtList *next;

public:
    StmtList(Stmt *stmt, StmtList *next);
    ~StmtList();

    inline Stmt *getStmt() { return stmt; };
    inline StmtList *Next() { return next; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class Pointer : public Root
{
public:
    Pointer();
    ~Pointer();

    inline void accept(Visitor *v) override { v->visit(this); }
};

class Stmt : public Root //: public StmtList
{
private:
    Root *stmt;

public:
    inline Root *getStmt() { return stmt; }

    inline void accept(Visitor *v) override { v->visit(this); };
};

class If : public Root //: public Stmt
{
private:
    Exp *exp;
    Stmt *stmt1;
    Stmt *stmt2;

public:
    If(Exp *exp, Stmt *stmt1, Stmt *stmt2);
    ~If();

    inline Exp *getExp() { return exp; };
    inline Stmt *Stmt1() { return stmt1; };
    inline Stmt *Stmt2() { return stmt2; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class While : public Root //: public Stmt
{
    Exp *exp;
    Stmt *stmt;

public:
    While(Exp *exp, Stmt *stmt);
    ~While();

    inline Exp *getExp() { return exp; };
    inline Stmt *getStmt() { return stmt; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class Switch : public Root //: public Stmt
{
private:
    Exp *exp;
    CaseBlock *caseblock;

public:
    Switch(Exp *exp, CaseBlock *caseblock);
    Switch();
    ~Switch();

    inline Exp *getExp() { return exp; };
    inline CaseBlock *getCaseBlock() { return caseblock; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class Break : public Stmt
{
public:
    Break();
    ~Break();

    inline void accept(Visitor *v) override { v->visit(this); };
};

class PrintLn : public Stmt
{
private:
    ExpList *explist;

public:
    PrintLn(ExpList *explist);
    ~PrintLn();

    inline ExpList *getExpList() { return explist; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class Read : public Root //: public Stmt
{
private:
    Exp *exp;

public:
    Read();
    ~Read();

    inline Exp *getExp() { return exp; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class Return : public Root //: public Stmt
{
private:
    Exp *exp;

public:
    Return(Exp *exp);
    ~Return();

    inline Exp *getExp() { return exp; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class Throw : public Stmt
{
public:
    Throw();
    ~Throw();

    inline void accept(Visitor *v) override { v->visit(this); };
};

class Call : public Exp
{
private:
    TokenNode *id;
    ExpList *explist;

public:
    Call(TokenNode *id, ExpList *explist);
    ~Call();

    inline TokenNode *Id() { return id; };
    inline ExpList *getExpList() { return explist; };

    inline void accept(Visitor *v) override { v->visit(this); };
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

    inline void accept(Visitor *v) override { v->visit(this); };
};

class Exp : public Stmt
{
private:
    int type;
    int arraySize;
    const char *lexeme;
    const char *typeLexeme;
    bool lValue;
    bool pointer;

public:
    Exp();

    inline void setType(int type) { this->type = type; }
    inline void setArraySize(int arraySize) { this->arraySize = arraySize; }
    inline void setTypeLexeme(const char *typeLexeme) { this->typeLexeme = typeLexeme; }
    inline void setLexeme(const char *lexeme) { this->lexeme = lexeme; }
    inline void setLValue(bool lValue) { this->lValue = lValue; }
    inline void setPointer(bool pointer) { this->pointer = pointer; }

    inline int getType() const { return type; }
    inline int getArraySize() const { return arraySize; }
    inline const char *getTypeLexeme() const { return typeLexeme; }
    inline const char *getLexeme() const { return lexeme; }

    inline bool isLValue() const { return lValue; }
    inline bool isPointer() const { return pointer; }

    void accept(Visitor *v) override = 0;
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
    inline StmtList *getStmtList() { return stmtlist; };
    inline CaseBlock *Next() { return next; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class ExpList : public Root //: public PrintLn
{
private:
    Exp *exp;
    ExpList *next;

public:
    ExpList(Exp *exp, ExpList *next);
    ~ExpList();

    inline Exp *getExp() { return exp; };
    inline ExpList *Next() { return next; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class NameExp : public Exp
{
private:
    Exp *exp;
    TokenNode *id;

public:
    NameExp(Exp *exp, TokenNode *id);

    inline Exp *getExp() { return exp; };
    inline TokenNode *Id() { return id; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class PointerValueExp : public Exp
{
private:
    Exp *exp;
    TokenNode *id;

public:
    PointerValueExp(Exp *exp, TokenNode *id);
    ~PointerValueExp();

    inline Exp *getExp() { return exp; };
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

    inline Exp *getExp() { return exp; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class PointerValue : public Exp
{
private:
    Exp *exp;

public:
    PointerValue(Exp *exp);
    ~PointerValue();

    inline Exp *getExp() { return exp; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class Array : public Exp
{
private:
    Exp *exp;
    ExpList *explist;

public:
    Array(Exp *exp, ExpList *explist);
    ~Array();

    inline Exp *getExp() { return exp; };
    inline ExpList *getExpList() { return explist; };

    inline void accept(Visitor *v) override { v->visit(this); };
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

    inline void accept(Visitor *v) override { v->visit(this); };
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

    inline void accept(Visitor *v) override { v->visit(this); };
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

    inline void accept(Visitor *v) override { v->visit(this); };
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

    inline void accept(Visitor *v) override { v->visit(this); };
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

    inline void accept(Visitor *v) override { v->visit(this); };
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

    inline void accept(Visitor *v) override { v->visit(this); };
};

class Not : public Exp
{
private:
    Exp *exp;

public:
    Not(Exp *exp);
    ~Not();

    inline Exp *getExp() { return exp; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class Sign : public Exp
{
private:
    Exp *exp;

public:
    Sign(Exp *exp);
    ~Sign();

    inline Exp *getExp() { return exp; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class True : public Exp
{
public:
    True();
    ~True();

    inline void accept(Visitor *v) override { v->visit(this); };
};

class False : public Exp
{
public:
    False();
    ~False();

    inline void accept(Visitor *v) override { v->visit(this); };
};

#endif // ACCEPT_H
