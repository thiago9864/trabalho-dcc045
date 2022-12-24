#ifndef VISITOR_AST_H
#define VISITOR_AST_H

#include "LexicalAnalyzer.h"
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

class Root_Node
{
private:
public:
    virtual ~Root_Node() = default;

    virtual void accept(Visitor *v) = 0;
};

class TokenNode : public Exp_Node
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

class Program_Node : public Root_Node
{
private:
    FunctionList_Node *functionlist;
    TypeList_Node *typelist;
    VarList_Node *varlist;

public:
    Program_Node(FunctionList_Node *functionlist, TypeList_Node *typelist, VarList_Node *varlist);
    ~Program_Node() override;

    inline FunctionList_Node *getFunctionList() { return functionlist; };
    inline TypeList_Node *getTypeList() { return typelist; };
    inline VarList_Node *getVarList() { return varlist; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class VarList_Node : public Root_Node //: public Program_Node
{
private:
    NameDecl_Node *namedecl;
    VarList_Node *next;

public:
    VarList_Node(NameDecl_Node *namedecl, VarList_Node *next);
    VarList_Node();
    ~VarList_Node();

    inline NameDecl_Node *getNameDecl() { return namedecl; };
    inline VarList_Node *Next() { return next; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class FunctionList_Node : public Root_Node //: public Program_Node
{
private:
    Type_Node *type;
    TokenNode *id;
    VarList_Node *varlist;
    StmtList_Node *stmtlist;
    FunctionList_Node *next;

public:
    FunctionList_Node(Type_Node *type, TokenNode *id, VarList_Node *varlist, StmtList_Node *stmtlist, FunctionList_Node *next);
    FunctionList_Node();

    inline Type_Node *getType() { return type; };
    inline TokenNode *Id() { return id; };
    inline VarList_Node *getVarList() { return varlist; };
    inline StmtList_Node *getStmtList() { return stmtlist; };
    inline FunctionList_Node *Next() { return next; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class TypeList_Node : public Root_Node //: public Program_Node
{
private:
    VarList_Node *varlist;
    TokenNode *id;
    TypeList_Node *next;

public:
    TypeList_Node(VarList_Node *varlist, TokenNode *id, TypeList_Node *next);
    ~TypeList_Node();

    inline VarList_Node *getVarlist() { return varlist; };
    inline TokenNode *Id() { return id; };
    inline TypeList_Node *Next() { return next; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class NameDecl_Node : public VarList_Node
{
private:
    Type_Node *type;
    TokenNode *id;

public:
    NameDecl_Node(Type_Node *type, TokenNode *id);
    ~NameDecl_Node();

    inline Type_Node *getType() { return type; };
    inline TokenNode *Id() { return id; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class Type_Node : public FunctionList_Node
{
private:
    TokenNode *id;
    const char *lexeme;

public:
    explicit Type_Node(TokenNode *id) { this->id = id; }

    Type_Node(TokenNode *id, const char *lexeme) : id(id), lexeme(lexeme) {}
    ~Type_Node() override { delete this->id; }

    inline void setId(TokenNode *id) { this->id = id; }
    inline void setLexeme(const char *lexeme) { this->lexeme = lexeme; }

    inline TokenNode *Id() { return id; }
    inline const char *getLexeme() const { return lexeme; }

    inline int getType() { return id->getToken(); }
    inline const char *getTypeLexeme() { return id->getTypeLexeme(); }

    inline void accept(Visitor *v) override { v->visit(this); };
};

class StmtList_Node : public FunctionList_Node
{
private:
    Stmt_Node *stmt;
    StmtList_Node *next;

public:
    StmtList_Node(Stmt_Node *stmt, StmtList_Node *next);
    ~StmtList_Node();

    inline Stmt_Node *getStmt() { return stmt; };
    inline StmtList_Node *Next() { return next; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class Pointer_Node : public Root_Node
{
public:
    Pointer_Node();
    ~Pointer_Node();

    inline void accept(Visitor *v) override { v->visit(this); }
};

class Stmt_Node : public Root_Node //: public StmtList_Node
{
private:
    Root_Node *stmt;

public:
    inline Root_Node *getStmt() { return stmt; }

    inline void accept(Visitor *v) override { v->visit(this); };
};

class If_Node : public Root_Node //: public Stmt_Node
{
private:
    Exp_Node *exp;
    Stmt_Node *stmt1;
    Stmt_Node *stmt2;

public:
    If_Node(Exp_Node *exp, Stmt_Node *stmt1, Stmt_Node *stmt2);
    ~If_Node();

    inline Exp_Node *getExp() { return exp; };
    inline Stmt_Node *Stmt1() { return stmt1; };
    inline Stmt_Node *Stmt2() { return stmt2; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class While_Node : public Root_Node //: public Stmt_Node
{
    Exp_Node *exp;
    Stmt_Node *stmt;

public:
    While_Node(Exp_Node *exp, Stmt_Node *stmt);
    ~While_Node();

    inline Exp_Node *getExp() { return exp; };
    inline Stmt_Node *getStmt() { return stmt; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class Switch_Node : public Root_Node //: public Stmt_Node
{
private:
    Exp_Node *exp;
    CaseBlock_Node *caseblock;

public:
    Switch_Node(Exp_Node *exp, CaseBlock_Node *caseblock);
    Switch_Node();
    ~Switch_Node();

    inline Exp_Node *getExp() { return exp; };
    inline CaseBlock_Node *getCaseBlock() { return caseblock; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class Break_Node : public Stmt_Node
{
public:
    Break_Node();
    ~Break_Node();

    inline void accept(Visitor *v) override { v->visit(this); };
};

class PrintLn_Node : public Stmt_Node
{
private:
    ExpList_Node *explist;

public:
    PrintLn_Node(ExpList_Node *explist);
    ~PrintLn_Node();

    inline ExpList_Node *getExpList() { return explist; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class Read_Node : public Root_Node //: public Stmt_Node
{
private:
    Exp_Node *exp;

public:
    Read_Node();
    ~Read_Node();

    inline Exp_Node *getExp() { return exp; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class Return_Node : public Root_Node //: public Stmt_Node
{
private:
    Exp_Node *exp;

public:
    Return_Node(Exp_Node *exp);
    ~Return_Node();

    inline Exp_Node *getExp() { return exp; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class Throw_Node : public Stmt_Node
{
public:
    Throw_Node();
    ~Throw_Node();

    inline void accept(Visitor *v) override { v->visit(this); };
};

class Call_Node : public Exp_Node
{
private:
    TokenNode *id;
    ExpList_Node *explist;

public:
    Call_Node(TokenNode *id, ExpList_Node *explist);
    ~Call_Node();

    inline TokenNode *Id() { return id; };
    inline ExpList_Node *getExpList() { return explist; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class Try_Node : public Stmt_Node
{
private:
    Stmt_Node *stmt1;
    Stmt_Node *stmt2;

public:
    Try_Node(Stmt_Node *stmt1, Stmt_Node *stmt2);
    ~Try_Node();

    inline Stmt_Node *Stmt1() { return stmt1; };
    inline Stmt_Node *Stmt2() { return stmt2; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class Exp_Node : public Stmt_Node
{
private:
    int type;
    int arraySize;
    const char *lexeme;
    const char *typeLexeme;
    bool lValue;
    bool pointer;

public:
    Exp_Node();

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

class CaseBlock_Node : public Switch_Node
{
private:
    TokenNode *num;
    StmtList_Node *stmtlist;
    CaseBlock_Node *next;

public:
    CaseBlock_Node(TokenNode *num, StmtList_Node *stmtlist, CaseBlock_Node *next);

    inline TokenNode *Num() { return num; };
    inline StmtList_Node *getStmtList() { return stmtlist; };
    inline CaseBlock_Node *Next() { return next; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class ExpList_Node : public Root_Node //: public PrintLn
{
private:
    Exp_Node *exp;
    ExpList_Node *next;

public:
    ExpList_Node(Exp_Node *exp, ExpList_Node *next);
    ~ExpList_Node();

    inline Exp_Node *getExp() { return exp; };
    inline ExpList_Node *Next() { return next; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class NameExp_Node : public Exp_Node
{
private:
    Exp_Node *exp;
    TokenNode *id;

public:
    NameExp_Node(Exp_Node *exp, TokenNode *id);

    inline Exp_Node *getExp() { return exp; };
    inline TokenNode *Id() { return id; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class PointerValueExp_Node : public Exp_Node
{
private:
    Exp_Node *exp;
    TokenNode *id;

public:
    PointerValueExp_Node(Exp_Node *exp, TokenNode *id);
    ~PointerValueExp_Node();

    inline Exp_Node *getExp() { return exp; };
    inline TokenNode *Id() { return id; };

    virtual void accept(Visitor *v);
};

class AddressValue_Node : public Exp_Node
{
private:
    Exp_Node *exp;

public:
    AddressValue_Node(Exp_Node *exp);
    ~AddressValue_Node();

    inline Exp_Node *getExp() { return exp; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class PointerValue_Node : public Exp_Node
{
private:
    Exp_Node *exp;

public:
    PointerValue_Node(Exp_Node *exp);
    ~PointerValue_Node();

    inline Exp_Node *getExp() { return exp; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class Array_Node : public Exp_Node
{
private:
    Exp_Node *exp;
    ExpList_Node *explist;

public:
    Array_Node(Exp_Node *exp, ExpList_Node *explist);
    ~Array_Node();

    inline Exp_Node *getExp() { return exp; };
    inline ExpList_Node *getExpList() { return explist; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class Assign_Node : Exp_Node
{
private:
    Exp_Node *exp1;
    Exp_Node *exp2;

public:
    Assign_Node(Exp_Node *exp1, Exp_Node *exp2);
    ~Assign_Node();

    inline Exp_Node *Exp1() { return exp1; };
    inline Exp_Node *Exp2() { return exp2; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class RelationalOP_Node : public Exp_Node
{
private:
    TokenNode *op;
    Exp_Node *exp1;
    Exp_Node *exp2;

public:
    RelationalOP_Node(Exp_Node *exp1, Exp_Node *exp2);
    ~RelationalOP_Node();

    inline TokenNode *Op() { return op; };
    inline Exp_Node *Exp1() { return exp1; };
    inline Exp_Node *Exp2() { return exp2; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class AdditionOP_Node : public Exp_Node
{
private:
    TokenNode *op;
    Exp_Node *exp1;
    Exp_Node *exp2;

public:
    AdditionOP_Node(Exp_Node *exp1, Exp_Node *exp2);
    ~AdditionOP_Node();

    inline TokenNode *Op() { return op; };
    inline Exp_Node *Exp1() { return exp1; };
    inline Exp_Node *Exp2() { return exp2; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class MultiplicationOP_Node : public Exp_Node
{
private:
    TokenNode *op;
    Exp_Node *exp1;
    Exp_Node *exp2;

public:
    MultiplicationOP_Node(Exp_Node *exp1, Exp_Node *exp2);
    ~MultiplicationOP_Node();

    inline TokenNode *Op() { return op; };
    inline Exp_Node *Exp1() { return exp1; };
    inline Exp_Node *Exp2() { return exp2; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class BooleanOP_Node : public Exp_Node
{
private:
    TokenNode *op;
    Exp_Node *exp1;
    Exp_Node *exp2;

public:
    BooleanOP_Node(Exp_Node *exp1, Exp_Node *exp2);
    ~BooleanOP_Node();

    inline TokenNode *Op() { return op; };
    inline Exp_Node *Exp1() { return exp1; };
    inline Exp_Node *Exp2() { return exp2; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class BitwiseOP_Node : public Exp_Node
{
private:
    TokenNode *op;
    Exp_Node *exp1;
    Exp_Node *exp2;

public:
    BitwiseOP_Node(Exp_Node *exp1, Exp_Node *exp2);
    ~BitwiseOP_Node();

    inline TokenNode *Op() { return op; };
    inline Exp_Node *Exp1() { return exp1; };
    inline Exp_Node *Exp2() { return exp2; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class Not_Node : public Exp_Node
{
private:
    Exp_Node *exp;

public:
    Not_Node(Exp_Node *exp);
    ~Not_Node();

    inline Exp_Node *getExp() { return exp; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class Sign_Node : public Exp_Node
{
private:
    Exp_Node *exp;

public:
    Sign_Node(Exp_Node *exp);
    ~Sign_Node();

    inline Exp_Node *getExp() { return exp; };

    inline void accept(Visitor *v) override { v->visit(this); };
};

class True_Node : public Exp_Node
{
public:
    True_Node();
    ~True_Node();

    inline void accept(Visitor *v) override { v->visit(this); };
};

class False_Node : public Exp_Node
{
public:
    False_Node();
    ~False_Node();

    inline void accept(Visitor *v) override { v->visit(this); };
};

#endif // VISITOR_H