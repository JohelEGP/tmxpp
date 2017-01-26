#ifndef TMXPP_TILE_SET_HPP
#define TMXPP_TILE_SET_HPP

// #include <optional>
#include <string>
#include <vector>
#include <tmxpp/Animation.hpp>
#include <tmxpp/File.hpp>
#include <tmxpp/Image.hpp>
// #include <tmxpp/Object_layer.hpp>
#include <tmxpp/Offset.hpp>
#include <tmxpp/Pixel.hpp>
#include <tmxpp/Properties.hpp>
#include <tmxpp/Size.hpp>
#include <tmxpp/Tile_id.hpp>

namespace tmxpp {

struct Tile_set {
    struct Tile {
        Tile_id id;
        Properties properties;
        // std::optional<Object_layer> collision_shape;
        Animation animation;
    };

    using Tiles = std::vector<Tile>;

    Tile_id first_gid;
    File tsx;
    std::string name;
    pxSize tile_size;
    Pixel spacing;
    Pixel margin;
    iSize size;
    Offset tile_offset;
    Properties properties;
    Image image;
    Tiles tiles;
};

} // namespace tmxpp

#endif // TMXPP_TILE_SET_HPP
