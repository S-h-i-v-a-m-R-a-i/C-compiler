#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include <memory>//for shared_ptr to handle dynamic memory for AST nodes
#include <string>
#include <vector>
using namespace std;

namespace Avengers
{
    struct ASTNode{
        string node_type;
        string value;
        vector<shared_ptr<ASTNode>> children;
        ASTNode(const string& type , const string& val = "")
        :node_type(type) , value(val){}
    };
    //class responsible for converting tokens into AST
    class Parser{
        private:
            vector<Token> tokens;
            size_t current;//index pointing to current node 
            Token peek();//return the current token without consuming it 
            Token advance();//moves current ahead and return the token
            bool match(LexicalUnit type);//this functions return true if token matches a particular type
            bool isAtEnd();//return true if parser reached at the end of file

            //these are core parsing methods (Recursive Desent) as it easy and efficient for simple grammars
            //these define rules using recursive descent parsing
            shared_ptr<ASTNode> expression();
            shared_ptr<ASTNode> term();
            shared_ptr<ASTNode> factor();

        public:
            //this is constructure to initilize the parser with a list of tokens 
            Parser(const vector<Token>& toks);
            //entry point of parser:start building the ast
            shared_ptr<ASTNode> parse();
            //function to print ast recursively 
            void printAST(const shared_ptr<ASTNode>& node, int indent = 0);
    };
}

#endif