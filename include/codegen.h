#ifndef CODEGEN_H
#define CODEGEN_H

#include "parser.h"
#include <string>
#include <vector>
#include <memory>

namespace Avengers {

class CodeGenerator {
private:
    int tempCount;
    std::vector<std::string> code;

    std::string generate(const std::shared_ptr<ASTNode>& node);

public:
    virtual ~CodeGenerator() = default; 
    CodeGenerator();
    void generateCode(const std::shared_ptr<ASTNode>& root);
    void printCode() const;
};

} // namespace Avengers

#endif