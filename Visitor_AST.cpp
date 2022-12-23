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

void Print_AST::visit(Program *node)
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

void Print_AST::visit(VarList *node)
{
    this->printNode("VAR_LIST");

    if (node->Next() != nullptr)
        node->Next()->accept(this);
    if (node->getNameDecl() != nullptr)
        node->getNameDecl()->accept(this);
}

void Print_AST::visit(NameDecl *node)
{
    this->printNode("NAME_DECL");

    if (node->getType() != nullptr)
        node->getType()->accept(this);
    if (node->Id() != nullptr)
        node->Id()->accept(this);
}

void Print_AST::visit(FunctionList *node)
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

void Print_AST::visit(TypeList *node)
{
    this->printNode("TYPE_LIST");

    if (node->getVarlist() != nullptr)
        node->getVarlist()->accept(this);
    if (node->Id() != nullptr)
        node->Id()->accept(this);
    if (node->Next() != nullptr)
        node->Next()->accept(this);
}

void Print_AST::visit(Type *node)
{
    this->printNode("TYPE");

    if (node->Id() != nullptr)
        node->Id()->accept(this);
}

void Print_AST::visit(Pointer *node)
{
    this->printNode("POINTER");
}

void Print_AST::visit(StmtList *node)
{
    this->printNode("STMT_LIST");

    if (node->getStmt() != nullptr)
        node->getStmt()->accept(this);
    if (node->Next() != nullptr)
        node->Next()->accept(this);
}

void Print_AST::visit(Stmt *node)
{
    this->printNode("STMT");
    if (node->getStmt() != nullptr)
    {
        node->getStmt()->accept(this);
    }
}

void Print_AST::visit(If *node)
{
    this->printNode("IF");

    if (node->getExp() != nullptr)
        node->getExp()->accept(this);
    if (node->Stmt1() != nullptr)
        node->Stmt1()->accept(this);
    if (node->Stmt2() != nullptr)
        node->Stmt2()->accept(this);
}

void Print_AST::visit(While *node)
{
    this->printNode("WHILE");

    if (node->getExp() != nullptr)
        node->getExp()->accept(this);
    if (node->getStmt() != nullptr)
        node->getStmt()->accept(this);
}

void Print_AST::visit(Switch *node)
{
    this->printNode("SWITCH");

    if (node->getExp() != nullptr)
        node->getExp()->accept(this);
    if (node->getCaseBlock() != nullptr)
        node->getCaseBlock()->accept(this);
}

void Print_AST::visit(Break *node)
{
    this->printNode("BREAK");
}

void Print_AST::visit(PrintLn *node)
{
    this->printNode("PRINT_LN");

    if (node->getExpList() != nullptr)
        node->getExpList()->accept(this);
}

void Print_AST::visit(Read *node)
{
    this->printNode("READ");

    if (node->getExp() != nullptr)
        node->getExp()->accept(this);
}

void Print_AST::visit(Return *node)
{
    this->printNode("RETURN");

    if (node->getExp() != nullptr)
        node->getExp()->accept(this);
}

void Print_AST::visit(CaseBlock *node)
{
    this->printNode("CASE_BLOCK");

    if (node->Num() != nullptr)
        node->Num()->accept(this);
    if (node->getStmtList() != nullptr)
        node->getStmtList()->accept(this);
    if (node->Next() != nullptr)
        node->Next()->accept(this);
}

void Print_AST::visit(Throw *node)
{
    this->printNode("THROW");
}

void Print_AST::visit(ExpList *node)
{
    this->printNode("EXP_LIST");

    if (node->getExp() != nullptr)
        node->getExp()->accept(this);
    if (node->Next() != nullptr)
        node->Next()->accept(this);
}

void Print_AST::visit(Try *node)
{
    this->printNode("TRY");

    if (node->Stmt1() != nullptr)
        node->Stmt1()->accept(this);
    if (node->Stmt2() != nullptr)
        node->Stmt2()->accept(this);
}

void Print_AST::visit(Exp *node)
{
    this->printNode("EXP");
}

void Print_AST::visit(Assign *node)
{
    this->printNode("ASSIGN");

    if (node->Exp1() != nullptr)
        node->Exp1()->accept(this);
    if (node->Exp2() != nullptr)
        node->Exp2()->accept(this);
}

void Print_AST::visit(NameExp *node)
{
    this->printNode("NAME_EXP");

    if (node->getExp() != nullptr)
        node->getExp()->accept(this);
    if (node->Id() != nullptr)
        node->Id()->accept(this);
}

void Print_AST::visit(PointerValueExp *node)
{
    this->printNode("POINTER_EXP");

    if (node->getExp() != nullptr)
        node->getExp()->accept(this);
    if (node->Id() != nullptr)
        node->Id()->accept(this);
}

void Print_AST::visit(AddressValue *node)
{
    this->printNode("ADDRESS_VAL");

    if (node->getExp() != nullptr)
        node->getExp()->accept(this);
}

void Print_AST::visit(PointerValue *node)
{
    this->printNode("POINTER_VAL");

    if (node->getExp() != nullptr)
        node->getExp()->accept(this);
}

void Print_AST::visit(Array *node)
{
    this->printNode("ARRAY");

    if (node->getExp() != nullptr)
        node->getExp()->accept(this);
    if (node->getExpList() != nullptr)
        node->getExpList()->accept(this);
}

void Print_AST::visit(Call *node)
{
    this->printNode("CALL");

    if (node->Id() != nullptr)
        node->Id()->accept(this);
    if (node->getExpList() != nullptr)
        node->getExpList()->accept(this);
}

void Print_AST::visit(RelationalOP *node)
{
    this->printNode("RELATIONAL_OP");

    if (node->Exp1() != nullptr)
        node->Exp1()->accept(this);
    if (node->Exp2() != nullptr)
        node->Exp2()->accept(this);
}

void Print_AST::visit(AdditionOP *node)
{
    this->printNode("ADD_OP");

    if (node->Exp1() != nullptr)
        node->Exp1()->accept(this);
    if (node->Exp2() != nullptr)
        node->Exp2()->accept(this);
}

void Print_AST::visit(MultiplicationOP *node)
{
    this->printNode("MULT_OP");

    if (node->Exp1() != nullptr)
        node->Exp1()->accept(this);
    if (node->Exp2() != nullptr)
        node->Exp2()->accept(this);
}

void Print_AST::visit(BooleanOP *node)
{
    this->printNode("BOOL_OP");

    if (node->Exp1() != nullptr)
        node->Exp1()->accept(this);
    if (node->Exp2() != nullptr)
        node->Exp2()->accept(this);
}

void Print_AST::visit(BitwiseOP *node)
{
    this->printNode("BITWISE_OP");

    if (node->Exp1() != nullptr)
        node->Exp1()->accept(this);
    if (node->Exp2() != nullptr)
        node->Exp2()->accept(this);
}

void Print_AST::visit(True *node)
{
    this->printNode("TRUE");
}

void Print_AST::visit(False *node)
{
    this->printNode("FALSE");
}

void Print_AST::visit(Not *node)
{
    this->printNode("NOT");

    if (node->getExp() != nullptr)
        node->getExp()->accept(this);
}

void Print_AST::visit(Sign *node)
{
    this->printNode("SIGN");

    if (node->getExp() != nullptr)
        node->getExp()->accept(this);
}