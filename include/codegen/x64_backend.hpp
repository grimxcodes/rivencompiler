#pragma once

#include "../ir/ir_module.hpp"

#include <vector>
#include <cstdint>

namespace riven
{

class X64Backend
{
public:
    std::vector<std::uint8_t>
    generate(
        const IRModule& module
    );

private:
    void emit(
        std::uint8_t byte
    );

    void emit32(
        std::uint32_t value
    );

private:
    std::vector<
        std::uint8_t
    > m_code;
};

}
