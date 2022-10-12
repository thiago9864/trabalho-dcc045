
#ifndef TABLE_ENTRY_H
#define TABLE_ENTRY_H

class TableEntry
{
public:
    int lexeme; // lexeme vector index
    int token;
    TableEntry *next;
};

#endif // TABLE_ENTRY_H