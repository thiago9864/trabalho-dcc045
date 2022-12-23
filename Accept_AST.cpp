#include "Accept_AST.h"

TokenNode::TokenNode(int token, const char *lexeme)
{
    this->token = token;
    this->size = 0;

    this->setType(-42);
    this->setArraySize(-42);
    this->setLexeme(lexeme);
    this->setTypeLexeme(NULL);
    this->setLValue(false);
    this->setPointer(false);
}

Program::Program(FunctionList *functionlist, TypeList *typelist, VarList *varlist)
{
    this->functionlist = functionlist;
    this->typelist = typelist;
    this->varlist = varlist;
}
Program::~Program()
{
    delete this->varlist;
    delete this->typelist;
    delete this->functionlist;
}

VarList::VarList(NameDecl *namedecl, VarList *next)
{
    this->namedecl = namedecl;
    this->next = next;
}
VarList::~VarList()
{
    delete this->namedecl;
    delete this->next;
}

FunctionList::FunctionList(Type *type, TokenNode *id, VarList *varlist, StmtList *stmtlist, FunctionList *next)
{
    this->type = type;
    this->id = id;
    this->varlist = varlist;
    this->stmtlist = stmtlist;
    this->next = next;
}
FunctionList::~FunctionList()
{
    delete this->type;
    delete this->id;
    delete this->varlist;
    delete this->stmtlist;
    delete this->next;
}

TypeList::TypeList(VarList *varlist, TokenNode *id, TypeList *next)
{
    this->varlist = varlist;
    this->id = id;
    this->next = next;
}
TypeList::~TypeList()
{
    delete this->varlist;
    delete this->id;
    delete this->next;
}

NameDecl::NameDecl(Type *type, TokenNode *id)
{
    this->type = type;
    this->id = id;
}
NameDecl::~NameDecl()
{
    delete this->type;
    delete this->id;
}

StmtList::StmtList(Stmt *stmt1, StmtList *next1)
{
    this->stmt = stmt;
    this->next = next;
}
StmtList::~StmtList()
{
    delete this->next;
    delete this->stmt;
}

If::If(Exp *exp, Stmt *stmt1, Stmt *stmt2)
{
    this->exp = exp;
    this->stmt1 = stmt1;
    this->stmt2 = stmt2;
}
If::~If()
{
    delete this->exp;
    delete this->stmt1;
    delete this->stmt2;
}

While::While(Exp *exp, Stmt *stmt)
{
    this->exp = exp;
    this->stmt = stmt;
}
While::~While()
{
    delete this->exp;
    delete this->stmt;
}

Switch::Switch(Exp *exp, CaseBlock *caseblock)
{
    this->exp = exp;
    this->caseblock = caseblock;
}
Switch::~Switch()
{
    delete this->exp;
    delete this->caseblock;
}

CaseBlock::CaseBlock(TokenNode *num, StmtList *stmtlist, CaseBlock *next)
{
    this->num = num;
    this->stmtlist = stmtlist;
    this->next = next;
}
CaseBlock::~CaseBlock()
{
    delete this->num;
    delete this->stmtlist;
    delete this->next;
}

ExpList::ExpList(Exp *exp, ExpList *next)
{
    this->exp = exp;
    this->next = next;
}
ExpList::~ExpList()
{
    delete this->exp;
    delete this->next;
}

Try::Try(Stmt *stmt1, Stmt *stmt2)
{
    this->stmt1 = stmt1;
    this->stmt2 = stmt2;
}
Try::~Try()
{
    delete this->stmt1;
    delete this->stmt2;
}

Assign::Assign(Exp *exp1, Exp *exp2)
{
    this->exp1 = exp1;
    this->exp2 = exp2;

    this->setType(-42);
    this->setArraySize(-42);
    this->setLexeme(NULL);
    this->setTypeLexeme(NULL);
    this->setLValue(false);
    this->setPointer(false);
}
Assign::~Assign()
{
    delete this->exp1;
    delete this->exp2;
}

NameExp::NameExp(Exp *exp, TokenNode *id)
{
    this->exp = exp;
    this->id = id;

    this->setType(-42);
    this->setArraySize(-42);
    this->setLexeme(NULL);
    this->setTypeLexeme(NULL);
    this->setLValue(false);
    this->setPointer(false);
}
NameExp::~NameExp()
{
    delete this->exp;
    delete this->id;
}

PointerValueExp::PointerValueExp(Exp *exp, TokenNode *id)
{
    this->exp = exp;
    this->id = id;

    this->setType(-42);
    this->setArraySize(-42);
    this->setLexeme(NULL);
    this->setTypeLexeme(NULL);
    this->setLValue(false);
    this->setPointer(false);
}
PointerValueExp::~PointerValueExp()
{
    delete this->id;
    delete this->exp;
}

AddressValue::AddressValue(Exp *exp)
{
    this->exp = exp;

    this->setType(-42);
    this->setArraySize(-42);
    this->setLexeme(NULL);
    this->setTypeLexeme(NULL);
    this->setLValue(false);
    this->setPointer(false);
}

PointerValue::PointerValue(Exp *exp)
{
    this->exp = exp;

    this->setType(-42);
    this->setArraySize(-42);
    this->setLexeme(NULL);
    this->setTypeLexeme(NULL);
    this->setLValue(false);
    this->setPointer(false);
}

Array::Array(Exp *exp, ExpList *explist)
{
    this->exp = exp;
    this->explist = explist;

    this->setType(-42);
    this->setArraySize(-42);
    this->setLexeme(NULL);
    this->setTypeLexeme(NULL);
    this->setLValue(false);
    this->setPointer(false);
}
Array::~Array()
{
    delete this->exp;
    delete this->explist;
}

Call::Call(TokenNode *id, ExpList *explist)
{
    this->id = id;
    this->explist = explist;

    this->setType(-42);
    this->setArraySize(-42);
    this->setLexeme(NULL);
    this->setTypeLexeme(NULL);
    this->setLValue(false);
    this->setPointer(false);
}
Call::~Call()
{
    delete this->id;
    delete this->explist;
}

RelationalOP::RelationalOP(Exp *exp1, Exp *exp2)
{
    this->op = op;
    this->exp1 = exp1;
    this->exp2 = exp2;

    this->setType(-42);
    this->setArraySize(-42);
    this->setLexeme(NULL);
    this->setTypeLexeme(NULL);
    this->setLValue(false);
    this->setPointer(false);
}
RelationalOP::~RelationalOP()
{
    delete this->op;
    delete this->exp1;
    delete this->exp2;
}

AdditionOP::AdditionOP(Exp *exp1, Exp *exp2)
{
    this->op = op;
    this->exp1 = exp1;
    this->exp2 = exp2;

    this->setType(-42);
    this->setArraySize(-42);
    this->setLexeme(NULL);
    this->setTypeLexeme(NULL);
    this->setLValue(false);
    this->setPointer(false);
}
AdditionOP::~AdditionOP()
{
    delete this->op;
    delete this->exp1;
    delete this->exp2;
}

MultiplicationOP::MultiplicationOP(Exp *exp1, Exp *exp2)
{
    this->op = op;
    this->exp1 = exp1;
    this->exp2 = exp2;

    this->setType(-42);
    this->setArraySize(-42);
    this->setLexeme(NULL);
    this->setTypeLexeme(NULL);
    this->setLValue(false);
    this->setPointer(false);
}
MultiplicationOP::~MultiplicationOP()
{
    delete this->op;
    delete this->exp1;
    delete this->exp2;
}

BooleanOP::BooleanOP(Exp *exp1, Exp *exp2)
{
    this->op = op;
    this->exp1 = exp1;
    this->exp2 = exp2;

    this->setLValue(false);
    this->setPointer(false);
    this->setTypeLexeme(NULL);
    this->setArraySize(-42);
    this->setLexeme(NULL);
}
BooleanOP::~BooleanOP()
{
    delete this->op;
    delete this->exp1;
    delete this->exp2;
}

BitwiseOP::BitwiseOP(Exp *exp1, Exp *exp2)
{
    this->op = op;
    this->exp1 = exp1;
    this->exp2 = exp2;

    this->setLValue(false);
    this->setPointer(false);
    this->setTypeLexeme(NULL);
    this->setArraySize(-42);
    this->setLexeme(NULL);
}
BitwiseOP::~BitwiseOP()
{
    delete this->op;
    delete this->exp1;
    delete this->exp2;
}

Sign::Sign(Exp *exp)
{
    this->exp = exp;

    this->setType(-42);
    this->setArraySize(-42);
    this->setLexeme(NULL);
    this->setTypeLexeme(NULL);
    this->setLValue(false);
    this->setPointer(false);
}

Not::Not(Exp *exp)
{
    this->exp = exp;

    this->setType(-42);
    this->setArraySize(-42);
    this->setLexeme(NULL);
    this->setTypeLexeme(NULL);
    this->setLValue(false);
    this->setPointer(false);
}