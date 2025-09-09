#include "parser.h"
#include "lexer.h"
#include <iostream>

using namespace Avengers;

void testParser(const std::string& input, bool shouldPass) {
    std::cout << "=== TESTING: '" << input << "' ===\n";
    try {
        LexicalStream lexer(input);
        auto tokens = lexer.TokenizeAll();
        Parser parser(tokens);
        auto ast = parser.parse();
        
        if (shouldPass) {
            std::cout << "✓ Test passed\n";
            std::cout << "AST:\n";
            parser.printAST(ast);
        } else {
            std::cerr << "✗ Test failed: Expected parse error but passed\n";
        }
    } catch (const std::exception& e) {
        if (shouldPass) {
            std::cerr << "✗ Test failed: " << e.what() << "\n";
        } else {
            std::cout << "✓ Correctly caught error: " << e.what() << "\n";
        }
    }
}

int main() {
    // Valid expressions
    testParser("x + y * z", true);
    
    // Invalid expressions
    testParser("x + + y", false);  // Malformed
    
    return 0;
}