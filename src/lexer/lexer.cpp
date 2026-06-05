#include "../../include/lexer/lexer.hpp"

#include <cctype>

#include "../../include/common/error.hpp"

namespace riven
{

Lexer::Lexer(
    const std::string& source
)
    : m_source(source)
{
}

std::vector<Token> Lexer::tokenize()
{
    std::vector<Token> tokens;

    while (!isAtEnd())
    {
        skipWhitespace();

        if (isAtEnd())
        {
            break;
        }

        SourceLocation location(
            m_line,
            m_column
        );

        char c = peek();

        if (std::isalpha(c) || c == '_')
        {
            tokens.push_back(
                identifier()
            );
            continue;
        }

        if (std::isdigit(c))
        {
            tokens.push_back(
                number()
            );
            continue;
        }

        switch (c)
        {
            case '"':
                tokens.push_back(
                    string()
                );
                break;

            case '(':
                advance();
                tokens.emplace_back(
                    TokenType::LeftParen,
                    "(",
                    location
                );
                break;

            case ')':
                advance();
                tokens.emplace_back(
                    TokenType::RightParen,
                    ")",
                    location
                );
                break;

            case '{':
                advance();
                tokens.emplace_back(
                    TokenType::LeftBrace,
                    "{",
                    location
                );
                break;

            case '}':
                advance();
                tokens.emplace_back(
                    TokenType::RightBrace,
                    "}",
                    location
                );
                break;

            case '[':
                advance();
                tokens.emplace_back(
                    TokenType::LeftBracket,
                    "[",
                    location
                );
                break;

            case ']':
                advance();
                tokens.emplace_back(
                    TokenType::RightBracket,
                    "]",
                    location
                );
                break;

            case ',':
                advance();
                tokens.emplace_back(
                    TokenType::Comma,
                    ",",
                    location
                );
                break;

            case ';':
                advance();
                tokens.emplace_back(
                    TokenType::Semicolon,
                    ";",
                    location
                );
                break;

            case '.':
                advance();
                tokens.emplace_back(
                    TokenType::Dot,
                    ".",
                    location
                );
                break;

            case '+':
                advance();

                if (peek() == '>')
                {
                    advance();

                    tokens.emplace_back(
                        TokenType::Increment,
                        "+>",
                        location
                    );
                }
                else
                {
                    tokens.emplace_back(
                        TokenType::Plus,
                        "+",
                        location
                    );
                }

                break;

            case '-':
                advance();

                if (peek() == '<')
                {
                    advance();

                    tokens.emplace_back(
                        TokenType::Decrement,
                        "-<",
                        location
                    );
                }
                else
                {
                    tokens.emplace_back(
                        TokenType::Minus,
                        "-",
                        location
                    );
                }

                break;

            case '*':
                advance();

                tokens.emplace_back(
                    TokenType::Star,
                    "*",
                    location
                );
                break;

            case '/':
                advance();

                tokens.emplace_back(
                    TokenType::Slash,
                    "/",
                    location
                );
                break;

            case '=':
                advance();

                if (peek() == '=')
                {
                    advance();

                    tokens.emplace_back(
                        TokenType::Equal,
                        "==",
                        location
                    );
                }
                else
                {
                    tokens.emplace_back(
                        TokenType::Assign,
                        "=",
                        location
                    );
                }

                break;

            case '!':
                advance();

                if (peek() == '=')
                {
                    advance();

                    tokens.emplace_back(
                        TokenType::NotEqual,
                        "!=",
                        location
                    );
                }
                else
                {
                    tokens.emplace_back(
                        TokenType::Not,
                        "!",
                        location
                    );
                }

                break;

            case '>':
                advance();

                if (peek() == '=')
                {
                    advance();

                    tokens.emplace_back(
                        TokenType::GreaterEqual,
                        ">=",
                        location
                    );
                }
                else
                {
                    tokens.emplace_back(
                        TokenType::Greater,
                        ">",
                        location
                    );
                }

                break;

            case '<':
                advance();

                if (peek() == '=')
                {
                    advance();

                    tokens.emplace_back(
                        TokenType::LessEqual,
                        "<=",
                        location
                    );
                }
                else
                {
                    tokens.emplace_back(
                        TokenType::Less,
                        "<",
                        location
                    );
                }

                break;

            default:
                throw LexerError(
                    "Unknown character",
                    location
                );
        }
    }

    tokens.emplace_back(
        TokenType::EndOfFile,
        "",
        SourceLocation(
            m_line,
            m_column
        )
    );

    return tokens;
}

bool Lexer::isAtEnd() const
{
    return m_position >=
           m_source.size();
}

char Lexer::peek() const
{
    if (isAtEnd())
    {
        return '\0';
    }

    return m_source[m_position];
}

char Lexer::peekNext() const
{
    if (m_position + 1 >=
        m_source.size())
    {
        return '\0';
    }

    return m_source[
        m_position + 1
    ];
}

char Lexer::advance()
{
    char c =
        m_source[m_position++];

    ++m_column;

    return c;
}

void Lexer::skipWhitespace()
{
    while (!isAtEnd())
    {
        char c = peek();

        if (c == '\n')
        {
            ++m_line;

            m_column = 1;

            advance();

            continue;
        }

        if (std::isspace(c))
        {
            advance();

            continue;
        }

        break;
    }
}

Token Lexer::string()
{
    SourceLocation location(
        m_line,
        m_column
    );

    advance();

    std::string value;

    while (!isAtEnd() &&
           peek() != '"')
    {
        value.push_back(
            advance()
        );
    }

    if (isAtEnd())
    {
        throw LexerError(
            "Unterminated string",
            location
        );
    }

    advance();

    return makeToken(
        TokenType::String,
        value,
        location
    );
}

Token Lexer::number()
{
    SourceLocation location(
        m_line,
        m_column
    );

    std::string value;

    while (std::isdigit(peek()))
    {
        value.push_back(
            advance()
        );
    }

    if (peek() == '.')
    {
        value.push_back(
            advance()
        );

        while (std::isdigit(peek()))
        {
            value.push_back(
                advance()
            );
        }
    }

    return makeToken(
        TokenType::Number,
        value,
        location
    );
}

Token Lexer::identifier()
{
    SourceLocation location(
        m_line,
        m_column
    );

    std::string text;

    while (
        std::isalnum(peek()) ||
        peek() == '_'
    )
    {
        text.push_back(
            advance()
        );
    }

    return makeToken(
        keywordType(text),
        text,
        location
    );
}

Token Lexer::makeToken(
    TokenType type,
    const std::string& lexeme,
    SourceLocation location
)
{
    return Token(
        type,
        lexeme,
        location
    );
}

TokenType Lexer::keywordType(
    const std::string& text
) const
{
    static const std::unordered_map<
        std::string,
        TokenType
    > keywords =
    {
        {"riven",TokenType::Riven},
        {"core",TokenType::Core},

        {"consistof",TokenType::ConsistOf},

        {"firm",TokenType::Firm},

        {"craft",TokenType::Craft},
        {"returns",TokenType::Returns},

        {"if",TokenType::If},
        {"altif",TokenType::AltIf},
        {"else",TokenType::Else},

        {"flow",TokenType::Flow},
        {"during",TokenType::During},

        {"imprint",TokenType::Imprint},
        {"scanq",TokenType::Scanq},

        {"correct",TokenType::Correct},
        {"incorrect",TokenType::Incorrect},

        {"emp",TokenType::Emp},

        {"and",TokenType::And},
        {"or",TokenType::Or},
        {"not",TokenType::Not},

        {"rise",TokenType::Rise},
        {"drop",TokenType::Drop}
    };

    auto it =
        keywords.find(text);

    if (it != keywords.end())
    {
        return it->second;
    }

    return TokenType::Identifier;
}

}
