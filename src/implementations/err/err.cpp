//
// Created by Sid B on 23/01/26.
//

#include "../../headers/err/err.h"

BLSL::BLSLException::BLSLException(const char *msg)
    : _msg(msg)
{}

BLSL::BLSLException::BLSLException(std::string &&msg)
    : _msg(std::move(msg))
{}

BLSL::BLSLException::BLSLException()
{

}

const char * BLSL::BLSLException::what() const noexcept
{
    return _msg.str().c_str();
}

BLSL::Error::FileNotFound::FileNotFound(const char *filePath)
{
    _msg << "Unable to find file: " << filePath;
}

BLSL::Error::FileNotFound::FileNotFound(const std::string &filePath)
{
    _msg << "Unable to find file: " << filePath;
}

BLSL::Error::UnidentifiedSequence::UnidentifiedSequence(DebugPosition debugPos)
{
    _msg << "Unidentified Sequence for Lexing. \n" << debugPos;
    _msg << "\n" << debugPos;
}

BLSL::Error::UnexpectedToken::UnexpectedToken(TokenType expected, Token got)
{
    _msg << "Unexpected Token\nExpected: " << static_cast<int>(expected) << "\ngot: " << got;
    _msg << "\n" << got.debugPos;
}

BLSL::Error::BadToken::BadToken(Token got)
{
    _msg << "Bad Token: " << got << "\n" << got.debugPos;
    _msg << "\n" << got.debugPos;
}

BLSL::Error::BadConsume::BadConsume(Token got)
{
    _msg << "Failed to Consume Token\ngot: " << got;
    _msg << "\n" << got.debugPos;
}

BLSL::Error::MissingIf::MissingIf(DebugPosition debugPos)
{
    _msg << "Block: 'else' Must Have 'if' Block Preceding It.";
    _msg << "\n" << debugPos;
}

BLSL::Error::MissingExpression::MissingExpression(DebugPosition debugPos)
{
    _msg << "Expected an Expression";
    _msg << "\n" << debugPos;
}


