#pragma once

#include "../ast/statements.hpp"
#include "../ast/declarations.hpp"
#include "../ast/expressions.hpp"

#include "ir_module.hpp"

namespace riven
{

class IRBuilder
{
public:
    IRModule build(
        ProgramNode* program
    );

private:
    IRModule m_module;

    int m_tempCounter = 0;

private:
    void generateNode(
        ASTNode* node
    );

    void generateConstant(
        ConstantNode* node
    );

    void generateFunction(
        FunctionNode* node
    );

    std::string generateExpression(
        ASTNode* node
    );

    std::string createTemp();
};

}
