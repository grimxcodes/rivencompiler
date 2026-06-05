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

    if (match(TokenType::Firm))
    {
        return parseFirm();
    }

    if (match(TokenType::Craft))
    {
        return parseFunction();
    }

    if (match(TokenType::If))
    {
        return parseIf();
    }

    if (match(TokenType::Flow))
    {
        return parseFlow();
    }

    if (match(TokenType::During))
    {
        return parseDuring();
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
            "Expected import path"
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

ASTNodePtr Parser::parseFirm()
{
    Token name =
        consume(
            TokenType::Identifier,
            "Expected constant name"
        );

    consume(
        TokenType::Assign,
        "Expected '='"
    );

    auto value =
        expression();

    return std::make_unique<ConstantNode>(
        name.lexeme,
        std::move(value),
        name.location
    );
}

ASTNodePtr Parser::parseFunction()
{
    Token name =
        consume(
            TokenType::Identifier,
            "Expected function name"
        );

    auto function =
        std::make_unique<FunctionNode>(
            name.lexeme,
            name.location
        );

    consume(
        TokenType::LeftParen,
        "Expected '('"
    );

    while (!check(
        TokenType::RightParen))
    {
        Token parameter =
            consume(
                TokenType::Identifier,
                "Expected parameter"
            );

        function->parameters.push_back(
            parameter.lexeme
        );

        if (!match(
            TokenType::Comma))
        {
            break;
        }
    }

    consume(
        TokenType::RightParen,
        "Expected ')'"
    );

    consume(
        TokenType::LeftBrace,
        "Expected '{'"
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

    return function;
}

ASTNodePtr Parser::parseIf()
{
    auto node =
        std::make_unique<IfNode>(
            previous().location
        );

    node->condition =
        expression();

    consume(
        TokenType::LeftBrace,
        "Expected '{'"
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

ASTNodePtr Parser::parseFlow()
{
    auto node =
        std::make_unique<FlowNode>(
            previous().location
        );

    node->count =
        expression();

    consume(
        TokenType::LeftBrace,
        "Expected '{'"
    );

    while (!check(
        TokenType::RightBrace))
    {
        if (isAtEnd())
        {
            throw ParserError(
                "Expected '}'"
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

ASTNodePtr Parser::parseDuring()
{
    auto node =
        std::make_unique<DuringNode>(
            previous().location
        );

    node->condition =
        expression();

    consume(
        TokenType::LeftBrace,
        "Expected '{'"
    );

    while (!check(
        TokenType::RightBrace))
    {
        if (isAtEnd())
        {
            throw ParserError(
                "Expected '}'"
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

ASTNodePtr Parser::expression()
{
    return primary();
}

ASTNodePtr Parser::primary()
{
    if (match(TokenType::Number))
    {
        return std::make_unique<
            NumberLiteralNode>(
            previous().lexeme,
            previous().location
        );
    }

    if (match(TokenType::String))
    {
        return std::make_unique<
            StringLiteralNode>(
            previous().lexeme,
            previous().location
        );
    }

    if (match(TokenType::Identifier))
    {
        return std::make_unique<
            IdentifierNode>(
            previous().lexeme,
            previous().location
        );
    }

    throw ParserError(
        "Invalid expression",
        peek().location
    );
}

}
