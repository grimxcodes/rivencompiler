#pragma once

#include "ast_node.hpp"

namespace riven
{

class StatementNode
    : public ASTNode
{
public:
    StatementNode(
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

}
