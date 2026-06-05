#pragma once

#include "../ast/statements.hpp"
#include "../ast/declarations.hpp"

#include "scope.hpp"

namespace riven
{

class SemanticAnalyzer
{
public:
    void analyze(
        ProgramNode* program
    );

private:
    Scope m_globalScope;

private:
    void analyzeNode(
        ASTNode* node
    );

    void analyzeConstant(
        ConstantNode* node
    );

    void analyzeFunction(
        FunctionNode* node
    );
};

}
