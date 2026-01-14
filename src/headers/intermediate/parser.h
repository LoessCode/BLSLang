//
// Created by Sid B on 06/01/26.
//

#ifndef BLSLANG_PARSER_H
#define BLSLANG_PARSER_H

#include <expected>

#include "astnodes.h"

namespace BLSL
{
    class Parser
    {
        private:
            std::unique_ptr<std::vector<Token>> _tokens;
            size_t _pos;

        private:
            Token _peek() const;
            Token _next();


            std::expected<OperatorType, Token> _peek_operator() const;
            std::expected<Node_t, Token> _get_atom();
            std::expected<std::unique_ptr<ASTNode::BinaryOperator>, Token> _get_operator();

        private:
            Node_t _parse_expression(int lowestPrecedence = -1);


        public:
            Parser(std::unique_ptr<std::vector<Token>> in);

            Node_t parse();
    };
}

#endif //BLSLANG_PARSER_H