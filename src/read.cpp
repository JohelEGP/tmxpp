#include <chrono>
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

Offset read_tile_offset(Xml::Element element)
{
    auto tile_offset{element.optional_child(tmx_info::tile_offset)};

    if (!tile_offset)
        return {};

    return Offset{
        from_string<Offset::Coordinate>(value(*tile_offset, tile_offset_x)),
        from_string<Offset::Coordinate>(value(*tile_offset, tile_offset_y))};
}

namespace properties {

Property::Value read_value(Xml::Element property)
{
    auto value{optional_value(property, property_value)};

    if (!value)
        return std::string{get(property.value())};

    auto alternative{optional_value(property, property_alternative)};

    if (!alternative || *alternative == property_alternative_string)
        return std::string{get(*value)};
    if (*alternative == property_alternative_int)
        return from_string<int>(*value);
    if (*alternative == property_alternative_double)
        return from_string<double>(*value);
    if (*alternative == property_alternative_bool) {
        if (*value == property_value_true)
            return true;
        if (*value == property_value_false)
            return false;
        throw Exception{"Bad property bool value: " + std::string{get(*value)}};
    }
    if (*alternative == property_alternative_color)
        return to_color(*value);
    if (*alternative == property_alternative_file)
        return File{get(*value)};

    throw Invalid_attribute{property_alternative, *alternative};
}

std::string read_name(Xml::Element property)
{
    return std::string{get(value(property, property_name))};
}

Property read_property(Xml::Element property)
{
    return {read_name(property), read_value(property)};
}

Properties read_properties(Xml::Element element)
{
    auto properties{element.optional_child(tmx_info::properties)};

    if (!properties)
        return {};

    return transform<Properties>(properties->children(property), read_property);
}

} // namespace properties

using properties::read_properties;

namespace image {

File read_source(Xml::Element image)
{
    return get(value(image, image_source));
}

std::optional<Color> read_transparent(Xml::Element image)
{
    if (auto color{optional_value(image, image_transparent)})
        return to_color(*color);
    return {};
}

std::optional<pxSize> read_size(Xml::Element image)
{
    auto width{optional_value(image, size_width)};
    auto height{optional_value(image, size_height)};

    if (bool{width} != bool{height})
        throw Exception{"Expected image with both width and height, or none."};

    if (!width)
        return {};

    return pxSize{from_string<pxSize::Dimension>(*width),
                  from_string<pxSize::Dimension>(*height)};
}

Image read_image(Xml::Element image)
{
    return {read_source(image), read_transparent(image), read_size(image)};
}

} // namespace image

using image::read_image;

namespace animation {

Tile_id read_local_id(Xml::Element frame)
{
    return from_string<Tile_id>(value(frame, frame_local_id));
}

std::chrono::milliseconds read_duration(Xml::Element frame)
{
    return from_string<std::chrono::milliseconds>(value(frame, frame_duration));
}

Frame read_frame(Xml::Element frame)
{
    return {read_local_id(frame), read_duration(frame)};
}

Animation read_animation(Xml::Element element)
{
    auto animation{element.optional_child(tmx_info::animation)};

    if (!animation)
        return {};

    return transform<Animation>(element.children(frame), read_frame);
}

} // namespace animation

using animation::read_animation;

namespace tile_set {

Tile_id read_first_global_id(Xml::Element tile_set)
{
    return from_string<Tile_id>(value(tile_set, tile_set_first_global_id));
}

File read_tsx(Xml::Element tile_set)
{
    if (auto tsx{optional_value(tile_set, tile_set_tsx)})
        return get(*tsx);
    return {};
}

std::string read_name(Xml::Element tile_set)
{
    if (auto name{optional_value(tile_set, tile_set_name)})
        return std::string{get(*name)};
    return {};
}

int read_tile_count(Xml::Element tile_set)
{
    return from_string<int>(value(tile_set, tile_set_tile_count));
}

int read_columns(Xml::Element tile_set)
{
    return from_string<int>(value(tile_set, tile_set_columns));
}

Tile_id read_tile_local_id(Xml::Element tile)
{
    return from_string<Tile_id>(value(tile, tile_set_tile_local_id));
}

std::optional<Object_layer> read_tile_collision_shape(Xml::Element tile)
{
    return {};
}

namespace tile_set {

Pixel read_spacing(Xml::Element tile_set)
{
    if (auto spacing{optional_value(tile_set, tile_set_spacing)})
        return from_string<Pixel>(*spacing);
    return {};
}

Pixel read_margin(Xml::Element tile_set)
{
    if (auto margin{optional_value(tile_set, tile_set_margin)})
        return from_string<Pixel>(*margin);
    return {};
}

iSize read_size(Xml::Element tile_set)
{
    auto tile_count{read_tile_count(tile_set)};
    auto columns{read_columns(tile_set)};

    if (columns == 0)
        throw Exception{"Invalid columns value: 0"};

    return {columns, tile_count / columns};
}

Tile_set::Tile read_tile(Xml::Element tile)
{
    return {read_tile_local_id(tile), read_properties(tile),
            read_tile_collision_shape(tile), read_animation(tile)};
}

Tile_set::Tiles read_tiles(Xml::Element tile_set)
{
    return transform<Tile_set::Tiles>(
        tile_set.children(tile_set_tile), read_tile);
}

Tile_set read_tile_set(Xml::Element tile_set)
{
    return {read_first_global_id(tile_set),
            read_tsx(tile_set),
            read_name(tile_set),
            read_tile_size(tile_set),
            read_spacing(tile_set),
            read_margin(tile_set),
            read_size(tile_set),
            read_tile_offset(tile_set),
            read_properties(tile_set),
            read_image(tile_set.child(tmx_info::image)),
            read_tiles(tile_set)};
}

} // namespace tile_set

namespace image_collection {

Image_collection::Tile read_tile(Xml::Element tile)
{
    return {read_tile_local_id(tile), read_properties(tile),
            read_image(tile.child(tmx_info::image)),
            read_tile_collision_shape(tile), read_animation(tile)};
}

Image_collection::Tiles read_tiles(Xml::Element image_collection)
{
    return transform<Image_collection::Tiles>(
        image_collection.children(tile_set_tile), read_tile);
}

Image_collection read_image_collection(Xml::Element image_collection)
{
    return {read_first_global_id(image_collection),
            read_tsx(image_collection),
            read_name(image_collection),
            read_tile_size(image_collection),
            read_tile_count(image_collection),
            read_columns(image_collection),
            read_tile_offset(image_collection),
            read_properties(image_collection),
            read_tiles(image_collection)};
}

} // namespace image_collection

} // namespace tile_set

using tile_set::tile_set::read_tile_set;
using tile_set::image_collection::read_image_collection;

namespace map {

std::string read_version(Xml::Element map)
{
    return std::string{get(value(map, map_version))};
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
    auto render_order{optional_value(map, map_render_order)};

    if (!render_order || *render_order == map_render_order_right_down)
        return Map::Render_order::right_down;
    if (*render_order == map_render_order_right_up)
        return Map::Render_order::right_up;
    if (*render_order == map_render_order_left_down)
        return Map::Render_order::left_down;
    if (*render_order == map_render_order_left_up)
        return Map::Render_order::left_up;

    throw Invalid_attribute{map_render_order, *render_order};
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
    return {read_version(map),        read_orientation(map),
            read_render_order(map),   read_isize(map),
            read_tile_size(map),      read_background(map),
            read_next_unique_id(map), read_properties(map)};
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
