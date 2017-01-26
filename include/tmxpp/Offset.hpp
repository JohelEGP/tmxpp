#ifndef TMXPP_OFFSET_HPP
#define TMXPP_OFFSET_HPP

#include <tmxpp/Pixel.hpp>

namespace tmxpp {

struct Offset {
    using Dimension = Pixel;

    Dimension w;
    Dimension h;
};

constexpr bool operator==(Offset l, Offset r) noexcept
{
    return l.w == r.w && l.h == r.h;
}

constexpr bool operator!=(Offset l, Offset r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_OFFSET_HPP
