#include "../../include/ir/ir_module.hpp"

namespace riven
{

void IRModule::addInstruction(
    const IRInstruction& instruction
)
{
    m_instructions.push_back(
        instruction
    );
}

const std::vector<
    IRInstruction
>& IRModule::instructions() const
{
    return m_instructions;
}

}
