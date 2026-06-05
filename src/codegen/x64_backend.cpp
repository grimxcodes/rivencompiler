#include "../../include/codegen/x64_backend.hpp"

namespace riven
{

std::vector<std::uint8_t>
X64Backend::generate(
    const IRModule& module
)
{
    m_code.clear();

    for (
        const auto& instruction :
        module.instructions()
    )
    {
        switch (
            instruction.type
        )
        {
            case IRInstructionType::LoadConst:
                break;

            case IRInstructionType::StoreVariable:
                break;

            case IRInstructionType::Call:
                break;

            default:
                break;
        }
    }

    return m_code;
}

void X64Backend::emit(
    std::uint8_t byte
)
{
    m_code.push_back(
        byte
    );
}

void X64Backend::emit32(
    std::uint32_t value
)
{
    emit(
        static_cast<
            std::uint8_t
        >(value)
    );

    emit(
        static_cast<
            std::uint8_t
        >(value >> 8)
    );

    emit(
        static_cast<
            std::uint8_t
        >(value >> 16)
    );

    emit(
        static_cast<
            std::uint8_t
        >(value >> 24)
    );
}

}
