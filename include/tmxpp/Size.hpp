#ifndef TMXPP_SIZE_HPP
#define TMXPP_SIZE_HPP

#include <tmxpp/Pixel.hpp>

namespace tmxpp {

template <class Number>
struct Size {
    using Dimension = Number;

    Dimension width;
    Dimension height;
};

using pxSize = Size<Pixel>;
using iSize  = Size<int>;

template <class N>
constexpr bool operator==(Size<N> l, Size<N> r) noexcept
{
    return l.width == r.width && l.height == r.height;
}

template <class N>
constexpr bool operator!=(Size<N> l, Size<N> r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_SIZE_HPP
