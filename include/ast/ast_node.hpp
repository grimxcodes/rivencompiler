#pragma once

#include <memory>
#include <vector>

#include "../common/source_location.hpp"

namespace riven
{

enum class ASTNodeType
{
    Program,

    EntryPoint,

    Import,

    Constant,
    Variable,

    Function,
    Return,

    If,
    Flow,
    During,

    CallExpression,

    BinaryExpression,

    Identifier,

    NumberLiteral,
    StringLiteral,

    BooleanLiteral,

    NullLiteral
};

class ASTNode
{
public:
    ASTNode(
        ASTNodeType type,
        SourceLocation location
    )
        : m_type(type),
          m_location(location)
    {
    }

    virtual ~ASTNode() = default;

    ASTNodeType type() const
    {
        return m_type;
    }

    SourceLocation location() const
    {
        return m_location;
    }

private:
    ASTNodeType m_type;

    SourceLocation m_location;
};

using ASTNodePtr =
    std::unique_ptr<ASTNode>;

class ProgramNode final
    : public ASTNode
{
public:
    ProgramNode()
        : ASTNode(
            ASTNodeType::Program,
            {}
        )
    {
    }

    std::vector<ASTNodePtr>
        declarations;
};

}
