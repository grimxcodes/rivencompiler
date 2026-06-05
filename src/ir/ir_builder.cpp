#include "../../include/ir/ir_builder.hpp"

namespace riven
{

IRModule IRBuilder::build(
    ProgramNode* program
)
{
    for (auto& node :
         program->declarations)
    {
        generateNode(
            node.get()
        );
    }

    return m_module;
}

void IRBuilder::generateNode(
    ASTNode* node
)
{
    switch (node->type())
    {
        case ASTNodeType::Constant:
            generateConstant(
                static_cast<
                    ConstantNode*>(
                    node
                )
            );
            break;

        case ASTNodeType::Function:
            generateFunction(
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

void IRBuilder::generateConstant(
    ConstantNode* node
)
{
    std::string value =
        generateExpression(
            node->value.get()
        );

    m_module.addInstruction(
        {
            IRInstructionType::
            StoreVariable,

            value,
            "",
            node->name
        }
    );
}

void IRBuilder::generateFunction(
    FunctionNode* node
)
{
    m_module.addInstruction(
        {
            IRInstructionType::
            Call,

            node->name,
            "",
            ""
        }
    );
}

std::string IRBuilder::
generateExpression(
    ASTNode* node
)
{
    if (
        node->type() ==
        ASTNodeType::
        NumberLiteral
    )
    {
        auto* literal =
            static_cast<
                NumberLiteralNode*>(
                node
            );

        std::string temp =
            createTemp();

        m_module.addInstruction(
            {
                IRInstructionType::
                LoadConst,

                literal->value,
                "",
                temp
            }
        );

        return temp;
    }

    if (
        node->type() ==
        ASTNodeType::
        StringLiteral
    )
    {
        auto* literal =
            static_cast<
                StringLiteralNode*>(
                node
            );

        std::string temp =
            createTemp();

        m_module.addInstruction(
            {
                IRInstructionType::
                LoadConst,

                literal->value,
                "",
                temp
            }
        );

        return temp;
    }

    if (
        node->type() ==
        ASTNodeType::
        Identifier
    )
    {
        auto* identifier =
            static_cast<
                IdentifierNode*>(
                node
            );

        return identifier->name;
    }

    return "";
}

std::string IRBuilder::createTemp()
{
    return "_t" +
           std::to_string(
               m_tempCounter++
           );
}

}
