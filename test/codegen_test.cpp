#include "codegen.h"
#include "parser.h"
#include "lexer.h"
#include <iostream>

using namespace Avengers;

void testCodegen(const std::string& input, const std::vector<std::string>& expected) {
    std::cout << "=== TESTING: '" << input << "' ===\n";
    try {
        LexicalStream lexer(input);
        auto tokens = lexer.TokenizeAll();
        Parser parser(tokens);
        auto ast = parser.parse();
        
        CodeGenerator codegen;
        codegen.generateCode(ast);
        
        auto generated = codegen.getGeneratedCode();
        bool passed = true;
        
        for (size_t i = 0; i < std::min(generated.size(), expected.size()); i++) {
            if (generated[i] != expected[i]) {
                std::cerr << "✗ Line " << i+1 << " mismatch:\n"
                          << "  Expected: " << expected[i] << "\n"
                          << "  Got:      " << generated[i] << "\n";
                passed = false;
            }
        }
        
        if (passed && generated.size() == expected.size()) {
            std::cout << "✓ Test passed\n";
        } else {
            std::cerr << "✗ Test failed\n";
        }
        
    } catch (const std::exception& e) {
        std::cerr << "✗ Test failed: " << e.what() << "\n";
    }
}

int main() {
    testCodegen("x + y * z", {
        "t0 = y * z",
        "t1 = x + t0"
    });
    
    return 0;
}