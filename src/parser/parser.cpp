#include "../../include/parser/parser.hpp"

#include "../../include/common/error.hpp"

namespace riven
{

Parser::Parser(
    const std::vector<Token>& tokens
)
    : m_tokens(tokens)
{
}

std::unique_ptr<ProgramNode> Parser::parse()
{
    auto program =
        std::make_unique<ProgramNode>();

    while (!isAtEnd())
    {
        auto node = declaration();

        if (node)
        {
            program->declarations.push_back(
                std::move(node)
            );
        }
    }

    return program;
}

bool Parser::isAtEnd() const
{
    return peek().type ==
           TokenType::EndOfFile;
}

const Token& Parser::peek() const
{
    return m_tokens[m_current];
}

const Token& Parser::previous() const
{
    return m_tokens[m_current - 1];
}

const Token& Parser::advance()
{
    if (!isAtEnd())
    {
        ++m_current;
    }

    return previous();
}

bool Parser::check(
    TokenType type
) const
{
    if (isAtEnd())
    {
        return false;
    }

    return peek().type == type;
}

bool Parser::match(
    TokenType type
)
{
    if (!check(type))
    {
        return false;
    }

    advance();

    return true;
}

const Token& Parser::consume(
    TokenType type,
    const std::string& message
)
{
    if (check(type))
    {
        return advance();
    }

    throw ParserError(
        message,
        peek().location
    );
}

ASTNodePtr Parser::declaration()
{
    if (match(TokenType::ConsistOf))
    {
        return parseImport();
    }

    if (match(TokenType::Riven))
    {
        return parseCore();
    }

    throw ParserError(
        "Unexpected token",
        peek().location
    );
}

ASTNodePtr Parser::parseImport()
{
    Token fileToken =
        consume(
            TokenType::String,
            "Expected import file"
        );

    return std::make_unique<ImportNode>(
        fileToken.lexeme,
        fileToken.location
    );
}

ASTNodePtr Parser::parseCore()
{
    Token coreToken =
        consume(
            TokenType::Core,
            "Expected core keyword"
        );

    consume(
        TokenType::LeftBrace,
        "Expected '{'"
    );

    auto node =
        std::make_unique<CoreNode>(
            coreToken.location
        );

    while (!check(
        TokenType::RightBrace))
    {
        if (isAtEnd())
        {
            throw ParserError(
                "Expected '}'",
                peek().location
            );
        }

        advance();
    }

    consume(
        TokenType::RightBrace,
        "Expected '}'"
    );

    return node;
}

}
