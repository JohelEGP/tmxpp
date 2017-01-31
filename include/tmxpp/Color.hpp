#ifndef TMXPP_COLOR_HPP
#define TMXPP_COLOR_HPP

#include <cstdint>

namespace tmxpp {

struct Color {
    using Channel = std::uint_least8_t;

    Channel alpha;
    Channel red;
    Channel green;
    Channel blue;
};

constexpr bool operator==(Color l, Color r) noexcept
{
    return l.alpha == r.alpha && l.red == r.red && l.green == r.green &&
           l.blue == r.blue;
}

constexpr bool operator!=(Color l, Color r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_COLOR_HPP
