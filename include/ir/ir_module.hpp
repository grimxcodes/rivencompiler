#pragma once

#include <vector>

#include "ir_instruction.hpp"

namespace riven
{

class IRModule
{
public:
    void addInstruction(
        const IRInstruction& instruction
    );

    const std::vector<
        IRInstruction
    >& instructions() const;

private:
    std::vector<
        IRInstruction
    > m_instructions;
};

}
