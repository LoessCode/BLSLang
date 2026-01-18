//
// Created by Sid B on 06/01/26.
//

#include "../../headers/intermediate/parser.h"

#include <print>

BLSL::Token BLSL::Parser::_peek() const
{
    if (_pos != _tokens->size())
    {
        return _tokens->at(_pos);
    }

    return _tokens->back();
}

BLSL::Token BLSL::Parser::_next()
{
    if (_pos != _tokens->size())
    {
        return _tokens->at(_pos++);
    }

    return _tokens->back();
}

std::expected<BLSL::OperatorType, BLSL::Token> BLSL::Parser::_peek_operator() const
{
    auto token = _peek();
    if (token.type == TokenType::OPERATOR)
    {
        return std::get<OperatorType>(token.subType);
    }

    return std::unexpected(token);
}

std::expected<BLSL::Node_t, BLSL::Token> BLSL::Parser::_get_atom()
{
    if (_peek().type == TokenType::LITERAL)
    {
        Token token = _next();
        ASTNode::Literal literal;
        literal.debugPos = token.debugPos;
        literal.value = token.value.value();
        literal.type = std::get<LiteralType>(token.subType);

        return std::make_unique<ASTNode::Literal>(literal);
    }

    if (_peek().type == TokenType::IDENTIFIER)
    {
        Token token = _next();
        ASTNode::Variable variable;
        variable.debugPos = token.debugPos;
        variable.identifier = token.value.value();

        return std::make_unique<ASTNode::Variable>(variable);
    }

    return std::unexpected(_peek());
}

std::expected<std::unique_ptr<BLSL::ASTNode::BinaryOperator>, BLSL::Token> BLSL::Parser::_get_operator()
{
    if (_peek().type == TokenType::OPERATOR)
    {
        Token token = _next();
        ASTNode::BinaryOperator op;
        op.debugPos = token.debugPos;
        op.type = std::get<OperatorType>(token.subType);

        return std::make_unique<ASTNode::BinaryOperator>(std::move(op));
    }
}

bool BLSL::Parser::_match_punctuator(PunctuatorType pType) const
{
    if (_peek().type == TokenType::PUNCTUATOR)
    {
        if (std::get<PunctuatorType>(_peek().subType) == pType)
        {
            return true;
        }
        return false;
    }
    return false;
}

bool BLSL::Parser::_match_keyword(KeywordType kType) const
{
    if (_peek().type == TokenType::KEYWORD)
    {
        if (std::get<KeywordType>(_peek().subType) == kType)
        {
            return true;
        }
        return false;
    }
    return false;
}

void BLSL::Parser::_consume_punctuator(PunctuatorType pType)
{
    if (_peek().type == TokenType::PUNCTUATOR)
    {

        Token token = _next();
        if (std::get<PunctuatorType>(token.subType) != pType)
        {
            //TODO: THrow
            throw;
        }
    }
    else
    {
        //TODO: THrow
        throw;
    }
}

void BLSL::Parser::_consume_keyword(KeywordType kType)
{
    if (_peek().type == TokenType::KEYWORD)
    {
        Token token = _next();
        if (std::get<KeywordType>(token.subType) != kType)
        {
            //TODO: THROW
            throw;
        }
    }
    else
    {
        //TODO: THrow
        throw;
    }
}

BLSL::Node_t BLSL::Parser::_parse_for() {}
BLSL::Node_t BLSL::Parser::_parse_while() {}


BLSL::Node_t BLSL::Parser::_parse_if()
{
    ASTNode::If ifNode;

    _consume_punctuator(PunctuatorType::LPAREN);

    ifNode.condition = _parse_expression();

    _consume_punctuator(PunctuatorType::RPAREN);

    ifNode.body = _parse_statement();

    if (_match_keyword(KeywordType::ELSE))
    {
        _consume_keyword(KeywordType::ELSE);
        ifNode.elseBranch = _parse_statement();

    }
    else
    {
        ifNode.elseBranch = std::nullopt;
    }

    return std::make_unique<ASTNode::If>(std::move(ifNode));
}

BLSL::Node_t BLSL::Parser::_parse_else() {}
BLSL::Node_t BLSL::Parser::_parse_func() {}

BLSL::Node_t BLSL::Parser::_parse_expression(int lowestPrecedence)
{
    Node_t LHS;

    if (_peek().type == TokenType::PUNCTUATOR)
    {
        if (std::get<PunctuatorType>(_peek().subType) == PunctuatorType::LPAREN)
        {
            _next();

            LHS = _parse_expression();

            _consume_punctuator(PunctuatorType::RPAREN);
        }
        else
        {
            throw;
        }
    }
    else if (_peek().type == TokenType::OPERATOR)
    {
        if (PREFIX_PRECEDENCE.contains(std::get<OperatorType>(_peek().subType)))
        {
            auto token = _next();
            ASTNode::UnaryOperator unaryOperator;
            unaryOperator.debugPos = token.debugPos;
            unaryOperator.type = std::get<OperatorType>(token.subType);

            unaryOperator.right = _parse_expression(PREFIX_PRECEDENCE.at(std::get<OperatorType>(token.subType)));

            return std::make_unique<ASTNode::UnaryOperator>(std::move(unaryOperator));
        }
    }
    else
    {
        auto LHSExpected = _get_atom();
        if (!LHSExpected.has_value())
        {
            //TODO: Errors. std::print("{}", LHSExpected.error());
            throw;
        }

        LHS = std::move(LHSExpected.value());
    }



    while (true)
    {
        if (_peek().type == TokenType::PUNCTUATOR)
        {
            if (std::get<PunctuatorType>(_peek().subType) == PunctuatorType::RPAREN)
            {
                break;
            }
        }

        auto opExpected = _peek_operator();
        if (!opExpected.has_value()) break;

        auto [leftPrecedence, rightPrecedence] = OPERATOR_PRECEDENCE.at(opExpected.value());
        if (leftPrecedence < lowestPrecedence) break;

        auto op = _get_operator().value();

        auto RHS = _parse_expression(rightPrecedence);

        op->left = std::move(LHS);
        op->right = std::move(RHS);

        LHS = std::move(op);

    }

    return std::move(LHS);
}

BLSL::BodyNode_t BLSL::Parser::_parse_block()
{
    _consume_punctuator(PunctuatorType::LBRACE);
    ASTNode::BodyNode bodyNode;

    while (!_match_punctuator(PunctuatorType::RBRACE))
    {
        bodyNode.nodes.emplace_back(_parse_expression());
    }

    _consume_punctuator(PunctuatorType::RBRACE);

    return std::make_unique<ASTNode::BodyNode>(std::move(bodyNode));
}

BLSL::Node_t BLSL::Parser::_parse_statement()
{
    if (_match_punctuator(PunctuatorType::LBRACE))
    {
        BodyNode_t block = _parse_block();
        return block;
    }

    switch (_peek().type)
    {
        case TokenType::KEYWORD:
            switch (std::get<KeywordType>(_peek().subType))
            {
            case KeywordType::FOR:
                _next();
                return _parse_for();

            case KeywordType::WHILE:
                _next();
                return _parse_while();

            case KeywordType::IF:
                _next();
                return _parse_if();

            case KeywordType::ELSE:
                _next();
                return _parse_else();

            case KeywordType::FUNC:
                _next();
                return _parse_func();
            }

        default:
            throw;
            //TODO: Throw
    }
}

BLSL::Parser::Parser(std::unique_ptr<std::vector<Token>> in)
    : _tokens(std::move(in)), _pos(0)
{

}

BLSL::Node_t BLSL::Parser::parse()
{
    ASTNode::BodyNode bodyNode;

    while (_pos < _tokens->size())
    {
        //_parse_statement();
        bodyNode.nodes.emplace_back(_parse_statement());
    }

    return std::make_unique<ASTNode::BodyNode>(std::move(bodyNode));

}
