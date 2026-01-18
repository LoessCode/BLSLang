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

        bool _match_punctuator(PunctuatorType pType) const;
        bool _match_keyword(KeywordType kType) const;

        void _consume_punctuator(PunctuatorType pType);
        void _consume_keyword(KeywordType kType);

    private:

        Node_t _parse_for();
        Node_t _parse_while();
        Node_t _parse_if();
        Node_t _parse_else();

        Node_t _parse_func();

        Node_t _parse_expression(int lowestPrecedence = -1);
        BodyNode_t _parse_block();
        Node_t _parse_statement();


    public:
        explicit Parser(std::unique_ptr<std::vector<Token>> in);

        Node_t parse();
    };
}

#endif //BLSLANG_PARSER_H