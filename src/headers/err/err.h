//
// Created by Sid B on 18/01/26.
//

#ifndef BLSLANG_ERR_H
#define BLSLANG_ERR_H
#include <exception>
#include <string>
#include <sstream>

#include "../core/blsl.h"
#include "../log/log.h"

namespace BLSL
{
    class BLSLException : public std::exception
    {
    protected:
        std::stringstream _msg;

    public:
        explicit BLSLException(const char* msg);
        explicit BLSLException(std::string&& msg);
        BLSLException();

        virtual ~BLSLException() = default;

        virtual const char* what() const noexcept;
    };

    namespace Error
    {
        class FileNotFound : public BLSLException
        {
        public:
            explicit FileNotFound(const char* filePath);
            explicit FileNotFound(const std::string& filePath);
        };

        class UnidentifiedSequence : public BLSLException
        {
        public:
            explicit UnidentifiedSequence(DebugPosition debugPos);
        };

        class UnexpectedToken : public BLSLException
        {
        public:
            explicit UnexpectedToken(TokenType expected, Token got);
        };

        class BadToken : public BLSLException
        {
        public:
            explicit BadToken(Token got);
        };

        class BadConsume : public BLSLException
        {
        public:
            explicit BadConsume(Token got);
        };

        class MissingIf : public BLSLException
        {
        public:
            explicit MissingIf(DebugPosition debugPos);
        };

        class MissingExpression : public BLSLException
        {
        public:
            explicit MissingExpression(DebugPosition debugPos);
        };


    }
}
#endif //BLSLANG_ERR_H
