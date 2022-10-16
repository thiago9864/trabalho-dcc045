#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <string>
#include "TableEntry.h"
#include "TokenDefinitions.h"

#define TABLE_SIZE 127
#define LEXEME_ARRAY 1024

namespace c_namespace
{
    class SymbolTable
    {
    private:
        int lexArray_size;
        int lexArray_pos;
        char *lexArray; // lexeme array

        TableEntry **table; // hash table

    public:
        SymbolTable();
        virtual ~SymbolTable() = 0;

        int hashFuntion(std::string const &lexeme);

        void insert(TableEntry *entry, const char *lexeme);
        TableEntry *searchLexeme(const char *lexeme);

        void print();
        void print_LexArray();
    };

    class ReservedWordTable : public SymbolTable
    {
    public:
        void insert(const char *lexeme, int token);
        ReservedWordEntry *searchLexeme(const char *lexeme);
    };

    class IdentifierTable : public SymbolTable
    {
    public:
        void insert(char const *lexeme);
        IdentifierEntry *searchLexeme(const char *lexeme);
    };

    class NumTable : public SymbolTable
    {
    public:
        void insert(char const *lexeme);
        NumEntry *searchLexeme(const char *lexeme);
    };

    class LiteralTable : public SymbolTable
    {
    public:
        void insert(char const *lexeme);
        LiteralEntry *searchLexeme(const char *lexeme);
    };

} // namespace c_namespace

#endif // SYMBOL_TABLE_H
