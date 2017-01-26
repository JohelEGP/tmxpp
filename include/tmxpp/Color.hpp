#ifndef TMXPP_COLOR_HPP
#define TMXPP_COLOR_HPP

#include <cstdint>

namespace tmxpp {

struct Color {
    using Channel = std::uint_least8_t;

    Channel a;
    Channel r;
    Channel g;
    Channel b;
};

constexpr bool operator==(Color l, Color r) noexcept
{
    return l.a == r.a && l.r == r.r && l.g == r.g && l.b == r.b;
}

constexpr bool operator!=(Color l, Color r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_COLOR_HPP
