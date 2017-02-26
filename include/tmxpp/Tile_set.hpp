#ifndef TMXPP_TILE_SET_HPP
#define TMXPP_TILE_SET_HPP

#include <optional>
#include <string>
#include <vector>
#include <tmxpp/Animation.hpp>
#include <tmxpp/Constrained.hpp>
#include <tmxpp/File.hpp>
#include <tmxpp/Image.hpp>
#include <tmxpp/Object_layer.hpp>
#include <tmxpp/Offset.hpp>
#include <tmxpp/Pixel.hpp>
#include <tmxpp/Properties.hpp>
#include <tmxpp/Size.hpp>
#include <tmxpp/Tile_id.hpp>

namespace tmxpp {

struct Tile_set {
    struct Tile {
        Local_tile_id id;
        Properties properties;
        std::optional<Object_layer> collision_shape;
        Animation animation;
    };

    using Tiles = std::vector<Tile>;

    Global_tile_id first_id;
    File tsx;
    std::string name;
    pxSize tile_size;
    Non_negative<Pixel> spacing;
    Non_negative<Pixel> margin;
    iSize size; // In tiles.
    Offset tile_offset;
    Properties properties;
    Image image;
    Tiles tiles;
};

inline bool
operator==(const Tile_set::Tile& l, const Tile_set::Tile& r) noexcept
{
    return l.id == r.id && l.properties == r.properties &&
           l.collision_shape == r.collision_shape && l.animation == r.animation;
}
inline bool
operator!=(const Tile_set::Tile& l, const Tile_set::Tile& r) noexcept
{
    return !(l == r);
}

inline bool operator==(const Tile_set& l, const Tile_set& r) noexcept
{
    return l.first_id == r.first_id && l.tsx == r.tsx && l.name == r.name &&
           l.tile_size == r.tile_size && l.spacing == r.spacing &&
           l.margin == r.margin && l.size == r.size &&
           l.tile_offset == r.tile_offset && l.properties == r.properties &&
           l.image == r.image && l.tiles == r.tiles;
}
inline bool operator!=(const Tile_set& l, const Tile_set& r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_TILE_SET_HPP
