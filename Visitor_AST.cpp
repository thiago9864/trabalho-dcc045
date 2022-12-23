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