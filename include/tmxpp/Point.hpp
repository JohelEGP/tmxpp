#ifndef TMXPP_POINT_HPP
#define TMXPP_POINT_HPP

#include <tmxpp/Pixels.hpp>

namespace tmxpp {

struct Point {
    using Coordinate = Pixels;

    Coordinate x;
    Coordinate y;
};

constexpr bool operator==(Point l, Point r) noexcept
{
    return l.x == r.x && l.y == r.y;
}

constexpr bool operator!=(Point l, Point r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_POINT_HPP
