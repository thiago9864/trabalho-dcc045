#include "Visitor.h"

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

void Print_AST::visit(Program *node)
{
    std::cout << std::endl
              << "******************* ABSTRACT SYNTAX TREE *******************" << std::endl
              << std::endl;
    this->printNode("PROGRAM");
}

void Print_AST::visit(VarList *node)
{
    this->printNode("VAR_LIST");
}

void Print_AST::visit(NameDecl *node)
{
    this->printNode("NAME_DECL");
}

void Print_AST::visit(FunctionList *node)
{
    this->printNode("FUNCTION_LIST");
}

void Print_AST::visit(TypeList *node)
{
    this->printNode("TYPE_LIST");
}

void Print_AST::visit(StmtList *node)
{
    this->printNode("STMT_LIST");
}

void Print_AST::visit(Stmt *node)
{
    this->printNode("STMT");
}

void Print_AST::visit(If *node)
{
    this->printNode("IF");
}

void Print_AST::visit(While *node)
{
    this->printNode("WHILE");
}

void Print_AST::visit(Switch *node)
{
    this->printNode("SWITCH");
}

void Print_AST::visit(PrintLn *node)
{
    this->printNode("PRINT_LN");
}

void Print_AST::visit(Read *node)
{
    this->printNode("READ");
}

void Print_AST::visit(Return *node)
{
    this->printNode("RETURN");
}

void Print_AST::visit(CaseBlock *node)
{
    this->printNode("CASE_BLOCK");
}

void Print_AST::visit(ExpList *node)
{
    this->printNode("EXP_LIST");
}

void Print_AST::visit(Try *node)
{
    this->printNode("TRY");
}

void Print_AST::visit(Exp *node)
{
    this->printNode("EXP");
}

void Print_AST::visit(Assign *node)
{
    this->printNode("ASSIGN");
}

void Print_AST::visit(NameExp *node)
{
    this->printNode("NAME_EXP");
}

void Print_AST::visit(PointerValueExp *node)
{
    this->printNode("POINTER_EXP");
}

void Print_AST::visit(AddressValue *node)
{
    this->printNode("ADDRESS_VAL");
}

void Print_AST::visit(PointerValue *node)
{
    this->printNode("POINTER_VAL");
}

void Print_AST::visit(Array *node)
{
    this->printNode("ARRAY");
}

void Print_AST::visit(Call *node)
{
    this->printNode("CALL");
}

void Print_AST::visit(RelationalOP *node)
{
    this->printNode("RELATIONAL_OP");
}

void Print_AST::visit(AdditionOP *node)
{
    this->printNode("ADD_OP");
}

void Print_AST::visit(MultiplicationOP *node)
{
    this->printNode("MULT_OP");
}

void Print_AST::visit(BooleanOP *node)
{
    this->printNode("BOOL_OP");
}

void Print_AST::visit(BitwiseOP *node)
{
    this->printNode("BITWISE_OP");
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
}

void Print_AST::visit(Sign *node)
{
    this->printNode("SIGN");
}

/*
 * TERMINAL NODES
 */
void Print_AST::visit(Pointer *node)
{
    this->printNode("POINTER");
}

void Print_AST::visit(Break *node)
{
    this->printNode("BREAK");
}

void Print_AST::visit(Throw *node)
{
    this->printNode("THROW");
}

void Print_AST::visit(Type *node)
{
    this->printNode("TYPE");
}