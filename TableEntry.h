
#ifndef TABLE_ENTRY_H
#define TABLE_ENTRY_H

#include <iostream>

namespace c_namespace
{
    class TableEntry
    {
    private:
        int lexIndex; // lexeme vector index
        int token;
        TableEntry *next; // pointer next equal token lexeme

    public:
        TableEntry(int lexIndex, int token);
        ~TableEntry();

        void setLexIndex(int lexIndex);
        int getLexIndex();

        void setToken(int t);
        int getToken();

        void setNext(TableEntry *nextptr);
        TableEntry *getNext();
    };

    class ReservedWordEntry : public TableEntry
    {
    public:
        ReservedWordEntry(int lexIndex, int token);
    };

    class IdentifierEntry : public TableEntry
    {
    public:
        IdentifierEntry(int lexIndex, int token);
    };

    class LiteralEntry : public TableEntry
    {
    public:
        LiteralEntry(int lexIndex, int token);
    };

    class NumEntry : public TableEntry
    {
    public:
        NumEntry(int lexIndex, int token);
    };
}

#endif // TABLE_ENTRY_H