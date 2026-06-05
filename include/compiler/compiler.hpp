#pragma once

#include <string>

namespace riven
{

class Compiler
{
public:
    bool compile(
        const std::string& source,
        const std::string& output
    );
};

}
