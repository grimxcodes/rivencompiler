#pragma once

#include "statements.hpp"
#include "expressions.hpp"

namespace riven
{

class ConstantNode final : public StatementNode
{
public:
    std::string name;

    ASTNodePtr value;

    ConstantNode(
        const std::string& constantName,
        ASTNodePtr constantValue,
        SourceLocation location
    )
        : StatementNode(
              ASTNodeType::Constant,
              location
          ),
          name(constantName),
          value(std::move(constantValue))
    {
    }
};

class VariableNode final : public StatementNode
{
public:
    std::string name;

    ASTNodePtr value;

    VariableNode(
        const std::string& variableName,
        ASTNodePtr variableValue,
        SourceLocation location
    )
        : StatementNode(
              ASTNodeType::Variable,
              location
          ),
          name(variableName),
          value(std::move(variableValue))
    {
    }
};

class ReturnNode final : public StatementNode
{
public:
    ASTNodePtr value;

    ReturnNode(
        ASTNodePtr returnValue,
        SourceLocation location
    )
        : StatementNode(
              ASTNodeType::Return,
              location
          ),
          value(std::move(returnValue))
    {
    }
};

class FunctionNode final : public StatementNode
{
public:
    std::string name;

    std::vector<std::string> parameters;

    std::vector<ASTNodePtr> body;

    FunctionNode(
        const std::string& functionName,
        SourceLocation location
    )
        : StatementNode(
              ASTNodeType::Function,
              location
          ),
          name(functionName)
    {
    }
};

}
