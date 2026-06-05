#pragma once

#include <stdexcept>
#include <string>

#include "source_location.hpp"

namespace riven
{

class CompilerError
    : public std::runtime_error
{
public:
    CompilerError(
        const std::string& message,
        SourceLocation location
    )
        : std::runtime_error(message),
          m_location(location)
    {
    }

    [[nodiscard]]
    SourceLocation location() const
    {
        return m_location;
    }

private:
    SourceLocation m_location;
};

class LexerError
    : public CompilerError
{
public:
    LexerError(
        const std::string& message,
        SourceLocation location
    )
        : CompilerError(
            message,
            location
        )
    {
    }
};

class ParserError
    : public CompilerError
{
public:
    ParserError(
        const std::string& message,
        SourceLocation location
    )
        : CompilerError(
            message,
            location
        )
    {
    }
};

class SemanticError
    : public CompilerError
{
public:
    SemanticError(
        const std::string& message,
        SourceLocation location
    )
        : CompilerError(
            message,
            location
        )
    {
    }
};

}
