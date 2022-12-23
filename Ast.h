#ifndef AST_H
#define AST_H

#include <iostream>
#include "Visitor_AST.h"

class Root;
class TokenNode;
class Program;
class VarList;
class NameDecl;
class FunctionList;
class TypeList;
class Type;
class Pointer;
class StmtList;
class Stmt;
class If;
class While;
class Switch;
class Break;
class PrintLn;
class Read;
class Return;
class CaseBlock;
class Throw;
class ExpList;
class Try;
class Exp;
class Assign;
class NameExp;
class PointerValueExp;
class AddressValue;
class PointerValue;
class Array;
class Call;
class RelationalOP;
class AdditionOP;
class MultiplicationOP;
class BooleanOP;
class BitwiseOP;
class True;
class False;
class Not;
class Sign;

class Ast {
    protected:
        int line;
    public:
        virtual ~Ast() = default;
        inline int getLine() { return line; }
        virtual inline void setLine(int line) { this->line = line; }
        virtual void accept(Visitor *visitor) = 0;
};



#endif 