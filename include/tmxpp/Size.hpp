#ifndef TMXPP_SIZE_HPP
#define TMXPP_SIZE_HPP

#include <tmxpp/Constrained.hpp>
#include <tmxpp/Pixel.hpp>

namespace tmxpp {

template <class T>
struct Size {
    using Dimension = Positive<T>;

    Dimension w;
    Dimension h;
};

using pxSize = Size<Pixel>;
using iSize  = Size<int>;

template <class T>
inline bool operator==(Size<T> l, Size<T> r) noexcept
{
    return l.w == r.w && l.h == r.h;
}

template <class T>
inline bool operator!=(Size<T> l, Size<T> r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_SIZE_HPP
