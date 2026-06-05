#pragma once

#include <string>
#include <vector>

#include "../common/token.hpp"

namespace riven
{

class Lexer
{
public:
    explicit Lexer(const std::string& source);

    std::vector<Token> tokenize();

private:
    std::string m_source;

    std::size_t m_position = 0;
    std::size_t m_line = 1;
    std::size_t m_column = 1;

private:
    bool isAtEnd() const;

    char peek() const;
    char peekNext() const;

    char advance();

    void skipWhitespace();

    Token identifier();
    Token number();
    Token string();

    Token makeToken(
        TokenType type,
        const std::string& lexeme,
        SourceLocation location
    );

    TokenType keywordType(
        const std::string& text
    ) const;
};

}
