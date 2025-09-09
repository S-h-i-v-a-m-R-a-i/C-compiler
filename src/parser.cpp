//in this parser.cpp we implement a recursive decendent parser that built a AST
#include "../include/parser.h"
#include <iostream>

using namespace std;
using namespace Avengers;

Parser::Parser(const vector<Token>& toks) : tokens(toks), current(0) {}

Token Parser::peek(){
    if (isAtEnd()) {
        return {LexicalUnit::end_of_file, "", 0, 0};
    }
    return tokens[current];
}

Token Parser::advance(){
    if (!isAtEnd()) current++;
    return peek();
}

bool Parser::match(LexicalUnit type){
    if (!isAtEnd() && peek().kind == type) {
        advance();
        return true;
    }
    return false;
}

bool Parser::isAtEnd(){
    return static_cast<size_t>(current) >= tokens.size() || tokens[current].kind == LexicalUnit::end_of_file;
}

shared_ptr<ASTNode> Parser::parse(){
    return expression();
}


shared_ptr<ASTNode> Parser::expression(){
    auto node = term();
    while (!isAtEnd() && (peek().lexeme == "+" || peek().lexeme == "-")) {
        string op = peek().lexeme;
        advance();
        auto right = term();
        auto parent = make_shared<ASTNode>("BinaryOp", op);
        parent->children.push_back(node);
        parent->children.push_back(right);
        node = parent;
    }
    return node;
}

shared_ptr<ASTNode> Parser::term(){
    auto node = factor();
    while (!isAtEnd() && (peek().lexeme == "*" || peek().lexeme == "/")){
        string op = peek().lexeme;
        advance();
        auto right = factor();
        auto parent = make_shared<ASTNode>("BinaryOp", op);
        parent->children.push_back(node);
        parent->children.push_back(right);
        node = parent;
    }
    return node;
}

// shared_ptr<ASTNode> Parser::factor(){
//     Token tok = peek();

//     if (tok.kind == LexicalUnit::identifier) {
//         advance();
//         return make_shared<ASTNode>("Identifier", tok.lexeme);
//     }
    
//     if (tok.kind == LexicalUnit::integer_literal || tok.kind == LexicalUnit::float_literal) {
//         advance();
//         return make_shared<ASTNode>("Literal", tok.lexeme);
//     }

//     if (tok.lexeme == "("){
//         advance();
//         auto expr = expression();
//         if (peek().lexeme == ")"){
//             advance(); // consume ')'
//         } else{
//             cerr << "Error: Expected ')' after expression\n";
//         }
//         return expr;
//     }

//     cerr << "Error: Unexpected token'" << tok.lexeme << "'at line" << tok.line << ", column " << tok.column << "\n";
//     advance();
//     return make_shared<ASTNode>("Error");
// }

shared_ptr<ASTNode> Parser::factor(){
    Token tok = peek();

    if (tok.kind == LexicalUnit::identifier) {
        advance();
        return make_shared<ASTNode>("Identifier", tok.lexeme);
    }

    if (tok.kind == LexicalUnit::integer_literal || tok.kind == LexicalUnit::float_literal) {
        advance();
        return make_shared<ASTNode>("Literal", tok.lexeme);
    }

    if (tok.lexeme == "("){
        advance();
        auto expr = expression();
        if (peek().lexeme == ")"){
            advance(); // consume ')'
        } else{
            cerr << "Error: Expected ')' after expression\n";
        }
        return expr;
    }

    cerr << "Error: Unexpected token '" << tok.lexeme << "' at line " << tok.line << ", column " << tok.column << "\n";
    advance();
    return make_shared<ASTNode>("Error");
}

void Parser::printAST(const shared_ptr<ASTNode>& node, int indent){
    if (!node) return;
    for (int i = 0; i < indent; ++i) cout << "  ";
    cout << node->node_type;
    if (!node->value.empty()) cout << ": " << node->value;
    cout << endl;
    for (const auto& child : node->children) {
        printAST(child, indent + 1);
    }
}