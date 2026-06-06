#pragma once

#include "statements.hpp"

namespace riven
{

class IfNode final
    : public StatementNode
{
public:
    ASTNodePtr condition;

    std::vector<
        ASTNodePtr
    > body;

    std::vector<
        ASTNodePtr
    > altIfConditions;

    std::vector<
        std::vector<
            ASTNodePtr
        >
    > altIfBodies;

    std::vector<
        ASTNodePtr
    > elseBody;

    IfNode(
        SourceLocation location
    )
        : StatementNode(
            ASTNodeType::If,
            location
        )
    {
    }
};

class FlowNode final
    : public StatementNode
{
public:
    ASTNodePtr count;

    std::vector<
        ASTNodePtr
    > body;

    FlowNode(
        SourceLocation location
    )
        : StatementNode(
            ASTNodeType::Flow,
            location
        )
    {
    }
};

class DuringNode final
    : public StatementNode
{
public:
    ASTNodePtr condition;

    std::vector<
        ASTNodePtr
    > body;

    DuringNode(
        SourceLocation location
    )
        : StatementNode(
            ASTNodeType::During,
            location
        )
    {
    }
};

}
