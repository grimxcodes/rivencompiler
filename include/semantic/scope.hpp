#pragma once

#include <memory>

#include "symbol_table.hpp"

namespace riven
{

class Scope
{
public:
    explicit Scope(
        Scope* parent = nullptr
    );

    Scope* parent() const;

    SymbolTable& symbols();

private:
    Scope* m_parent;

    SymbolTable m_symbols;
};

}
