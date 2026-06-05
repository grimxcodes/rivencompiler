#pragma once

#include "ast_node.hpp"

namespace riven
{

class ExpressionNode : public ASTNode
{
public:
    ExpressionNode(
        ASTNodeType type,
        SourceLocation location
    )
        : ASTNode(type, location)
    {
    }
};

class IdentifierNode final : public ExpressionNode
{
public:
    std::string name;

    IdentifierNode(
        const std::string& identifier,
        SourceLocation location
    )
        : ExpressionNode(
              ASTNodeType::Identifier,
              location
          ),
          name(identifier)
    {
    }
};

class NumberLiteralNode final : public ExpressionNode
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

class StringLiteralNode final : public ExpressionNode
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

}
