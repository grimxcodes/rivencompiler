#pragma once

#include <string>
#include <unordered_map>

namespace riven
{

enum class SymbolType
{
    Variable,
    Constant,
    Function,
    Frame
};

struct Symbol
{
    std::string name;
    SymbolType type;
};

class SymbolTable
{
public:
    bool exists(
        const std::string& name
    ) const;

    void define(
        const Symbol& symbol
    );

    const Symbol* lookup(
        const std::string& name
    ) const;

private:
    std::unordered_map<
        std::string,
        Symbol
    > m_symbols;
};

}
