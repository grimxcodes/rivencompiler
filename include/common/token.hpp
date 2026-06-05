#pragma once

#include <string>

#include "token_type.hpp"
#include "source_location.hpp"

namespace riven
{

struct Token
{
    TokenType type;

    std::string lexeme;

    SourceLocation location;

    Token(
        TokenType tokenType,
        std::string text,
        SourceLocation sourceLocation
    )
        : type(tokenType),
          lexeme(std::move(text)),
          location(sourceLocation)
    {
    }
};

}
