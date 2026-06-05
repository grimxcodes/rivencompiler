#pragma once

#include "ast_node.hpp"

namespace riven
{

class StatementNode : public ASTNode
{
public:
    StatementNode(
        ASTNodeType type,
        SourceLocation location
    )
        : ASTNode(type, location)
    {
    }
};

class ProgramNode final : public ASTNode
{
public:
    std::vector<ASTNodePtr> declarations;

    ProgramNode()
        : ASTNode(
              ASTNodeType::Program,
              SourceLocation()
          )
    {
    }
};

class ImportNode final : public StatementNode
{
public:
    std::string path;

    ImportNode(
        const std::string& importPath,
        SourceLocation location
    )
        : StatementNode(
              ASTNodeType::Import,
              location
          ),
          path(importPath)
    {
    }
};

class CoreNode final : public StatementNode
{
public:
    std::vector<ASTNodePtr> body;

    CoreNode(
        SourceLocation location
    )
        : StatementNode(
              ASTNodeType::Core,
              location
          )
    {
    }
};

}
