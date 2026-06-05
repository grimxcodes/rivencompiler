#include "../../include/semantic/scope.hpp"

namespace riven
{

Scope::Scope(
    Scope* parent
)
    : m_parent(parent)
{
}

Scope* Scope::parent() const
{
    return m_parent;
}

SymbolTable& Scope::symbols()
{
    return m_symbols;
}

}
