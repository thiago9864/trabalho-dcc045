#include "Visitor_AST.h"

Print_AST::Print_AST()
{
    height = 0;
}

void Print_AST::up_height()
{
    this->height++;
}

void Print_AST::down_height()
{
    this->height--;
}

void Print_AST::printNode(const char *node)
{
    for (unsigned int i = 0; i < this->height; i++)
        std::cout << "    ";
    std::cout << "-" << node << std::endl;
}

void Print_AST::printLexeme(const char *node, const char *lexeme)
{
    for (unsigned int i = 0; i < this->height; i++)
        std::cout << "    ";
    std::cout << "-" << node << "." << lexeme << std::endl;
}

void Print_AST::visit(TokenNode *node)
{
    if (node->getLexeme() != nullptr)
    {
        this->printLexeme(getTokenName(node->getToken()), node->getLexeme());
    }
    else
    {
        this->printNode(getTokenName(node->getToken()));
    }
}

void Print_AST::visit(Program_Node *node)
{
    std::cout << std::endl
              << "******************* ABSTRACT SYNTAX TREE *******************" << std::endl
              << std::endl;
    this->printNode("PROGRAM");

    if (node->getFunctionList() != nullptr)
        node->getFunctionList()->accept(this);
    if (node->getTypeList() != nullptr)
        node->getTypeList()->accept(this);
    if (node->getVarList() != nullptr)
        node->getVarList()->accept(this);
}

void Print_AST::visit(VarList_Node *node)
{
    this->printNode("VAR_LIST");

    if (node->Next() != nullptr)
        node->Next()->accept(this);
    if (node->getNameDecl() != nullptr)
        node->getNameDecl()->accept(this);
}

void Print_AST::visit(NameDecl_Node *node)
{
    this->printNode("NAME_DECL");

    if (node->getType() != nullptr)
        node->getType()->accept(this);
    if (node->Id() != nullptr)
        node->Id()->accept(this);
}

void Print_AST::visit(FunctionList_Node *node)
{
    this->printNode("FUNCTION_LIST");

    if (node->getType() != nullptr)
        node->getType()->accept(this);
    if (node->Id() != nullptr)
        node->Id()->accept(this);
    if (node->getVarList() != nullptr)
        node->getVarList()->accept(this);
    if (node->getStmtList() != nullptr)
        node->getStmtList()->accept(this);
    if (node->Next() != nullptr)
        node->Next()->accept(this);
}

void Print_AST::visit(TypeList_Node *node)
{
    this->printNode("TYPE_LIST");

    if (node->getVarlist() != nullptr)
        node->getVarlist()->accept(this);
    if (node->Id() != nullptr)
        node->Id()->accept(this);
    if (node->Next() != nullptr)
        node->Next()->accept(this);
}

void Print_AST::visit(Type_Node *node)
{
    this->printNode("TYPE");

    if (node->Id() != nullptr)
        node->Id()->accept(this);
}

void Print_AST::visit(Pointer_Node *node)
{
    this->printNode("POINTER");
}

void Print_AST::visit(StmtList_Node *node)
{
    this->printNode("STMT_LIST");

    if (node->getStmt() != nullptr)
        node->getStmt()->accept(this);
    if (node->Next() != nullptr)
        node->Next()->accept(this);
}

void Print_AST::visit(Stmt_Node *node)
{
    this->printNode("STMT");
    if (node->getStmt() != nullptr)
    {
        node->getStmt()->accept(this);
    }
}

void Print_AST::visit(If_Node *node)
{
    this->printNode("IF");

    if (node->getExp() != nullptr)
        node->getExp()->accept(this);
    if (node->Stmt1() != nullptr)
        node->Stmt1()->accept(this);
    if (node->Stmt2() != nullptr)
        node->Stmt2()->accept(this);
}

void Print_AST::visit(While_Node *node)
{
    this->printNode("WHILE");

    if (node->getExp() != nullptr)
        node->getExp()->accept(this);
    if (node->getStmt() != nullptr)
        node->getStmt()->accept(this);
}

void Print_AST::visit(Switch_Node *node)
{
    this->printNode("SWITCH");

    if (node->getExp() != nullptr)
        node->getExp()->accept(this);
    if (node->getCaseBlock() != nullptr)
        node->getCaseBlock()->accept(this);
}

void Print_AST::visit(Break_Node *node)
{
    this->printNode("BREAK");
}

void Print_AST::visit(PrintLn_Node *node)
{
    this->printNode("PRINT_LN");

    if (node->getExpList() != nullptr)
        node->getExpList()->accept(this);
}

void Print_AST::visit(Read_Node *node)
{
    this->printNode("READ");

    if (node->getExp() != nullptr)
        node->getExp()->accept(this);
}

void Print_AST::visit(Return_Node *node)
{
    this->printNode("RETURN");

    if (node->getExp() != nullptr)
        node->getExp()->accept(this);
}

void Print_AST::visit(CaseBlock_Node *node)
{
    this->printNode("CASE_BLOCK");

    if (node->Num() != nullptr)
        node->Num()->accept(this);
    if (node->getStmtList() != nullptr)
        node->getStmtList()->accept(this);
    if (node->Next() != nullptr)
        node->Next()->accept(this);
}

void Print_AST::visit(Throw_Node *node)
{
    this->printNode("THROW");
}

void Print_AST::visit(ExpList_Node *node)
{
    this->printNode("EXP_LIST");

    if (node->getExp() != nullptr)
        node->getExp()->accept(this);
    if (node->Next() != nullptr)
        node->Next()->accept(this);
}

void Print_AST::visit(Try_Node *node)
{
    this->printNode("TRY");

    if (node->Stmt1() != nullptr)
        node->Stmt1()->accept(this);
    if (node->Stmt2() != nullptr)
        node->Stmt2()->accept(this);
}

void Print_AST::visit(Exp_Node *node)
{
    this->printNode("EXP");
}

void Print_AST::visit(Assign_Node *node)
{
    this->printNode("ASSIGN");

    if (node->Exp1() != nullptr)
        node->Exp1()->accept(this);
    if (node->Exp2() != nullptr)
        node->Exp2()->accept(this);
}

void Print_AST::visit(NameExp_Node *node)
{
    this->printNode("NAME_EXP");

    if (node->getExp() != nullptr)
        node->getExp()->accept(this);
    if (node->Id() != nullptr)
        node->Id()->accept(this);
}

void Print_AST::visit(PointerValueExp_Node *node)
{
    this->printNode("POINTER_EXP");

    if (node->getExp() != nullptr)
        node->getExp()->accept(this);
    if (node->Id() != nullptr)
        node->Id()->accept(this);
}

void Print_AST::visit(AddressValue_Node *node)
{
    this->printNode("ADDRESS_VAL");

    if (node->getExp() != nullptr)
        node->getExp()->accept(this);
}

void Print_AST::visit(PointerValue_Node *node)
{
    this->printNode("POINTER_VAL");

    if (node->getExp() != nullptr)
        node->getExp()->accept(this);
}

void Print_AST::visit(Array_Node *node)
{
    this->printNode("ARRAY");

    if (node->getExp() != nullptr)
        node->getExp()->accept(this);
    if (node->getExpList() != nullptr)
        node->getExpList()->accept(this);
}

void Print_AST::visit(Call_Node *node)
{
    this->printNode("CALL");

    if (node->Id() != nullptr)
        node->Id()->accept(this);
    if (node->getExpList() != nullptr)
        node->getExpList()->accept(this);
}

void Print_AST::visit(RelationalOP_Node *node)
{
    this->printNode("RELATIONAL_OP");

    if (node->Exp1() != nullptr)
        node->Exp1()->accept(this);
    if (node->Exp2() != nullptr)
        node->Exp2()->accept(this);
}

void Print_AST::visit(AdditionOP_Node *node)
{
    this->printNode("ADD_OP");

    if (node->Exp1() != nullptr)
        node->Exp1()->accept(this);
    if (node->Exp2() != nullptr)
        node->Exp2()->accept(this);
}

void Print_AST::visit(MultiplicationOP_Node *node)
{
    this->printNode("MULT_OP");

    if (node->Exp1() != nullptr)
        node->Exp1()->accept(this);
    if (node->Exp2() != nullptr)
        node->Exp2()->accept(this);
}

void Print_AST::visit(BooleanOP_Node *node)
{
    this->printNode("BOOL_OP");

    if (node->Exp1() != nullptr)
        node->Exp1()->accept(this);
    if (node->Exp2() != nullptr)
        node->Exp2()->accept(this);
}

void Print_AST::visit(BitwiseOP_Node *node)
{
    this->printNode("BITWISE_OP");

    if (node->Exp1() != nullptr)
        node->Exp1()->accept(this);
    if (node->Exp2() != nullptr)
        node->Exp2()->accept(this);
}

void Print_AST::visit(True_Node *node)
{
    this->printNode("TRUE");
}

void Print_AST::visit(False_Node *node)
{
    this->printNode("FALSE");
}

void Print_AST::visit(Not_Node *node)
{
    this->printNode("NOT");

    if (node->getExp() != nullptr)
        node->getExp()->accept(this);
}

void Print_AST::visit(Sign_Node *node)
{
    this->printNode("SIGN");

    if (node->getExp() != nullptr)
        node->getExp()->accept(this);
}

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

Program_Node::Program_Node(FunctionList_Node *functionlist, TypeList_Node *typelist, VarList_Node *varlist)
{
    this->functionlist = functionlist;
    this->typelist = typelist;
    this->varlist = varlist;
}
Program_Node::~Program_Node()
{
    delete this->varlist;
    delete this->typelist;
    delete this->functionlist;
}

VarList_Node::VarList_Node(NameDecl_Node *namedecl, VarList_Node *next)
{
    this->namedecl = namedecl;
    this->next = next;
}
VarList_Node::~VarList_Node()
{
    delete this->namedecl;
    delete this->next;
}

FunctionList_Node::FunctionList_Node(Type_Node *type, TokenNode *id, VarList_Node *varlist, StmtList_Node *stmtlist, FunctionList_Node *next)
{
    this->type = type;
    this->id = id;
    this->varlist = varlist;
    this->stmtlist = stmtlist;
    this->next = next;
}
FunctionList_Node::~FunctionList_Node()
{
    delete this->type;
    delete this->id;
    delete this->varlist;
    delete this->stmtlist;
    delete this->next;
}

TypeList_Node::TypeList_Node(VarList_Node *varlist, TokenNode *id, TypeList_Node *next)
{
    this->varlist = varlist;
    this->id = id;
    this->next = next;
}
TypeList_Node::~TypeList_Node()
{
    delete this->varlist;
    delete this->id;
    delete this->next;
}

NameDecl_Node::NameDecl_Node(Type_Node *type, TokenNode *id)
{
    this->type = type;
    this->id = id;
}
NameDecl_Node::~NameDecl_Node()
{
    delete this->type;
    delete this->id;
}

StmtList_Node::StmtList_Node(Stmt_Node *stmt1, StmtList_Node *next1)
{
    this->stmt = stmt;
    this->next = next;
}
StmtList_Node::~StmtList_Node()
{
    delete this->next;
    delete this->stmt;
}

If_Node::If_Node(Exp_Node *exp, Stmt_Node *stmt1, Stmt_Node *stmt2)
{
    this->exp = exp;
    this->stmt1 = stmt1;
    this->stmt2 = stmt2;
}
If_Node::~If_Node()
{
    delete this->exp;
    delete this->stmt1;
    delete this->stmt2;
}

While_Node::While_Node(Exp_Node *exp, Stmt_Node *stmt)
{
    this->exp = exp;
    this->stmt = stmt;
}
While_Node::~While_Node()
{
    delete this->exp;
    delete this->stmt;
}

Switch_Node::Switch_Node(Exp_Node *exp, CaseBlock_Node *caseblock)
{
    this->exp = exp;
    this->caseblock = caseblock;
}
Switch_Node::~Switch_Node()
{
    delete this->exp;
    delete this->caseblock;
}

CaseBlock_Node::CaseBlock_Node(TokenNode *num, StmtList_Node *stmtlist, CaseBlock_Node *next)
{
    this->num = num;
    this->stmtlist = stmtlist;
    this->next = next;
}
CaseBlock_Node::~CaseBlock_Node()
{
    delete this->num;
    delete this->stmtlist;
    delete this->next;
}

ExpList_Node::ExpList_Node(Exp_Node *exp, ExpList_Node *next)
{
    this->exp = exp;
    this->next = next;
}
ExpList_Node::~ExpList_Node()
{
    delete this->exp;
    delete this->next;
}

Try_Node::Try_Node(Stmt_Node *stmt1, Stmt_Node *stmt2)
{
    this->stmt1 = stmt1;
    this->stmt2 = stmt2;
}
Try_Node::~Try_Node()
{
    delete this->stmt1;
    delete this->stmt2;
}

Assign_Node::Assign_Node(Exp_Node *exp1, Exp_Node *exp2)
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
Assign_Node::~Assign_Node()
{
    delete this->exp1;
    delete this->exp2;
}

NameExp_Node::NameExp_Node(Exp_Node *exp, TokenNode *id)
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
NameExp_Node::~NameExp_Node()
{
    delete this->exp;
    delete this->id;
}

PointerValueExp_Node::PointerValueExp_Node(Exp_Node *exp, TokenNode *id)
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
PointerValueExp_Node::~PointerValueExp_Node()
{
    delete this->id;
    delete this->exp;
}

AddressValue_Node::AddressValue_Node(Exp_Node *exp)
{
    this->exp = exp;

    this->setType(-42);
    this->setArraySize(-42);
    this->setLexeme(NULL);
    this->setTypeLexeme(NULL);
    this->setLValue(false);
    this->setPointer(false);
}

PointerValue_Node::PointerValue_Node(Exp_Node *exp)
{
    this->exp = exp;

    this->setType(-42);
    this->setArraySize(-42);
    this->setLexeme(NULL);
    this->setTypeLexeme(NULL);
    this->setLValue(false);
    this->setPointer(false);
}

Array_Node::Array_Node(Exp_Node *exp, ExpList_Node *explist)
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
Array_Node::~Array_Node()
{
    delete this->exp;
    delete this->explist;
}

Call_Node::Call_Node(TokenNode *id, ExpList_Node *explist)
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
Call_Node::~Call_Node()
{
    delete this->id;
    delete this->explist;
}

RelationalOP_Node::RelationalOP_Node(Exp_Node *exp1, Exp_Node *exp2)
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
RelationalOP_Node::~RelationalOP_Node()
{
    delete this->op;
    delete this->exp1;
    delete this->exp2;
}

AdditionOP_Node::AdditionOP_Node(Exp_Node *exp1, Exp_Node *exp2)
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
AdditionOP_Node::~AdditionOP_Node()
{
    delete this->op;
    delete this->exp1;
    delete this->exp2;
}

MultiplicationOP_Node::MultiplicationOP_Node(Exp_Node *exp1, Exp_Node *exp2)
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
MultiplicationOP_Node::~MultiplicationOP_Node()
{
    delete this->op;
    delete this->exp1;
    delete this->exp2;
}

BooleanOP_Node::BooleanOP_Node(Exp_Node *exp1, Exp_Node *exp2)
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
BooleanOP_Node::~BooleanOP_Node()
{
    delete this->op;
    delete this->exp1;
    delete this->exp2;
}

BitwiseOP_Node::BitwiseOP_Node(Exp_Node *exp1, Exp_Node *exp2)
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
BitwiseOP_Node::~BitwiseOP_Node()
{
    delete this->op;
    delete this->exp1;
    delete this->exp2;
}

Sign_Node::Sign_Node(Exp_Node *exp)
{
    this->exp = exp;

    this->setType(-42);
    this->setArraySize(-42);
    this->setLexeme(NULL);
    this->setTypeLexeme(NULL);
    this->setLValue(false);
    this->setPointer(false);
}

Not_Node::Not_Node(Exp_Node *exp)
{
    this->exp = exp;

    this->setType(-42);
    this->setArraySize(-42);
    this->setLexeme(NULL);
    this->setTypeLexeme(NULL);
    this->setLValue(false);
    this->setPointer(false);
}