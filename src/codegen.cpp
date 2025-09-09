// #include "codegen.h"
// #include <iostream>

// using namespace Avengers;

// CodeGenerator::CodeGenerator() : tempCount(0) {}

// std::string CodeGenerator::generate(const std::shared_ptr<ASTNode>& node) {
//     if (!node) return "";

//     if (node->node_type == "Literal") {
//         return node->value;
//     }

//     if (node->node_type == "BinaryOp" && node->children.size() == 2) {
//         std::string left = generate(node->children[0]);
//         std::string right = generate(node->children[1]);

//         std::string temp = "t" + std::to_string(tempCount++);
//         code.push_back(temp + " = " + left + " " + node->value + " " + right);
//         return temp;
//     }

//     return ""; // fallback
// }

// void CodeGenerator::generateCode(const std::shared_ptr<ASTNode>& root) {
//     generate(root);
// }

// void CodeGenerator::printCode() const {
//     for (const auto& line : code) {
//         std::cout << line << std::endl;
//     }
// }

#include "codegen.h"
#include <iostream>
#include <stdexcept>

using namespace Avengers;

CodeGenerator::CodeGenerator() : tempCount(0) {}

std::string CodeGenerator::generate(const std::shared_ptr<ASTNode>& node) {
    if (!node) throw std::runtime_error("Null node in code generation");

    // Handle identifiers
    if (node->node_type == "Identifier") {
        return node->value;
    }

    // Handle literals
    if (node->node_type == "Literal") {
        return node->value;
    }

    // Handle binary operations
    if (node->node_type == "BinaryOp" && node->children.size() == 2) {
        std::string left = generate(node->children[0]);
        std::string right = generate(node->children[1]);
        
        if (left.empty() || right.empty()) {
            throw std::runtime_error("Missing operands in binary operation");
        }

        std::string temp = "t" + std::to_string(tempCount++);
        code.push_back(temp + " = " + left + " " + node->value + " " + right);
        return temp;
    }

    throw std::runtime_error("Unsupported node type: " + node->node_type);
}

void CodeGenerator::generateCode(const std::shared_ptr<ASTNode>& root) {
    tempCount = 0;  // Reset counter for new generation
    code.clear();   // Clear previous code
    generate(root);
}

void CodeGenerator::printCode() const {
    for (const auto& line : code) {
        std::cout << line << std::endl;
    }
}