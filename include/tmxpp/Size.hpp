#ifndef TMXPP_SIZE_HPP
#define TMXPP_SIZE_HPP

#include <tmxpp/Pixel.hpp>

namespace tmxpp {

struct Size {
    using Dimension = Pixel;

    Dimension w;
    Dimension h;
};

constexpr bool operator==(Size l, Size r) noexcept
{
    return l.w == r.w && l.h == r.h;
}

constexpr bool operator!=(Size l, Size r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_SIZE_HPP
