#ifndef TMXPP_FLIP_HPP
#define TMXPP_FLIP_HPP

#include <jegp/utility.hpp>

namespace tmxpp {

enum class Flip : unsigned char {
    horizontal = 1 << 2,
    vertical   = 1 << 1,
    diagonal   = 1 << 0
};

constexpr Flip operator&(Flip l, Flip r) noexcept
{
    return static_cast<Flip>(jegp::underlying(l) & jegp::underlying(r));
}
constexpr Flip operator|(Flip l, Flip r) noexcept
{
    return static_cast<Flip>(jegp::underlying(l) | jegp::underlying(r));
}
constexpr Flip operator^(Flip l, Flip r) noexcept
{
    return static_cast<Flip>(jegp::underlying(l) ^ jegp::underlying(r));
}

constexpr Flip operator~(Flip f) noexcept
{
    return static_cast<Flip>(~jegp::underlying(f));
}

constexpr Flip& operator&=(Flip& l, Flip r) noexcept
{
    return l = l & r;
}
constexpr Flip& operator|=(Flip& l, Flip r) noexcept
{
    return l = l | r;
}
constexpr Flip& operator^=(Flip& l, Flip r) noexcept
{
    return l = l ^ r;
}

} // namespace tmxpp

#endif // TMXPP_FLIP_HPP
