//
// Created by Sid B on 06/01/26.
//

#include "../../headers/core/blsbyc.h"
#include "../../headers/core/blsl.h"

namespace BLSL
{
    const LexemeTable_t LEXEME_TABLE = {
        {TokenType::OPERATOR, {
            {"+", OperatorType::ADD},
            {"-", OperatorType::SUB},
            {"*", OperatorType::MUL},
            {"/", OperatorType::DIV},
            {"^", OperatorType::POW},
            {"&", OperatorType::BW_AND},
            {"|", OperatorType::BW_OR},
            {"<<", OperatorType::BW_LSHIFT},
            {">>", OperatorType::BW_RSHIFT},
            {"~", OperatorType::BW_NOT},
            {"^", OperatorType::BW_XOR}
        }},
        {TokenType::COMPARATOR, {
            {"&&", ComparatorType::AND},
            {"!", ComparatorType::NOT},
            {"||", ComparatorType::OR},
            {">", ComparatorType::GREATER},
            {"<", ComparatorType::LESSER},
            {"==", ComparatorType::EQUAL}
        }},
        {TokenType::PUNCTUATOR, {
            {",", PunctuatorType::COMMA},
            {";", PunctuatorType::SEMICOLON},
            {":", PunctuatorType::COLON},
            {"(", PunctuatorType::LPAREN},
            {")", PunctuatorType::RPAREN},
            {"[", PunctuatorType::LSQUARE},
            {"]", PunctuatorType::RSQUARE},
            {"{", PunctuatorType::LBRACE},
            {"}", PunctuatorType::RBRACE}
        }},
        {TokenType::KEYWORD, {
            {"meminit", KeywordType::MEMINIT},
            {"alloc", KeywordType::ALLOC},
            {"func", KeywordType::FUNC},
            {"for", KeywordType::FOR},
            {"while", KeywordType::WHILE},
            {"if", KeywordType::IF},
            {"else", KeywordType::ELSE}
        }}
    };

    const std::unordered_map<OperatorType, std::pair<int, int>> OPERATOR_PRECEDENCE = {
        {OperatorType::POW, {220, 222}},
        {OperatorType::MUL, {210, 212}},
        {OperatorType::DIV, {210, 212}},
        {OperatorType::ADD, {200, 202}},
        {OperatorType::SUB, {200, 202}},

        {OperatorType::BW_LSHIFT, {130, 132}},
        {OperatorType::BW_RSHIFT, {130, 132}},
        {OperatorType::BW_NOT, {120, 122}},
        {OperatorType::BW_AND, {110, 112}},
        {OperatorType::BW_OR, {100, 102}},
    };

    const std::unordered_map<ComparatorType, std::pair<int, int>> COMPARATOR_PRECEDENCE = {
        {ComparatorType::LESSER, {50, 52}},
        {ComparatorType::GREATER, {50, 52}},
        {ComparatorType::EQUAL, {40, 42}},
        {ComparatorType::NOT, {30, 32}},
        {ComparatorType::AND, {20, 22}},
        {ComparatorType::OR, {10, 12}}
    };



}