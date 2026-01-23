//
// Created by Sid B on 06/01/26.
//

#ifndef BLSLANG_LEXER_H
#define BLSLANG_LEXER_H

#include "../core/blsl.h"
#include "../err/err.h"
#include <fstream>
#include <functional>

namespace BLSL
{

    class Lexer;
    using SubLexer_t = std::optional<Token> (Lexer::*)();


    class Lexer
    {
    private:
        std::string _source;
        size_t _carat;
        DebugPosition _debugPos;
    private:
        void _step(size_t n = 1);
        void _newline();

    private:
        const std::vector<SubLexer_t> _SUB_LEXERS;

        std::optional<Token> _lex_empty();
        std::optional<Token> _lex_long_operator();
        std::optional<Token> _lex_string();
        std::optional<Token> _lex_number();
        std::optional<Token> _lex_keyword_identifier();
        std::optional<Token> _lex_single_operator();


    public:
        Lexer();
        ~Lexer() = default;

        void mount_source_from_file(const std::string& path);
        void mount_source_from_string(std::string&& source);

        std::unique_ptr<std::vector<Token>> lex();
        void lex_to_file(const std::string& path);
    };
}


#endif //BLSLANG_LEXER_H