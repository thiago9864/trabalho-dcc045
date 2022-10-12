
#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <iostream>

namespace c_namespace
{

    class SymbolTable
    {
    private:
        int value;

    public:
        SymbolTable();
        ~SymbolTable();

        void setInt(int v);
        void printObj();
    };

} // namespace c_namespace

#endif // SYMBOL_TABLE_H