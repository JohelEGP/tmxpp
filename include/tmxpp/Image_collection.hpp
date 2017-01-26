#ifndef TMXPP_IMAGE_COLLECTION_HPP
#define TMXPP_IMAGE_COLLECTION_HPP

// #include <optional>
#include <string>
#include <vector>
#include <tmxpp/Animation.hpp>
#include <tmxpp/File.hpp>
#include <tmxpp/Image.hpp>
// #include <tmxpp/Object_layer.hpp>
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
        // std::optional<Object_layer> collision_shape;
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

} // namespace tmxpp

#endif // TMXPP_IMAGE_COLLECTION_HPP
