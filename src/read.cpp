#include <optional>
#include <string>
#include <tmxpp.hpp>
#include <tmxpp/impl/Xml.hpp>
#include <tmxpp/impl/exceptions.hpp>
#include <tmxpp/impl/read_utility.hpp>
#include <tmxpp/impl/tmx_info.hpp>
#include <tmxpp/impl/to_color.hpp>

namespace tmxpp {

namespace impl {
namespace {

using namespace tmx_info;

iSize read_isize(Xml::Element element)
{
    return iSize{from_string<iSize::Dimension>(value(element, size_width)),
                 from_string<iSize::Dimension>(value(element, size_height))};
}

pxSize read_tile_size(Xml::Element element)
{
    return pxSize{
        from_string<pxSize::Dimension>(value(element, tile_size_width)),
        from_string<pxSize::Dimension>(value(element, tile_size_height))};
}

namespace map {

std::string read_version(Xml::Element map)
{
    return std::string{get(value(map, tmx_info::map_version))};
}

Map::Staggered::Axis read_axis(Xml::Element map)
{
    auto axis{value(map, map_staggered_axis)};

    if (axis == map_staggered_axis_x)
        return Map::Staggered::Axis::x;
    if (axis == map_staggered_axis_y)
        return Map::Staggered::Axis::y;

    throw Invalid_attribute{map_staggered_axis, axis};
}

Map::Staggered::Index read_index(Xml::Element map)
{
    auto index{value(map, map_staggered_index)};

    if (index == map_staggered_index_even)
        return Map::Staggered::Index::even;
    if (index == map_staggered_index_odd)
        return Map::Staggered::Index::odd;

    throw Invalid_attribute{map_staggered_index, index};
}

Pixel read_side_length(Xml::Element map)
{
    return from_string<Pixel>(value(map, map_hexagonal_side_legth));
}

Map::Orientation read_orientation(Xml::Element map)
{
    auto orientation{value(map, map_orientation)};

    if (orientation == map_orthogonal)
        return Map::Orthogonal{};
    if (orientation == map_isometric)
        return Map::Isometric{};
    if (orientation == map_staggered)
        return Map::Staggered{read_axis(map), read_index(map)};
    if (orientation == map_hexagonal)
        return Map::Hexagonal{read_axis(map), read_index(map),
                              read_side_length(map)};

    throw Invalid_attribute{map_orientation, orientation};
}

Map::Render_order read_render_order(Xml::Element map)
{
    auto render_order{value(map, map_render_order)};

    if (render_order == map_render_order_right_down)
        return Map::Render_order::right_down;
    if (render_order == map_render_order_right_up)
        return Map::Render_order::right_up;
    if (render_order == map_render_order_left_down)
        return Map::Render_order::left_down;
    if (render_order == map_render_order_left_up)
        return Map::Render_order::left_up;

    throw Invalid_attribute{map_render_order, render_order};
}

std::optional<Color> read_background(Xml::Element map)
{
    if (auto color{optional_value(map, map_background)})
        return to_color(*color);
    return {};
}

Unique_id read_next_unique_id(Xml::Element map)
{
    return from_string<Unique_id>(value(map, map_next_unique_id));
}

Map read_map(Xml::Element map)
{
    return {read_version(map),       read_orientation(map),
            read_render_order(map),  read_isize(map),
            read_tile_size(map),     read_background(map),
            read_next_unique_id(map)};
}

} // namespace map

using map::read_map;

} // namespace
} // namespace impl

Map read_tmx(const std::string& path)
{
    const impl::Xml tmx{path};

    auto map{tmx.root()};

    if (map.name() == impl::tmx_info::map)
        return impl::read_map(map);

    throw impl::Invalid_element{map.name()};
}

Map::Tile_set read_tsx(const std::string& path);
Tile_set read_tile_set(const std::string& path);
Image_collection read_image_collection(const std::string& path);

} // namespace tmxpp
