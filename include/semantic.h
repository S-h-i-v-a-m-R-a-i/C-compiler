// semantic.h
#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "parser.h"
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <memory>
#include <vector>

namespace Avengers {

class SymbolTable {
private:
    std::unordered_map<std::string, bool> table;
    std::vector<std::string> declarationOrder;
public:
    void declare(const std::string& name);
    bool isDeclared(const std::string& name) const;
    void print() const;
};

class SemanticAnalyzer {
private:
    SymbolTable symbols;
    void analyzeNode(const std::shared_ptr<ASTNode>& node);
public:
    SymbolTable& getSymbolTable() { return symbols; }
    void analyze(const std::shared_ptr<ASTNode>& root);
    void printSymbolTable() const { symbols.print(); }
};

} // namespace Avengers

#endif // SEMANTIC_H