#include "../../include/semantic/analyzer.hpp"

#include "../../include/common/error.hpp"

namespace riven
{

void SemanticAnalyzer::analyze(
    ProgramNode* program
)
{
    for (auto& node :
         program->declarations)
    {
        analyzeNode(
            node.get()
        );
    }
}

void SemanticAnalyzer::analyzeNode(
    ASTNode* node
)
{
    switch (node->type())
    {
        case ASTNodeType::Constant:
            analyzeConstant(
                static_cast<
                    ConstantNode*>(
                    node
                )
            );
            break;

        case ASTNodeType::Function:
            analyzeFunction(
                static_cast<
                    FunctionNode*>(
                    node
                )
            );
            break;

        default:
            break;
    }
}

void SemanticAnalyzer::analyzeConstant(
    ConstantNode* node
)
{
    if (
        m_globalScope
        .symbols()
        .exists(node->name)
    )
    {
        throw SemanticError(
            "Duplicate symbol: "
            + node->name,
            node->location()
        );
    }

    m_globalScope
        .symbols()
        .define(
            {
                node->name,
                SymbolType::Constant
            }
        );
}

void SemanticAnalyzer::analyzeFunction(
    FunctionNode* node
)
{
    if (
        m_globalScope
        .symbols()
        .exists(node->name)
    )
    {
        throw SemanticError(
            "Duplicate function: "
            + node->name,
            node->location()
        );
    }

    m_globalScope
        .symbols()
        .define(
            {
                node->name,
                SymbolType::Function
            }
        );
}

}
