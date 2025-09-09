#include "lexer.h"
#include <iostream>

using namespace Avengers;

void testLexer(const std::string& input, const std::vector<std::pair<std::string, LexicalUnit>>& expected) {
    std::cout << "=== TESTING: '" << input << "' ===\n";
    LexicalStream lexer(input);
    auto tokens = lexer.TokenizeAll();
    
    bool passed = true;
    for (size_t i = 0; i < std::min(tokens.size(), expected.size()); i++) {
        if (tokens[i].lexeme != expected[i].first || tokens[i].kind != expected[i].second) {
            std::cerr << "✗ Token mismatch at position " << i 
                      << ": Expected '" << expected[i].first << "' (" 
                      << static_cast<int>(expected[i].second) << "), got '"
                      << tokens[i].lexeme << "' (" << static_cast<int>(tokens[i].kind) << ")\n";
            passed = false;
        }
    }
    
    if (passed && tokens.size() == expected.size()) {
        std::cout << "✓ Test passed\n";
    } else {
        std::cerr << "✗ Test failed\n";
    }
}

int main() {
    // Valid tokens
    testLexer("x + y", {
        {"x", LexicalUnit::identifier},
        {"+", LexicalUnit::Operator},
        {"y", LexicalUnit::identifier}
    });
    
    // Invalid token
    testLexer("123abc", {
        {"123", LexicalUnit::integer_literal}  // Should fail on "abc"
    });
    
    return 0;
}