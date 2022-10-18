#include "SymbolTable.h"

namespace c_namespace
{
    // Constructor
    SymbolTable::SymbolTable()
    {
        lexArray_size = 0; //
        lexArray_pos = 0;  // lexeme actual pos
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

    /**
     * The Hash function uses the prime number 131, as this number is the first
     * best greater than the size of the ASCII table. Next, the collision number
     * is a big number to avoid or minimize the collisions.
     * Each character in lexeme result in a hash_value + number of the character
     * corresponding ASCII * rest, in this result the % is made with the
     * collision number, and this is the new hash_value.
     * Finally the Hash function return hash_value % table size.
     * @param lexeme
     */
    int SymbolTable::hashFuntion(std::string const &lexeme)
    {
        int prime = 131;
        long collision = 1e9 + 9;

        long long hash_value = 0;
        long long rest = 1;

        for (char c : lexeme)
        {
            hash_value = (hash_value + (c - 'a' + 1) * rest) % collision;
            rest = (rest * prime) % collision;
        }
        return (unsigned int)hash_value % TABLE_SIZE;
    };

    /**
     * The insertion function use a new empty value of TableEntry and the lexeme,
     * if lexeme different of NULL then insert can be done.
     * The values of TableEntry is set and SymbolTable receive the entry.
     * Next, lexeme array receive the lexeme in next empty position.
     * @param entry
     * @param lexeme
     */
    void SymbolTable::insert(TableEntry *entry, const char *lexeme)
    {
        if (lexeme != NULL)
        {
            int lexemeSize = strlen(lexeme);

            int index = hashFuntion(lexeme);

            entry->setNext(table[index]);

            table[index] = entry;

            if (lexArray_size <= (lexArray_pos + lexemeSize))
            {
                while (lexArray_size <= (lexArray_pos + lexemeSize))
                {
                    lexArray_size += LEXEME_ARRAY;
                }
                lexArray = (char *)realloc(lexArray, lexArray_size * sizeof(char));
            }

            strcpy(lexArray + lexArray_pos, lexeme);

            entry->setLexIndex(lexArray_pos);

            lexArray_pos = lexArray_pos + ((int)lexemeSize + 1);
        }
    }

    /**
     * To search lexeme is created a TableEntry to receive SymbolTable in hash
     * result position, while TableEntry is different to NULL check if the lexemes
     * are equal to return that lexeme exists, skip to the next lexeme and check
     * successively, if not found return NULL.
     * @param lexeme
     */
    TableEntry *SymbolTable::searchLexeme(const char *lexeme)
    {
        if (lexeme != NULL)
        {
            int index = hashFuntion(lexeme);

            TableEntry *entry = table[index];

            while (entry != NULL)
            {
                if(strcmp((lexArray + entry->getLexIndex()), lexeme)==0)
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

            if (entry != NULL)
            {
                int index = entry->getLexIndex();

                int lexemeSize = 0;

                for (int j = 0; j < 20; j++)
                {
                    if (lexArray[index + j] == 0)
                        break;
                    lexemeSize = j;
                }

                if (entry->getToken() == 48 || entry->getToken() == 49 || entry->getToken() == 50)
                    std::cout << lexArray + entry->getLexIndex() << std::endl;
                else
                    std::cout << lexArray + entry->getLexIndex() << std::string((25 - lexemeSize), ' ') << entry->getToken() << std::endl;

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

    /**
     * In the inherited class from SymbolTable use search to check if it can insert.
     * If NULL call insert function of SymbolTable with params new TableEntry and
     * lexeme.
     * @param lexeme
     * @param token
     */
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

    /**
     * In the inherited class from SymbolTable use search to check if it can insert.
     * If NULL call insert function of SymbolTable with params new TableEntry and
     * lexeme.
     * In this case TableEntry the token param is fixed in ID = 48, because at all ids have
     * same token.
     * @param lexeme
     */
    void IdentifierTable::insert(const char *lexeme)
    {
        // if lexeme exists in table, so don't do anything
        if (searchLexeme(lexeme) == NULL)
        {
            SymbolTable::insert(new IdentifierEntry(0, ID), lexeme);
        }
    }
    IdentifierEntry *IdentifierTable::searchLexeme(const char *lexeme)
    {
        return (IdentifierEntry *)SymbolTable::searchLexeme(lexeme);
    }

    void LiteralTable::insert(const char *lexeme, int token)
    {
        // if lexeme exists in table, so don't do anything
        if (searchLexeme(lexeme) == NULL)
        {
            SymbolTable::insert(new LiteralEntry(0, token), lexeme);
        }
    }
    LiteralEntry *LiteralTable::searchLexeme(const char *lexeme)
    {
        return (LiteralEntry *)SymbolTable::searchLexeme(lexeme);
    }
}