#ifndef TMXPP_MAP_HPP
#define TMXPP_MAP_HPP

#include <optional>
#include <string>
#include <variant>
#include <vector>
#include <tmxpp/Color.hpp>
#include <tmxpp/Image_collection.hpp>
#include <tmxpp/Image_layer.hpp>
#include <tmxpp/Object_layer.hpp>
#include <tmxpp/Pixels.hpp>
#include <tmxpp/Properties.hpp>
#include <tmxpp/Size.hpp>
#include <tmxpp/Tile_layer.hpp>
#include <tmxpp/Tile_set.hpp>
#include <tmxpp/Unique_id.hpp>

namespace tmxpp {

struct Map {
    struct Orthogonal {
    };
    struct Isometric {
    };
    struct Staggered {
        enum class Axis : unsigned char { x, y };
        enum class Index : unsigned char { even, odd };
        Axis axis;
        Index index;
    };
    struct Hexagonal : Staggered {
        Pixels side_length;
    };

    using Orientation =
        std::variant<Orthogonal, Isometric, Staggered, Hexagonal>;

    enum class Render_order : unsigned char {
        right_down,
        right_up,
        left_down,
        left_up
    };

    using Tile_set  = std::variant<tmxpp::Tile_set, Image_collection>;
    using Tile_sets = std::vector<Tile_set>;

    using Layer  = std::variant<Tile_layer, Object_layer, Image_layer>;
    using Layers = std::vector<Layer>;

    std::string version;
    Orientation orientation;
    Render_order render_order;
    iSize size; // In tiles.
    pxSize general_tile_size;
    std::optional<Color> background;
    Unique_id next_id;
    Properties properties;
    Tile_sets tile_sets;
    Layers layers;
};

constexpr bool operator==(Map::Orthogonal, Map::Orthogonal) noexcept
{
    return true;
}
constexpr bool operator!=(Map::Orthogonal, Map::Orthogonal) noexcept
{
    return false;
}

constexpr bool operator==(Map::Isometric, Map::Isometric) noexcept
{
    return true;
}
constexpr bool operator!=(Map::Isometric, Map::Isometric) noexcept
{
    return false;
}

constexpr bool operator==(Map::Staggered l, Map::Staggered r) noexcept
{
    return l.axis == r.axis && l.index == r.index;
}
constexpr bool operator!=(Map::Staggered l, Map::Staggered r) noexcept
{
    return !(l == r);
}

constexpr bool operator==(Map::Hexagonal l, Map::Hexagonal r) noexcept
{
    return static_cast<Map::Staggered>(l) == static_cast<Map::Staggered>(r) &&
           l.side_length == r.side_length;
}
constexpr bool operator!=(Map::Hexagonal l, Map::Hexagonal r) noexcept
{
    return !(l == r);
}

inline bool operator==(const Map& l, const Map& r) noexcept
{
    return l.version == r.version && l.orientation == r.orientation &&
           l.render_order == r.render_order && l.size == r.size &&
           l.general_tile_size == r.general_tile_size &&
           l.background == r.background && l.next_id == r.next_id &&
           l.properties == r.properties && l.tile_sets == r.tile_sets &&
           l.layers == r.layers;
}
inline bool operator!=(const Map& l, const Map& r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_MAP_HPP
