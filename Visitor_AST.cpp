#include "Visitor_AST.h"
#include "Accept_AST.h"

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

    if (node->FunctionList() != nullptr)
        node->FunctionList()->accept(this);

    if (node->TypeList() != nullptr)
        node->TypeList()->accept(this);

    if (node->VarList() != nullptr)
        node->VarList()->accept(this);
}

void Print_AST::visit(VarList *node)
{
    this->printNode("VAR_LIST");

    if (node->Next() != nullptr)
        node->Next()->accept(this);

    if (node->NameDecl() != nullptr)
        node->NameDecl()->accept(this);
}

void Print_AST::visit(NameDecl *node)
{
    this->printNode("NAME_DECL");

    if (node->Type() != nullptr)
        node->Type()->accept(this);
    if (node->Id() != nullptr)
        node->Id()->accept(this);
}

void Print_AST::visit(FunctionList *node)
{
    this->printNode("FUNCTION_LIST");

    if (node->Type() != nullptr)
        node->Type()->accept(this);
    if (node->Id() != nullptr)
        node->Id()->accept(this);
    if (node->VarList() != nullptr)
        node->VarList()->accept(this);
    if (node->StmtList() != nullptr)
        node->StmtList()->accept(this);
    if (node->Next() != nullptr)
        node->Next()->accept(this);
}

void Print_AST::visit(TypeList *node)
{
    this->printNode("TYPE_LIST");

    if (node->Varlist() != nullptr)
        node->Varlist()->accept(this);
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
    if (node->Pointer() != nullptr)
        node->Pointer()->accept(this);
    if (node->Primitive() != nullptr)
        node->Primitive()->accept(this);
}

void Print_AST::visit(Pointer *node)
{
    this->printNode("POINTER");

    if (node->Type() != nullptr)
        node->Type()->accept(this);
}

void Print_AST::visit(StmtList *node)
{
    this->printNode("STMT_LIST");

    if (node->Stmt() != nullptr)
        node->Stmt()->accept(this);
    if (node->StmtList() != nullptr)
        node->StmtList->accept(this);
    if (node->Next() != nullptr)
        node->Next()->accept(this);
}

void Print_AST::visit(Stmt *node)
{
    this->printNode("STMT");

    if (node->If() != nullptr)
        node->If()->accept(this);
    if (node->While() != nullptr)
        node->While()->accept(this);
    if (node->Switch() != nullptr)
        node->Switch()->accept(this);
    if (node->Break() != nullptr)
        node->Break()->accept(this);
    if (node->PrintLn() != nullptr)
        node->PrintLn()->accept(this);
    if (node->Read() != nullptr)
        node->Read()->accept(this);
    if (node->Return() != nullptr)
        node->Return()->accept(this);
    if (node->Throw() != nullptr)
        node->Throw()->accept(this);
    if (node->StmtList() != nullptr)
        node->StmtList()->accept(this);
    if (node->Call() != nullptr)
        node->Call()->accept(this);
    if (node->Try() != nullptr)
        node->Try()->accept(this);
    if (node->Exp() != nullptr)
        node->Exp()->accept(this);
}

void Print_AST::visit(If *node)
{
    this->printNode("IF");

    if (node->Exp() != nullptr)
        node->Exp()->accept(this);
    if (node->Stmt1() != nullptr)
        node->Stmt1()->accept(this);
    if (node->Stmt2() != nullptr)
        node->Stmt2()->accept(this);
}

void Print_AST::visit(While *node)
{
    this->printNode("WHILE");

    if (node->Exp() != nullptr)
        node->Exp()->accept(this);
    if (node->Stmt() != nullptr)
        node->Stmt()->accept(this);
}

void Print_AST::visit(Switch *node)
{
    this->printNode("SWITCH");

    if (node->Exp() != nullptr)
        node->Exp()->accept(this);
    if (node->CaseBlock() != nullptr)
        node->CaseBlock()->accept(this);
}

void Print_AST::visit(Break *node)
{
    this->printNode("BREAK");

    if (node->Next() != nullptr)
        node->Next()->accept(this);
}

void Print_AST::visit(PrintLn *node)
{
    this->printNode("PRINT_LN");

    if (node->ExpList() != nullptr)
        node->ExpList()->accept(this);
}

void Print_AST::visit(Read *node)
{
    this->printNode("READ");

    if (node->Exp() != nullptr)
        node->Exp()->accept(this);
}

void Print_AST::visit(Return *node)
{
    this->printNode("RETURN");

    if (node->Exp() != nullptr)
        node->Exp()->accept(this);
}

void Print_AST::visit(CaseBlock *node)
{
    this->printNode("CASE_BLOCK");

    if (node->Num() != nullptr)
        node->Num()->accept(this);
    if (node->StmtList() != nullptr)
        node->StmtList()->accept(this);
    if (node->Next() != nullptr)
        node->Next()->accept(this);
}

void Print_AST::visit(Throw *node)
{
    this->printNode("THROW");

    if (node->Next() != nullptr)
        node->Next()->accept(this);
}

void Print_AST::visit(ExpList *node)
{
    this->printNode("EXP_LIST");

    if (node->Exp() != nullptr)
        node->Exp()->accept(this);
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

    if (node->Id() != nullptr)
        node->Id()->accept(this);
    if (node->Number() != nullptr)
        node->Number()->accept(this);
    if (node->Literal() != nullptr)
        node->Literal()->accept(this);
    if (node->Char() != nullptr)
        node->Char()->accept(this);
    if (node->Call() != nullptr)
        node->Call()->accept(this);
    if (node->NameExp() != nullptr)
        node->NameExp()->accept(this);
    if (node->PointerValueExp() != nullptr)
        node->PointerValueExp()->accept(this);
    if (node->AddressValue() != nullptr)
        node->AddressValue()->accept(this);
    if (node->PointerValue() != nullptr)
        node->PointerValue()->accept(this);
    if (node->Array() != nullptr)
        node->Array()->accept(this);
    if (node->Assign() != nullptr)
        node->Assign()->accept(this);
    if (node->RelationalOP() != nullptr)
        node->RelationalOP()->accept(this);
    if (node->AdditionOP() != nullptr)
        node->AdditionOP()->accept(this);
    if (node->MultiplicationOP() != nullptr)
        node->MultiplicationOP()->accept(this);
    if (node->Boolean_OP() != nullptr)
        node->Boolean_OP()->accept(this);
    if (node->BitwiseOP() != nullptr)
        node->BitwiseOP()->accept(this);
    if (node->Not() != nullptr)
        node->Not()->accept(this);
    if (node->Sign() != nullptr)
        node->Sign()->accept(this);
    if (node->True() != nullptr)
        node->True()->accept(this);
    if (node->False() != nullptr)
        node->False()->accept(this);
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

    if (node->Exp() != nullptr)
        node->Exp()->accept(this);
    if (node->Id() != nullptr)
        node->Id()->accept(this);
}

void Print_AST::visit(PointerValueExp *node)
{
    this->printNode("POINTER_EXP");

    if (node->Exp() != nullptr)
        node->Exp()->accept(this);
    if (node->Id() != nullptr)
        node->Id()->accept(this);
}

void Print_AST::visit(AddressValue *node)
{
    this->printNode("ADDRESS_VAL");

    if (node->Exp() != nullptr)
        node->Exp()->accept(this);
}

void Print_AST::visit(PointerValue *node)
{
    this->printNode("POINTER_VAL");

    if (node->Exp() != nullptr)
        node->Exp()->accept(this);
}

void Print_AST::visit(Array *node)
{
    this->printNode("ARRAY");

    if (node->Exp() != nullptr)
        node->Exp()->accept(this);
    if (node->ExpList() != nullptr)
        node->ExpList()->accept(this);
}

void Print_AST::visit(Call *node)
{
    this->printNode("CALL");

    if (node->Id() != nullptr)
        node->Id()->accept(this);
    if (node->ExpList() != nullptr)
        node->ExpList()->accept(this);
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

    if (node->Next() != nullptr)
        node->Next()->accept(this);
}

void Print_AST::visit(False *node)
{
    this->printNode("FALSE");

    if (node->Next() != nullptr)
        node->Next()->accept(this);
}

void Print_AST::visit(Not *node)
{
    this->printNode("NOT");

    if (node->Exp() != nullptr)
        node->Exp()->accept(this);
}

void Print_AST::visit(Sign *node)
{
    this->printNode("SIGN");

    if (node->Exp() != nullptr)
        node->Exp()->accept(this);
}