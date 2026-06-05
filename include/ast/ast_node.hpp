#pragma once

#include <memory>
#include <string>
#include <vector>

#include "../common/source_location.hpp"

namespace riven
{

enum class ASTNodeType
{
    Program,

    Import,

    Core,

    Variable,
    Constant,

    Function,
    Return,

    Frame,
    Method,

    If,
    Flow,
    During,

    Call,

    BinaryExpression,
    UnaryExpression,

    Identifier,
    NumberLiteral,
    StringLiteral
};

class ASTNode
{
public:
    ASTNode(
        ASTNodeType nodeType,
        SourceLocation location
    )
        : m_type(nodeType),
          m_location(location)
    {
    }

    virtual ~ASTNode() = default;

    [[nodiscard]]
    ASTNodeType type() const
    {
        return m_type;
    }

    [[nodiscard]]
    SourceLocation location() const
    {
        return m_location;
    }

private:
    ASTNodeType m_type;
    SourceLocation m_location;
};

using ASTNodePtr = std::unique_ptr<ASTNode>;

}
