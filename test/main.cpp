#include <iostream>
#include <memory>
#include "lexer.h"
#include "parser.h"
#include "semantic.h"
#include "codegen.h"

using namespace Avengers;

std::string tokenTypeToString(LexicalUnit type) {
    switch(type) {
        case LexicalUnit::identifier: return "Identifier";
        case LexicalUnit::keyword: return "Keyword";
        case LexicalUnit::integer_literal: return "Integer Literal";
        case LexicalUnit::float_literal: return "Float Literal";
        case LexicalUnit::Operator: return "Operator";
        case LexicalUnit::delimiter: return "Delimiter";
        case LexicalUnit::string_literal: return "String Literal";
        case LexicalUnit::char_literal: return "Char Literal";
        case LexicalUnit::end_of_file: return "EOF";
        default: return "Unknown";
    }
}

int main() {
    std::string input = "x + y * z - e / f * o - v";  
    
    // 1. Lexical Analysis
    LexicalStream lexer(input);
    std::vector<Token> tokens = lexer.TokenizeAll();
    
    // Print tokens in BOTH formats
    std::cout << "Tokens (Both Representations):\n";
    for (const auto& token : tokens) {
        std::cout << "[" << token.lexeme << " (" << static_cast<int>(token.kind) << ")] "
                  << "=> " << token.lexeme << " (" << tokenTypeToString(token.kind) << ")\n";
    }
    std::cout << "\n";
    
    // [Rest of your existing code...]
    // 2. Parsing
    Parser parser(tokens);
    std::shared_ptr<ASTNode> ast = parser.parse();
    
    std::cout << "AST Structure:\n";
    parser.printAST(ast);
    std::cout << "\n";
    
    // 3. Semantic Analysis
    SemanticAnalyzer semantic;
    
    std::cout << "=== SEMANTIC ANALYSIS ===\n";
    std::cout << "Initial Symbol Table:\n";
    semantic.printSymbolTable();

    std::cout << "\n=== VARIABLE DECLARATIONS ===\n";
    auto& symtable = semantic.getSymbolTable();
    symtable.declare("x");
    symtable.declare("y");
    symtable.declare("z");
    symtable.declare("e");
    symtable.declare("f"); 
    symtable.declare("o");
    symtable.declare("v");

    std::cout << "\nFinal Symbol Table:\n";
    semantic.printSymbolTable();

    try {
        std::cout << "\nAnalyzing AST...\n";
        semantic.analyze(ast);
        std::cout << "Semantic analysis passed.\n";
        
        // Test undeclared variable
        std::cout << "\nTesting Undeclared Variable Detection:\n";
        std::shared_ptr<ASTNode> testNode = std::make_shared<ASTNode>("Identifier", "undeclaredVar");
        try {
            semantic.analyze(testNode);
        } catch (const std::exception& e) {
            std::cout << "✓ " << e.what() << "\n";
        }
        
    } catch (const std::exception& e) {
        std::cerr << "Semantic error: " << e.what() << std::endl;
        return 1;
    }
    
    // 4. Code Generation
    CodeGenerator codegen;
    codegen.generateCode(ast);
    
    std::cout << "Generated Three Address Code:\n";
    codegen.printCode();
    
    return 0;
}