#include <fstream>
#include <variant>
#include <boost/hana/functional/overload.hpp>
#include <tmxpp.hpp>
#include <tmxpp/exceptions.hpp>
#include <tmxpp/impl/Xml.hpp>
#include <tmxpp/impl/tmx_info.hpp>
#include <tmxpp/impl/to_string_color.hpp>
#include <tmxpp/impl/write_utility.hpp>

namespace tmxpp {

namespace impl {
namespace {

using namespace tmx_info;

void write(iSize sz, Xml::Element elem)
{
    add(elem, size_width, to_string(sz.w));
    add(elem, size_height, to_string(sz.h));
}

void write_tile(pxSize sz, Xml::Element elem)
{
    add(elem, tile_size_width, to_string(sz.w));
    add(elem, tile_size_height, to_string(sz.h));
}

// Map -------------------------------------------------------------------------

void write(Map::Render_order ro, Xml::Element map)
{
    map.add(map_render_order, [ro] {
        switch (ro) {
        case Map::Render_order::right_down: return map_render_order_right_down;
        case Map::Render_order::right_up: return map_render_order_right_up;
        case Map::Render_order::left_down: return map_render_order_left_down;
        case Map::Render_order::left_up: return map_render_order_left_up;
        default: throw Exception{""};
        }
    }());
}

void write(Map::Staggered::Axis a, Xml::Element map)
{
    map.add(map_staggered_axis, [a] {
        switch (a) {
        case Map::Staggered::Axis::x: return map_staggered_axis_x;
        case Map::Staggered::Axis::y: return map_staggered_axis_y;
        default: throw Exception{""};
        }
    }());
}

void write(Map::Staggered::Index i, Xml::Element map)
{
    map.add(map_staggered_index, [i] {
        switch (i) {
        case Map::Staggered::Index::even: return map_staggered_index_even;
        case Map::Staggered::Index::odd: return map_staggered_index_odd;
        default: throw Exception{""};
        }
    }());
}

void write(Map::Staggered s, Xml::Element map)
{
    write(s.axis, map);
    write(s.index, map);
}

void write(Map::Hexagonal h, Xml::Element map)
{
    add(map, map_hexagonal_side_legth, to_string(h.side_length));
    write(static_cast<Map::Staggered>(h), map);
}

void write(
    Map::Orientation orient, Map::Render_order render_order, Xml::Element map)
{
    auto add = [=](Xml::Attribute::Value orient) {
        map.add(map_orientation, orient);

        write(render_order, map);
    };

    std::visit(
        boost::hana::overload(
            [=](Map::Orthogonal) { add(map_orthogonal); },
            [=](Map::Isometric) { add(map_isometric); },
            [=](Map::Staggered s) {
                add(map_staggered);
                write(s, map);
            },
            [=](Map::Hexagonal h) {
                add(map_hexagonal);
                write(h, map);
            }),
        orient);
}

void write(const Map& map, Xml::Element elem)
{
    add(elem, map_version, map.version);
    write(map.orientation, map.render_order, elem);
    write(map.size, elem);
    write_tile(map.general_tile_size, elem);
    if (auto bg{map.background})
        add(elem, map_background, to_string(*bg));
    add(elem, map_next_unique_id, to_string(map.next_unique_id));
}

} // namespace
} // namespace impl

void write(const Map& map, gsl::not_null<gsl::czstring<>> path)
{
    impl::Xml tmx{impl::tmx_info::map};

    impl::write(map, tmx.root());

    std::ofstream{path} << tmx;
}

void write(const Map::Tile_set&);
void write(const Tile_set&);
void write(const Image_collection&);

} // namespace tmxpp
