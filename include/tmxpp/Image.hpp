#ifndef TMXPP_IMAGE_HPP
#define TMXPP_IMAGE_HPP

#include <optional>
#include <tmxpp/Color.hpp>
#include <tmxpp/File.hpp>
#include <tmxpp/Size.hpp>

namespace tmxpp {

struct Image {
    File source;
    std::optional<Color> transparent;
    std::optional<pxSize> size;
};

inline bool operator==(const Image& l, const Image& r) noexcept
{
    return l.source == r.source && l.transparent == r.transparent &&
           l.size == r.size;
}

inline bool operator!=(const Image& l, const Image& r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_IMAGE_HPP
