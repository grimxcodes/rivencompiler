#pragma once

#include <vector>

#include "../common/token.hpp"

#include "../ast/ast_node.hpp"
#include "../ast/expressions.hpp"
#include "../ast/statements.hpp"
#include "../ast/declarations.hpp"
#include "../ast/control_flow.hpp"

namespace riven
{

class Parser
{
public:
    explicit Parser(
        const std::vector<Token>& tokens
    );

    std::unique_ptr<ProgramNode>
    parse();

private:
    const std::vector<Token>& m_tokens;

    std::size_t m_current = 0;

private:
    bool isAtEnd() const;

    const Token& peek() const;

    const Token& previous() const;

    const Token& advance();

    bool check(
        TokenType type
    ) const;

    bool match(
        TokenType type
    );

    const Token& consume(
        TokenType type,
        const std::string& message
    );

private:
    ASTNodePtr declaration();

    ASTNodePtr statement();

private:
    ASTNodePtr parseImport();

    ASTNodePtr parseConstant();

    ASTNodePtr parseVariable();

    ASTNodePtr parseFunction();

    ASTNodePtr parseReturn();

    ASTNodePtr parseIf();

    ASTNodePtr parseFlow();

    ASTNodePtr parseDuring();

private:
    ASTNodePtr expression();

    ASTNodePtr equality();

    ASTNodePtr comparison();

    ASTNodePtr term();

    ASTNodePtr factor();

    ASTNodePtr primary();

private:
    ASTNodePtr parseCall(
        const Token& identifier
    );
};

}
