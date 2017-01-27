#ifndef TMXPP_IMAGE_COLLECTION_HPP
#define TMXPP_IMAGE_COLLECTION_HPP

#include <optional>
#include <string>
#include <vector>
#include <tmxpp/Animation.hpp>
#include <tmxpp/File.hpp>
#include <tmxpp/Image.hpp>
#include <tmxpp/Object_layer.hpp>
#include <tmxpp/Offset.hpp>
#include <tmxpp/Properties.hpp>
#include <tmxpp/Size.hpp>
#include <tmxpp/Tile_id.hpp>

namespace tmxpp {

struct Image_collection {
    struct Tile {
        Tile_id id;
        Properties properties;
        Image image;
        std::optional<Object_layer> collision_shape;
        Animation animation;
    };

    using Tiles = std::vector<Tile>;

    Tile_id first_gid;
    File tsx;
    std::string name;
    pxSize max_tile_size;
    int tile_count;
    int columns;
    Offset tile_offset;
    Properties properties;
    Tiles tiles;
};

inline bool operator==(
    const Image_collection::Tile& l, const Image_collection::Tile& r) noexcept
{
    return l.id == r.id && l.properties == r.properties && l.image == r.image &&
           l.collision_shape == r.collision_shape && l.animation == r.animation;
}
inline bool operator!=(
    const Image_collection::Tile& l, const Image_collection::Tile& r) noexcept
{
    return !(l == r);
}

inline bool
operator==(const Image_collection& l, const Image_collection& r) noexcept
{
    return l.first_gid == r.first_gid && l.tsx == r.tsx && l.name == r.name &&
           l.max_tile_size == r.max_tile_size && l.tile_count == r.tile_count &&
           l.columns == r.columns && l.tile_offset == r.tile_offset &&
           l.properties == r.properties && l.tiles == r.tiles;
}
inline bool
operator!=(const Image_collection& l, const Image_collection& r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_IMAGE_COLLECTION_HPP
