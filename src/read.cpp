#include <optional>
#include <string>
#include <tmxpp.hpp>
#include <tmxpp/impl/Xml.hpp>
#include <tmxpp/impl/exceptions.hpp>
#include <tmxpp/impl/read_utility.hpp>
#include <tmxpp/impl/tmx_info.hpp>
#include <tmxpp/impl/to_color.hpp>
#include <tmxpp/impl/to_flipped_global_id.hpp>
#include <tmxpp/impl/to_point.hpp>

namespace tmxpp {

namespace impl {
namespace {

using namespace tmx_info;

pxSize read_tile_size(Xml::Element element)
{
    return pxSize{
        from_string<pxSize::Dimension>(value(element, tile_size_width)),
        from_string<pxSize::Dimension>(value(element, tile_size_height))};
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

Frame::Duration read_duration(Xml::Element frame)
{
    return from_string<Frame::Duration>(value(frame, frame_duration));
}

Frame read_frame(Xml::Element frame)
{
    return {read_local_id(frame), read_duration(frame)};
}

Animation read_animation(Xml::Element tile)
{
    auto animation{tile.optional_child(tmx_info::animation)};

    if (!animation)
        return {};

    return transform<Animation>(tile.children(frame), read_frame);
}

} // namespace animation

using animation::read_animation;

namespace object_layer {

Object_layer read_object_layer(Xml::Element object_layer);

} // namespace object_layer

using object_layer::read_object_layer;

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

Offset read_tile_offset(Xml::Element tile_set)
{
    auto tile_offset{tile_set.optional_child(tmx_info::tile_offset)};

    if (!tile_offset)
        return {};

    return Offset{
        from_string<Offset::Coordinate>(value(*tile_offset, tile_offset_x)),
        from_string<Offset::Coordinate>(value(*tile_offset, tile_offset_y))};
}

Tile_id read_tile_local_id(Xml::Element tile)
{
    return from_string<Tile_id>(value(tile, tile_set_tile_local_id));
}

std::optional<Object_layer> read_tile_collision_shape(Xml::Element tile)
{
    if (auto collision_shape{tile.optional_child(tmx_info::object_layer)})
        return read_object_layer(*collision_shape);
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

namespace data {

Data::Encoding read_encoding(Xml::Element data)
{
    auto encoding{value(data, data_encoding)};

    if (encoding == data_encoding_csv)
        return Data::Encoding::csv;
    if (encoding == data_encoding_base64)
        return Data::Encoding::base64;

    throw Invalid_attribute{data_encoding, encoding};
}

Data::Compression read_compression(Xml::Element data)
{
    auto compression{optional_value(data, data_compression)};

    if (!compression)
        return Data::Compression::none;
    if (*compression == data_compression_zlib)
        return Data::Compression::zlib;

    throw Invalid_attribute{data_compression, *compression};
}

Data::Flipped_global_ids read_flipped_global_ids(
    Data::Encoding encoding, Data::Compression compression,
    Xml::Element::Value data)
{
    if (encoding != Data::Encoding::csv &&
        compression != Data::Compression::none)
        throw Exception{"Can only handle csv-encoded data."};

    return transform<Data::Flipped_global_ids>(
        tokenize(get(data), ",\n"), to_flipped_global_id);
}

Data read_data(Xml::Element data)
{
    auto encoding{read_encoding(data)};
    auto compression{read_compression(data)};

    return {encoding, compression,
            read_flipped_global_ids(encoding, compression, data.value())};
}

} // namespace data

using data::read_data;

namespace layer {

std::string read_name(Xml::Element layer)
{
    if (auto name{optional_value(layer, layer_name)})
        return std::string{get(*name)};
    return {};
}

Unit_interval read_opacity(Xml::Element layer)
{
    if (auto opacity{optional_value(layer, layer_opacity)})
        return from_string<Unit_interval>(*opacity);
    return Unit_interval{1};
}

bool read_visible(Xml::Element layer)
{
    if (auto visible{optional_value(layer, layer_visible)})
        return from_string<bool>(*visible);
    return true;
}

Offset read_offset(Xml::Element layer)
{
    auto x{optional_value(layer, offset_x)};
    auto y{optional_value(layer, offset_y)};

    return Offset{x ? from_string<Offset::Coordinate>(*x) : Pixel{0},
                  y ? from_string<Offset::Coordinate>(*y) : Pixel{0}};
}

Layer read_layer(Xml::Element layer)
{
    return {read_name(layer), read_opacity(layer), read_visible(layer),
            read_offset(layer), read_properties(layer)};
}

} // namespace layer

using layer::read_layer;

namespace tile_layer {

Tile_layer read_tile_layer(Xml::Element tile_layer)
{
    return {read_layer(tile_layer),
            read_data(tile_layer.child(tmx_info::data))};
}

} // namespace tile_layer

using tile_layer::read_tile_layer;

namespace object {

Unique_id read_unique_id(Xml::Element object)
{
    return from_string<Unique_id>(value(object, object_unique_id));
}

std::string read_name(Xml::Element object)
{
    if (auto name{optional_value(object, object_name)})
        return std::string{get(*name)};
    return {};
}

std::string read_type(Xml::Element object)
{
    if (auto type{optional_value(object, object_type)})
        return std::string{get(*type)};
    return {};
}

Point read_position(Xml::Element object)
{
    return Point{from_string<Pixel>(value(object, point_x)),
                 from_string<Pixel>(value(object, point_y))};
}

Object::Polygon::Points read_points(Xml::Element poly)
{
    return transform<Object::Polygon::Points>(
        tokenize(get(value(poly, object_polygon_points)), " "), to_point);
}

pxSize read_size(Xml::Element object)
{
    auto w{optional_value(object, size_width)};
    auto h{optional_value(object, size_height)};

    if (!w && !h)
        return {};

    return {w ? from_string<pxSize::Dimension>(*w) : Pixel{0},
            h ? from_string<pxSize::Dimension>(*h) : Pixel{0}};
}

Object::Shape read_shape(Xml::Element object)
{
    if (auto polyline{object.optional_child(object_polyline)})
        return Object::Polyline{read_points(*polyline)};

    if (auto polygon{object.optional_child(object_polygon)})
        return Object::Polygon{read_points(*polygon)};

    if (object.optional_child(object_ellipse))
        return Object::Ellipse{read_size(object)};

    return Object::Rectangle{read_size(object)};
}

Degrees read_clockwise_rotation(Xml::Element object)
{
    if (auto rotation{optional_value(object, object_clockwise_rotation)})
        return from_string<Degrees>(*rotation);
    return {};
}

Tile_id read_global_id(Xml::Element object)
{
    if (auto global_id{optional_value(object, object_global_id)})
        return from_string<Tile_id>(*global_id);
    return {};
}

bool read_visible(Xml::Element object)
{
    return layer::read_visible(object);
}

Object read_object(Xml::Element object)
{
    return {read_unique_id(object), read_name(object),
            read_type(object),      read_position(object),
            read_shape(object),     read_clockwise_rotation(object),
            read_global_id(object), read_visible(object),
            read_properties(object)};
}

} // namespace object

using object::read_object;

namespace object_layer {

std::optional<Color> read_color(Xml::Element object_layer)
{
    if (auto color{optional_value(object_layer, object_layer_color)})
        return to_color(*color);
    return {};
}

Object_layer::Draw_order read_draw_order(Xml::Element object_layer)
{
    auto draw_order{optional_value(object_layer, object_layer_draw_order)};

    if (!draw_order || *draw_order == object_layer_draw_order_top_down)
        return Object_layer::Draw_order::top_down;
    if (*draw_order == object_layer_draw_order_index)
        return Object_layer::Draw_order::index;

    throw Invalid_attribute{object_layer_draw_order, *draw_order};
}

Object_layer::Objects read_objects(Xml::Element object_layer)
{
    return transform<Object_layer::Objects>(
        object_layer.children(tmx_info::object), read_object);
}

Object_layer read_object_layer(Xml::Element object_layer)
{
    return {read_layer(object_layer), read_color(object_layer),
            read_draw_order(object_layer), read_objects(object_layer)};
}

} // namespace object_layer

namespace image_layer {

std::optional<Image> read_image(Xml::Element image_layer)
{
    if (auto image{image_layer.optional_child(tmx_info::image)})
        return impl::read_image(*image);
    return {};
}

Image_layer read_image_layer(Xml::Element image_layer)
{
    return {read_layer(image_layer), read_image(image_layer)};
}

} // namespace image_layer

using image_layer::read_image_layer;

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

iSize read_size(Xml::Element map)
{
    return iSize{from_string<iSize::Dimension>(value(map, size_width)),
                 from_string<iSize::Dimension>(value(map, size_height))};
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

// Returns: `true` if the `Element` represents a `tmxpp::Tile_set`, and `false`
//          if it represents an `Image_collection`.
bool is_tmxpp_tile_set(Xml::Element tile_set)
{
    return bool{tile_set.optional_child(tmx_info::image)};
}

Map::Tile_set read_tile_set(Xml::Element tile_set)
{
    if (is_tmxpp_tile_set(tile_set))
        return impl::read_tile_set(tile_set);
    return read_image_collection(tile_set);
}

Map::Tile_sets read_tile_sets(Xml::Element map)
{
    return transform<Map::Tile_sets>(
        map.children(tmx_info::tile_set), read_tile_set);
}

Map::Layer read_layer(Xml::Element layer)
{
    auto name{layer.name()};

    if (name == tmx_info::tile_layer)
        return read_tile_layer(layer);
    if (name == tmx_info::object_layer)
        return read_object_layer(layer);
    if (name == tmx_info::image_layer)
        return read_image_layer(layer);

    throw Invalid_element{name};
}

Map::Layers read_layers(Xml::Element map)
{
    return transform<Map::Layers>(
        children(
            map, {tmx_info::tile_layer, tmx_info::object_layer,
                  tmx_info::image_layer}),
        read_layer);
}

Map read_map(Xml::Element map)
{
    return {read_version(map),        read_orientation(map),
            read_render_order(map),   read_size(map),
            read_tile_size(map),      read_background(map),
            read_next_unique_id(map), read_properties(map),
            read_tile_sets(map),      read_layers(map)};
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
