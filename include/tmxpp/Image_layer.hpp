#ifndef TMXPP_IMAGE_LAYER_HPP
#define TMXPP_IMAGE_LAYER_HPP

#include <optional>
#include <tmxpp/Image.hpp>
#include <tmxpp/Layer.hpp>

namespace tmxpp {

struct Image_layer : Layer {
    std::optional<Image> image;
};

inline bool operator==(const Image_layer& l, const Image_layer& r) noexcept
{
    return static_cast<const Layer&>(l) == static_cast<const Layer&>(r) &&
           l.image == r.image;
}

inline bool operator!=(const Image_layer& l, const Image_layer& r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_IMAGE_LAYER_HPP
