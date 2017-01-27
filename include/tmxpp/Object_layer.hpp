#ifndef TMXPP_OBJECT_LAYER_HPP
#define TMXPP_OBJECT_LAYER_HPP

#include <optional>
#include <vector>
#include <tmxpp/Color.hpp>
#include <tmxpp/Layer.hpp>
#include <tmxpp/Object.hpp>

namespace tmxpp {

struct Object_layer : Layer {
    enum class Draw_order : unsigned char { top_down, index };

    using Objects = std::vector<Object>;

    std::optional<Color> color;
    Draw_order draw_order;
    Objects objects;
};

inline bool operator==(const Object_layer& l, const Object_layer& r) noexcept
{
    return static_cast<const Layer&>(l) == static_cast<const Layer&>(r) &&
           l.color == r.color && l.draw_order == r.draw_order &&
           l.objects == r.objects;
}

inline bool operator!=(const Object_layer& l, const Object_layer& r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_OBJECT_LAYER_HPP
