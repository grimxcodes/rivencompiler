#pragma once

#include <cstddef>

namespace riven
{

struct SourceLocation
{
    std::size_t line;
    std::size_t column;

    constexpr SourceLocation(
        std::size_t lineNumber = 1,
        std::size_t columnNumber = 1
    )
        : line(lineNumber),
          column(columnNumber)
    {
    }

    constexpr bool operator==(
        const SourceLocation& other
    ) const
    {
        return line == other.line &&
               column == other.column;
    }

    constexpr bool operator!=(
        const SourceLocation& other
    ) const
    {
        return !(*this == other);
    }
};

}
