#pragma once

#include <string>

namespace riven
{

enum class IRInstructionType
{
    LoadConst,

    LoadVariable,
    StoreVariable,

    Add,
    Subtract,
    Multiply,
    Divide,

    CompareEqual,
    CompareNotEqual,

    CompareGreater,
    CompareLess,

    CompareGreaterEqual,
    CompareLessEqual,

    Jump,
    JumpIfFalse,

    Call,
    Return
};

struct IRInstruction
{
    IRInstructionType type;

    std::string operand1;
    std::string operand2;
    std::string result;
};

}
