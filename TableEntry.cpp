#include "TableEntry.h"

namespace c_namespace
{
    // Constructor
    TableEntry::TableEntry(int lexIndex, int token)
    {
        this->lexIndex = lexIndex;
        this->token = token;
        next = NULL;
    };
    // Destructor
    TableEntry::~TableEntry()
    {
        delete next;
    };

    void TableEntry::setLexIndex(int lexIndex)
    {
        this->lexIndex = lexIndex;
    }
    int TableEntry::getLexIndex()
    {
        return lexIndex;
    }

    void TableEntry::setToken(int v)
    {
        token = v;
    }
    int TableEntry::getToken()
    {
        return token;
    }

    void TableEntry::setNext(TableEntry *nextptr)
    {
        next = nextptr;
    }
    TableEntry *TableEntry::getNext()
    {
        return next;
    }

    ReservedWordEntry::ReservedWordEntry(int lexIndex, int token) : TableEntry(lexIndex, token) {}

    IdentifierEntry::IdentifierEntry(int lexIndex, int token) : TableEntry(lexIndex, token) {}

    LiteralEntry::LiteralEntry(int lexIndex, int token) : TableEntry(lexIndex, token) {}

    NumEntry::NumEntry(int lexIndex, int token) : TableEntry(lexIndex, token) {}
}
