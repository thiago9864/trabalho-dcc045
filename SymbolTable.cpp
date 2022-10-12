

#include "SymbolTable.h"

namespace c_namespace
{
    // Constructor
    SymbolTable::SymbolTable()
    {
        value = 0;
    };
    // Destructor
    SymbolTable::~SymbolTable(){

    };

    void SymbolTable::setInt(int v)
    {
        value = v;
    }
    void SymbolTable::printObj()
    {
        std::cout << "Teste do objeto " << value << std::endl;
    }
}