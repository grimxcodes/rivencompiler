#include "../../include/semantic/symbol_table.hpp"

namespace riven
{

bool SymbolTable::exists(
    const std::string& name
) const
{
    return m_symbols.find(name)
           != m_symbols.end();
}

void SymbolTable::define(
    const Symbol& symbol
)
{
    m_symbols[symbol.name] =
        symbol;
}

const Symbol* SymbolTable::lookup(
    const std::string& name
) const
{
    auto iterator =
        m_symbols.find(name);

    if (iterator ==
        m_symbols.end())
    {
        return nullptr;
    }

    return &iterator->second;
}

}
