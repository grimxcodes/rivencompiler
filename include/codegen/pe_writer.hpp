#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace riven
{

class PEWriter
{
public:
    bool write(
        const std::string& outputFile,
        const std::vector<
            std::uint8_t
        >& machineCode
    );
};

}
