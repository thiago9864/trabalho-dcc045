#include "SymbolTable.h"

namespace c_namespace
{
    // Constructor
    SymbolTable::SymbolTable()
    {
        lexArray_size = 0;
        lexArray_pos = 0;
        lexArray = new char[LEXEME_ARRAY]();

        table = new TableEntry *[TABLE_SIZE];
        memset(table, 0, sizeof(table) * TABLE_SIZE);
    };
    // Destructor
    SymbolTable::~SymbolTable()
    {
        delete table;
        delete lexArray;
    };

    int SymbolTable::hashFuntion(std::string const &lexeme)
    {
        int prime = 131; // first prime number greater than number of characters in the ASCII table
        int mult = 1e9 + 9;

        long long hash_value = 0;
        long long p_pow = 1;

        for (char c : lexeme)
        {
            hash_value = (hash_value + (c - 'a' + 1) * p_pow) % mult;
            p_pow = (p_pow * prime) % mult;
        }
        return hash_value % TABLE_SIZE;
    };

    void SymbolTable::insert(TableEntry *entry, const char *lexeme)
    {
        if (lexeme != NULL)
        {
            int index = hashFuntion(lexeme);

            entry->setNext(table[index]);

            table[index] = entry;

            if ((unsigned)lexArray_size <= (unsigned)(lexArray_pos + strlen(lexeme)))
            {
                while ((unsigned)lexArray_size <= (unsigned)(lexArray_pos + strlen(lexeme)))
                {
                    lexArray_size += LEXEME_ARRAY;
                }
                lexArray = (char *)realloc(lexArray, lexArray_size * sizeof(char));
            }

            strcpy(lexArray + lexArray_pos, lexeme);

            entry->setLexIndex(lexArray_pos);

            lexArray_pos = lexArray_pos + ((int)strlen(lexeme) + 1);
        }
    }

    TableEntry *SymbolTable::searchLexeme(const char *lexeme)
    {
        if (lexeme != NULL)
        {
            int index = hashFuntion(lexeme);

            TableEntry *entry = table[index];

            while (entry != NULL)
            {
                if (strcmp(lexArray + entry->getLexIndex(), lexeme) == 0)
                {
                    return entry;
                }
                entry = entry->getNext();
            }
            return NULL;
        }
        return NULL;
    }

    void SymbolTable::print()
    {
        std::cout << std::endl;
        for (int i = 0; i < TABLE_SIZE; ++i)
        {
            TableEntry *entry = table[i];

            while (entry != NULL)
            {
                int index = entry->getLexIndex();

                std::cout << "table_position = " << i << " | lexeme_array_positon = " << index << " | token = " << entry->getToken() << " | lexeme = ";

                // Cycle through each lexeme character in the lexeme array
                for (int j = 0; j < 20; j++)
                {
                    if (lexArray[index + j] == 0)
                        break;
                    std::cout << lexArray[index + j];
                }

                std::cout << std::endl;

                entry = entry->getNext();
            }
        }
    }

    void SymbolTable::print_LexArray()
    {
        if (lexArray == NULL)
        {
            std::cout << "NULL" << std::endl;
            return;
        }
        std::cout << "|";
        for (int i = 0; i < LEXEME_ARRAY; ++i)
        {
            if (lexArray[i] == 0)
                std::cout << "_"
                          << "|";
            else
                std::cout << lexArray[i] << "|";
            if (lexArray[i] == 0 && lexArray[i + 1] == 0)
                break;
        }
        std::cout << std::endl;
    }

    void ReservedWordTable::insert(const char *lexeme, int token)
    {
        // if lexeme exists in table, so don't do anything
        if (searchLexeme(lexeme) == NULL)
        {
            SymbolTable::insert(new ReservedWordEntry(0, token), lexeme);
        }
    }
    ReservedWordEntry *ReservedWordTable::searchLexeme(const char *lexeme)
    {
        return (ReservedWordEntry *)SymbolTable::searchLexeme(lexeme);
    }

    void IdentifierTable::insert(const char *lexeme)
    {
        // if lexeme exists in table, so don't do anything
        if (searchLexeme(lexeme) == NULL)
        {
            SymbolTable::insert(new IdentifierEntry(0, 48), lexeme);
        }
    }
    IdentifierEntry *IdentifierTable::searchLexeme(const char *lexeme)
    {
        return (IdentifierEntry *)SymbolTable::searchLexeme(lexeme);
    }

    void NumTable::insert(const char *lexeme)
    {
        // if lexeme exists in table, so don't do anything
        if (searchLexeme(lexeme) == NULL)
        {
            SymbolTable::insert(new NumEntry(0, 49), lexeme);
        }
    }
    NumEntry *NumTable::searchLexeme(const char *lexeme)
    {
        return (NumEntry *)SymbolTable::searchLexeme(lexeme);
    }

    void LiteralTable::insert(const char *lexeme)
    {
        // if lexeme exists in table, so don't do anything
        if (searchLexeme(lexeme) == NULL)
        {
            SymbolTable::insert(new LiteralEntry(0, 50), lexeme);
        }
    }
    LiteralEntry *LiteralTable::searchLexeme(const char *lexeme)
    {
        return (LiteralEntry *)SymbolTable::searchLexeme(lexeme);
    }
}