#include <iostream>
#include <memory>
#include "lexer.h"
#include "parser.h"
#include "semantic.h"
#include "codegen.h"

using namespace Avengers;

void testExpression(const std::string& input, bool shouldPass) {
    std::cout << "\n=== **********-SEMANTIC TEST-**********8 '" << input << "' ===\n";
    std::cout << "\n=== TESTING: '" << input << "' ===\n";
    
    try {
        // 1. Lexical Analysis
        LexicalStream lexer(input);
        auto tokens = lexer.TokenizeAll();
        
        // 2. Parsing
        Parser parser(tokens);
        auto ast = parser.parse();
        
        // 3. Semantic Analysis
        SemanticAnalyzer semantic;
        
        // Declare only x,y,z for testing
        if (input.find("x") != std::string::npos) semantic.getSymbolTable().declare("x");
        if (input.find("y") != std::string::npos) semantic.getSymbolTable().declare("y");
        if (input.find("z") != std::string::npos) semantic.getSymbolTable().declare("z");
        
        semantic.analyze(ast);
        
        if (!shouldPass) {
            std::cerr << "TEST FAILED: Expected semantic error but passed\n";
            return;
        }
        
        // 4. Code Generation
        CodeGenerator codegen;
        codegen.generateCode(ast);
        
        std::cout << "Generated Code:\n";
        codegen.printCode();
        std::cout << "TEST PASSED\n";
        
    } catch (const std::exception& e) {
        if (shouldPass) {
            std::cerr << "TEST FAILED: " << e.what() << "\n";
        } else {
            std::cout << "✓ Correctly caught semantic error: " << e.what() << "\n";
            std::cout << "TEST PASSED\n";
        }
    }
}

int main() {
    // Valid expressions (should pass)
    testExpression("x + y * z", true);
    
    // Invalid expressions (should fail)
    testExpression("a + b * c", false);  // Undeclared vars
    testExpression("x + x", false);      // Duplicate var (if your semantics prohibit this)
    testExpression("1 + true", false);   // Type mismatch (when you implement types)
    
    return 0;
}