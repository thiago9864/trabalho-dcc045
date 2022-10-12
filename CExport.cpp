#include "CExport.h"
#include "SymbolTable.h"

using namespace c_namespace;

namespace
{
    SymbolTable cppObj;
} // namespace name

void setObjValue(int v){
    cppObj.setInt(v);
}
void printObjValue(){
    cppObj.printObj();
}