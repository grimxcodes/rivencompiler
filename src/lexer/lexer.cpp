#include "../../include/lexer/lexer.hpp"

#include <cctype>
#include <unordered_map>

#include "../../include/common/error.hpp"

namespace riven
{

Lexer::Lexer(const std::string& source)
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

        char current = peek();

        if (std::isalpha(current) || current == '_')
        {
            tokens.push_back(identifier());
            continue;
        }

        if (std::isdigit(current))
        {
            tokens.push_back(number());
            continue;
        }

        switch (current)
        {
            case '"':
                tokens.push_back(string());
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

            case '.':
                advance();
                tokens.emplace_back(
                    TokenType::Dot,
                    ".",
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

            case '=':
            {
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
            }

            case '!':
            {
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
            }

            case '>':
            {
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
            }

            case '<':
            {
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
            }

            case '+':
            {
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
            }

            case '-':
            {
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
            }

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

            default:
                throw LexerError(
                    "Unknown character: " +
                    std::string(1, current),
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
    return m_position >= m_source.size();
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
    if (m_position + 1 >= m_source.size())
    {
        return '\0';
    }

    return m_source[m_position + 1];
}

char Lexer::advance()
{
    char current = m_source[m_position++];

    if (current == '\n')
    {
        ++m_line;
        m_column = 1;
    }
    else
    {
        ++m_column;
    }

    return current;
}

void Lexer::skipWhitespace()
{
    while (!isAtEnd())
    {
        char current = peek();

        if (current == ' ' ||
            current == '\t' ||
            current == '\r' ||
            current == '\n')
        {
            advance();
        }
        else
        {
            break;
        }
    }
}

Token Lexer::identifier()
{
    SourceLocation location(
        m_line,
        m_column
    );

    std::string text;

    while (!isAtEnd())
    {
        char current = peek();

        if (std::isalnum(current) ||
            current == '_')
        {
            text += advance();
        }
        else
        {
            break;
        }
    }

    return Token(
        keywordType(text),
        text,
        location
    );
}

Token Lexer::number()
{
    SourceLocation location(
        m_line,
        m_column
    );

    std::string text;

    while (!isAtEnd() &&
           std::isdigit(peek()))
    {
        text += advance();
    }

    if (!isAtEnd() &&
        peek() == '.')
    {
        text += advance();

        while (!isAtEnd() &&
               std::isdigit(peek()))
        {
            text += advance();
        }
    }

    return Token(
        TokenType::Number,
        text,
        location
    );
}

Token Lexer::string()
{
    SourceLocation location(
        m_line,
        m_column
    );

    advance();

    std::string text;

    while (!isAtEnd() &&
           peek() != '"')
    {
        text += advance();
    }

    if (isAtEnd())
    {
        throw LexerError(
            "Unterminated string",
            location
        );
    }

    advance();

    return Token(
        TokenType::String,
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
        {"riven", TokenType::Riven},
        {"core", TokenType::Core},

        {"consistof", TokenType::ConsistOf},

        {"firm", TokenType::Firm},

        {"craft", TokenType::Craft},
        {"returns", TokenType::Returns},

        {"frame", TokenType::Frame},
        {"boot", TokenType::Boot},

        {"open", TokenType::Open},
        {"hidden", TokenType::Hidden},

        {"if", TokenType::If},
        {"altif", TokenType::AltIf},
        {"else", TokenType::Else},

        {"flow", TokenType::Flow},
        {"during", TokenType::During},

        {"spark", TokenType::Spark},
        {"sync", TokenType::Sync},

        {"ref", TokenType::Ref},
        {"ptr", TokenType::Ptr},

        {"raw", TokenType::Raw},

        {"rise", TokenType::Rise},
        {"drop", TokenType::Drop},

        {"imprint", TokenType::Imprint},
        {"scanq", TokenType::Scanq},

        {"fetch", TokenType::Fetch},

        {"attack", TokenType::Attack},
        {"resc", TokenType::Resc},

        {"correct", TokenType::Correct},
        {"incorrect", TokenType::Incorrect},

        {"emp", TokenType::Emp},

        {"and", TokenType::And},
        {"or", TokenType::Or},
        {"not", TokenType::Not}
    };

    auto iterator = keywords.find(text);

    if (iterator != keywords.end())
    {
        return iterator->second;
    }

    return TokenType::Identifier;
}

}
