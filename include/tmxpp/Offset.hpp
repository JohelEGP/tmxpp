#ifndef TMXPP_OFFSET_HPP
#define TMXPP_OFFSET_HPP

#include <tmxpp/Pixel.hpp>

namespace tmxpp {

struct Offset {
    using Coordinate = Pixel;

    Coordinate x;
    Coordinate y;
};

constexpr bool operator==(Offset l, Offset r) noexcept
{
    return l.x == r.x && l.y == r.y;
}

constexpr bool operator!=(Offset l, Offset r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_OFFSET_HPP
