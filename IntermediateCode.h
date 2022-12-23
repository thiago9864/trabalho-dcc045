#ifndef INTERMEDIATE_CODE_H
#define INTERMEDIATE_CODE_H

#include <cstdio>
#include <cstring>
#include "TokenDefinitions.h"
#include "Visitor_CST.h"

//STM_NODES
#define V_CONST 0
#define V_CONSTF 1
#define V_NAME 2
#define V_TEMP 3
#define V_BINOP 4
#define V_MEM 5
#define V_CALL 6
#define V_ESEQ 7

//EXP_NODES
#define V_MOVE 8
#define V_EXP 9
#define V_JUMP 10
#define V_CJUMP 11
#define V_SEQ 12
#define V_LABEL 13

//LIST_NODES
#define V_STM_LIST 14
#define V_EXP_LIST 15

extern int num_labels;
extern int num_temps;

//forward declarations
class Program ;
class Type ;
class IdList ;
class Array ;
class TypeDecl ;
class VarFn ;
class VarDecl ;
class FunctionDecl ;
class FormalRest ;
class FormalList ;
class FunctionBody ;
class ExprList ;
class StmtList ;
class CaseBlock ;
class Stmt ;
class IfOpt ;
class ElseOpt ;
class ExpSemID ;
class ExpSemIDL ;
class Primary ;
class PrimaryL ;


#endif //INTERMEDIATE_CODE_H