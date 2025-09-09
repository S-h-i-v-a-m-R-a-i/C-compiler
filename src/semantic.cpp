// semantic.cpp
#include "semantic.h"
#include <iostream>

namespace Avengers {

void SymbolTable::declare(const std::string& name) {
    if (isDeclared(name)) {
        throw std::runtime_error("Redeclaration of variable: " + name);
    }
    table[name] = true;
    declarationOrder.push_back(name);
    std::cout << "  [DECLARED] " << name << "\n";
}

bool SymbolTable::isDeclared(const std::string& name) const {
    return table.find(name) != table.end();
}

void SymbolTable::print() const {
    std::cout << "  Symbol Table Contents:\n";
    if (declarationOrder.empty()) {
        std::cout << "  [Empty]\n";
    } else {
        for (const auto& name : declarationOrder) {
            std::cout << "  • " << name << "\n";
        }
    }
}

void SemanticAnalyzer::analyzeNode(const std::shared_ptr<ASTNode>& node) {
    if (!node) return;
    
    if (node->node_type == "Identifier") {
        if (!symbols.isDeclared(node->value)) {
            throw std::runtime_error("Undeclared variable: " + node->value);
        }
    }
    
    for (const auto& child : node->children) {
        analyzeNode(child);
    }
}

void SemanticAnalyzer::analyze(const std::shared_ptr<ASTNode>& root) {
    analyzeNode(root);
}

} // namespace Avengers