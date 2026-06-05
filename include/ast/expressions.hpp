#pragma once

#include "ast_node.hpp"

#include "../common/token_type.hpp"

namespace riven
{

class ExpressionNode
    : public ASTNode
{
public:
    ExpressionNode(
        ASTNodeType type,
        SourceLocation location
    )
        : ASTNode(
            type,
            location
        )
    {
    }
};

class IdentifierNode final
    : public ExpressionNode
{
public:
    std::string name;

    IdentifierNode(
        const std::string& value,
        SourceLocation location
    )
        : ExpressionNode(
            ASTNodeType::Identifier,
            location
        ),
          name(value)
    {
    }
};

class NumberLiteralNode final
    : public ExpressionNode
{
public:
    std::string value;

    NumberLiteralNode(
        const std::string& number,
        SourceLocation location
    )
        : ExpressionNode(
            ASTNodeType::NumberLiteral,
            location
        ),
          value(number)
    {
    }
};

class StringLiteralNode final
    : public ExpressionNode
{
public:
    std::string value;

    StringLiteralNode(
        const std::string& text,
        SourceLocation location
    )
        : ExpressionNode(
            ASTNodeType::StringLiteral,
            location
        ),
          value(text)
    {
    }
};

class BooleanLiteralNode final
    : public ExpressionNode
{
public:
    bool value;

    BooleanLiteralNode(
        bool state,
        SourceLocation location
    )
        : ExpressionNode(
            ASTNodeType::BooleanLiteral,
            location
        ),
          value(state)
    {
    }
};

class NullLiteralNode final
    : public ExpressionNode
{
public:
    NullLiteralNode(
        SourceLocation location
    )
        : ExpressionNode(
            ASTNodeType::NullLiteral,
            location
        )
    {
    }
};

class BinaryExpressionNode final
    : public ExpressionNode
{
public:
    TokenType operation;

    ASTNodePtr left;

    ASTNodePtr right;

    BinaryExpressionNode(
        TokenType op,
        ASTNodePtr lhs,
        ASTNodePtr rhs,
        SourceLocation location
    )
        : ExpressionNode(
            ASTNodeType::
            BinaryExpression,
            location
        ),
          operation(op),
          left(std::move(lhs)),
          right(std::move(rhs))
    {
    }
};

class CallExpressionNode final
    : public ExpressionNode
{
public:
    std::string callee;

    std::vector<
        ASTNodePtr
    > arguments;

    CallExpressionNode(
        const std::string& function,
        SourceLocation location
    )
        : ExpressionNode(
            ASTNodeType::
            CallExpression,
            location
        ),
          callee(function)
    {
    }
};

}
