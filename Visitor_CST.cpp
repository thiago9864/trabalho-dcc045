#include "Visitor_CST.h"
#include "LexicalAnalyzer.h"

PrintCST::PrintCST() {
    this->level = 0;
}

void PrintCST::printIR(const char *node_name) {
    for (unsigned int i = 0; i < this->level; i++)
        std::cout << "|    ";
    std::cout << "->" << node_name << std::endl;
}

void PrintCST::printLexemeIR(const char *node_name, const char *aux) {
    for (unsigned int i = 0; i < this->level; i++)
        std::cout << "|    ";
    std::cout << "->" << node_name << "." << aux << std::endl;
}

void PrintCST::up_level() {
    this->level++;
}

void PrintCST::down_level() {
    this->level--;

}