#pragma once

#include <memory>
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

    std::unique_ptr<ProgramNode> parse();

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

    ASTNodePtr parseImport();

    ASTNodePtr parseCore();

    ASTNodePtr parseFirm();

    ASTNodePtr parseFunction();

    ASTNodePtr parseIf();

    ASTNodePtr parseFlow();

    ASTNodePtr parseDuring();

private:
    ASTNodePtr expression();

    ASTNodePtr primary();
};

}
