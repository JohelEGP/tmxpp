#include <fstream>
#include <string>
#include <type_traits>
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

template <class Number>
void write(Size<Number> sz, Xml::Element elem)
{
    add(elem, size_width, sz.w);
    add(elem, size_height, sz.h);
}

void write_tile(pxSize sz, Xml::Element elem)
{
    add(elem, tile_size_width, sz.w);
    add(elem, tile_size_height, sz.h);
}

// Properties ------------------------------------------------------------------

void write(const Property::Value& value, Xml::Element prop)
{
    auto add = [=](Xml::Attribute::Value alternative, auto value) {
        prop.add(property_alternative, alternative);
        impl::add(prop, property_value, value);
    };

    std::visit(
        boost::hana::overload(
            [=](int i) { add(property_alternative_int, i); },
            [=](double d) { add(property_alternative_double, d); },
            [=](bool b) {
                add(property_alternative_bool,
                    get(b ? property_value_true : property_value_false));
            },
            [=](Color c) { add(property_alternative_color, c); },
            [=](File f) { add(property_alternative_file, f.string()); },
            [=](const std::string& s) {
                prop.add(property_alternative, property_alternative_string);

                if (bool is_multiline{s.find('\n') != std::string::npos})
                    prop.value(Xml::Element::Value{s});
                else
                    impl::add(prop, property_value, s);
            }),
        value);
}

void write(const Property& p, Xml::Element elem)
{
    add(elem, property_name, p.name);
    write(p.value, elem);
}

void write(const Properties& ps, Xml::Element parent)
{
    if (ps.empty())
        return;

    auto elem{parent.add(properties)};

    for (const auto& p : ps)
        write(p, elem.add(property));
}

// Image -----------------------------------------------------------------------

void write(const Image& img, Xml::Element elem)
{
    add(elem, image_source, img.source.string());
    if (auto trans{img.transparent})
        add(elem, image_transparent, *trans);
    if (auto sz{img.size})
        write(*sz, elem);
}

// Map::Tile_set ---------------------------------------------------------------

void write_tile(Offset o, Xml::Element parent)
{
    if (o == Offset{})
        return;

    auto elem{parent.add(tile_offset)};

    add(elem, tile_offset_x, o.x);
    add(elem, tile_offset_y, o.y);
}

void write(const Map::Tile_set& ts, Xml::Element elem)
{
    std::visit(
        [elem](const auto& ts) {
            add(elem, tile_set_first_global_id, ts.first_global_id);
            if (!ts.tsx.empty())
                add(elem, tile_set_tsx, ts.tsx.string());
            add(elem, tile_set_name, ts.name);
            if
                constexpr(std::is_same_v<std::decay_t<decltype(ts)>, Tile_set>)
                {
                    write_tile(ts.tile_size, elem);
                    if (ts.spacing != Pixel{0})
                        add(elem, tile_set_spacing, ts.spacing);
                    if (ts.margin != Pixel{0})
                        add(elem, tile_set_margin, ts.margin);
                    add(elem, tile_set_tile_count, ts.size.w * ts.size.h);
                    add(elem, tile_set_columns, ts.size.w);
                }
            else {
                write_tile(ts.max_tile_size, elem);
                add(elem, tile_set_tile_count, ts.tile_count);
                add(elem, tile_set_columns, ts.columns);
            };
            write_tile(ts.tile_offset, elem);
            write(ts.properties, elem);
            if
                constexpr(std::is_same_v<std::decay_t<decltype(ts)>, Tile_set>)
                    write(ts.image, elem.add(image));
        },
        ts);
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
    add(map, map_hexagonal_side_legth, h.side_length);
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

void write(const Map::Tile_sets& tses, Xml::Element map)
{
    for (const auto& ts : tses)
        write(ts, map.add(tile_set));
}

void write(const Map& map, Xml::Element elem)
{
    add(elem, map_version, map.version);
    write(map.orientation, map.render_order, elem);
    write(map.size, elem);
    write_tile(map.general_tile_size, elem);
    if (auto bg{map.background})
        add(elem, map_background, *bg);
    add(elem, map_next_unique_id, map.next_unique_id);
    write(map.properties, elem);
    write(map.tile_sets, elem);
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
