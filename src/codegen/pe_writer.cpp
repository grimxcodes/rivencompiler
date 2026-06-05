#include "../../include/codegen/pe_writer.hpp"

#include <fstream>

namespace riven
{

bool PEWriter::write(
    const std::string& outputFile,
    const std::vector<
        std::uint8_t
    >& machineCode
)
{
    std::ofstream file(
        outputFile,
        std::ios::binary
    );

    if (!file)
    {
        return false;
    }

    file.write(
        reinterpret_cast<
            const char*
        >(machineCode.data()),
        static_cast<
            std::streamsize
        >(machineCode.size())
    );

    return true;
}

}
