#ifndef TMXPP_TILE_LAYER_HPP
#define TMXPP_TILE_LAYER_HPP

#include <tmxpp/Data.hpp>
#include <tmxpp/Layer.hpp>

namespace tmxpp {

struct Tile_layer : Layer {
    Data data;
};

inline bool operator==(const Tile_layer& l, const Tile_layer& r) noexcept
{
    return static_cast<const Layer&>(l) == static_cast<const Layer&>(r) &&
           l.data == r.data;
}

inline bool operator!=(const Tile_layer& l, const Tile_layer& r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_TILE_LAYER_HPP
