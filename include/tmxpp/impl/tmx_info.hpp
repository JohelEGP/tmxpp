#ifndef TMXPP_IMPL_TMX_INFO_HPP
#define TMXPP_IMPL_TMX_INFO_HPP

#include <string_view>
#include <tmxpp/impl/Xml.hpp>

namespace tmxpp::impl::tmx_info {

using namespace std::string_view_literals;

constexpr Xml::Attribute::Name size_width{"width"sv};
constexpr Xml::Attribute::Name size_height{"height"sv};
constexpr Xml::Attribute::Name tile_size_width{"tilewidth"sv};
constexpr Xml::Attribute::Name tile_size_height{"tileheight"sv};

constexpr Xml::Element::Name map{"map"sv};
constexpr Xml::Attribute::Name map_version{"version"sv};
constexpr Xml::Attribute::Name map_orientation{"orientation"sv};
constexpr Xml::Attribute::Value map_orthogonal{"orthogonal"sv};
constexpr Xml::Attribute::Value map_isometric{"isometric"sv};
constexpr Xml::Attribute::Value map_staggered{"staggered"sv};
constexpr Xml::Attribute::Value map_hexagonal{"hexagonal"sv};
constexpr Xml::Attribute::Name map_render_order{"renderorder"sv};
constexpr Xml::Attribute::Value map_render_order_right_down{"right-down"sv};
constexpr Xml::Attribute::Value map_render_order_right_up{"right-up"sv};
constexpr Xml::Attribute::Value map_render_order_left_down{"left-down"sv};
constexpr Xml::Attribute::Value map_render_order_left_up{"left-up"sv};
constexpr Xml::Attribute::Name map_hexagonal_side_legth{"hexsidelength"sv};
constexpr Xml::Attribute::Name map_staggered_axis{"staggeraxis"sv};
constexpr Xml::Attribute::Value map_staggered_axis_x{"x"sv};
constexpr Xml::Attribute::Value map_staggered_axis_y{"y"sv};
constexpr Xml::Attribute::Name map_staggered_index{"staggerindex"sv};
constexpr Xml::Attribute::Value map_staggered_index_even{"even"sv};
constexpr Xml::Attribute::Value map_staggered_index_odd{"odd"sv};
constexpr Xml::Attribute::Name map_background{"backgroundcolor"sv};
constexpr Xml::Attribute::Name map_next_unique_id{"nextobjectid"sv};

constexpr Xml::Element::Name tile_set{"tileset"sv};
constexpr Xml::Attribute::Name tile_set_first_global_id{"firstgid"sv};
constexpr Xml::Attribute::Name tile_set_tsx{"source"sv};
constexpr Xml::Attribute::Name tile_set_name{"name"sv};
constexpr Xml::Attribute::Name tile_set_spacing{"spacing"sv};
constexpr Xml::Attribute::Name tile_set_margin{"margin"sv};
constexpr Xml::Attribute::Name tile_set_tile_count{"tilecount"sv};
constexpr Xml::Attribute::Name tile_set_columns{"columns"sv};

constexpr Xml::Element::Name tile_offset{"tileoffset"sv};
constexpr Xml::Attribute::Name tile_offset_x{"x"sv};
constexpr Xml::Attribute::Name tile_offset_y{"y"sv};

constexpr Xml::Element::Name image{"image"sv};
constexpr Xml::Attribute::Name image_source{"source"sv};
constexpr Xml::Attribute::Name image_transparent{"source"sv};

constexpr Xml::Element::Name tile_set_tile{"tile"sv};
constexpr Xml::Attribute::Name tile_set_tile_local_id{"id"sv};

constexpr Xml::Element::Name animation{"animation"sv};

constexpr Xml::Element::Name frame{""sv};
constexpr Xml::Attribute::Name frame_local_id{"tileid"sv};
constexpr Xml::Attribute::Name frame_duration{"duration"sv};

constexpr Xml::Attribute::Name offset_x{"offsetx"sv};
constexpr Xml::Attribute::Name offset_y{"offsety"sv};

constexpr Xml::Attribute::Name layer_name{"name"sv};
constexpr Xml::Attribute::Name layer_opacity{"opacity"sv};
constexpr Xml::Attribute::Name layer_visible{"visible"sv};

constexpr Xml::Element::Name tile_layer{"layer"sv};

constexpr Xml::Element::Name data{"data"sv};
constexpr Xml::Attribute::Name data_encoding{"encoding"sv};
constexpr Xml::Attribute::Value data_encoding_csv{"csv"sv};
constexpr Xml::Attribute::Value data_encoding_base64{"base64"sv};
constexpr Xml::Attribute::Name data_compression{"compression"sv};
constexpr Xml::Attribute::Value data_compression_zlib{"zlib"sv};

constexpr Xml::Element::Name object_layer{"objectgroup"sv};
constexpr Xml::Attribute::Name object_layer_color{"color"sv};
constexpr Xml::Attribute::Name object_layer_draw_order{"offsety"sv};
constexpr Xml::Attribute::Value object_layer_draw_order_top_down{"topdown"sv};
constexpr Xml::Attribute::Value object_layer_draw_order_index{"index"sv};

constexpr Xml::Attribute::Name point_x{"x"sv};
constexpr Xml::Attribute::Name point_y{"y"sv};

constexpr Xml::Element::Name object{"object"sv};
constexpr Xml::Attribute::Name object_unique_id{"id"sv};
constexpr Xml::Attribute::Name object_name{"name"sv};
constexpr Xml::Attribute::Name object_type{"type"sv};
constexpr Xml::Attribute::Name object_clockwise_rotation{"rotation"sv};
constexpr Xml::Attribute::Name object_global_id{"gid"sv};
constexpr Xml::Attribute::Name object_visible{"visible"sv};

constexpr Xml::Element::Name object_ellipse{"ellipse"sv};

constexpr Xml::Element::Name object_polygon{"polygon"sv};
constexpr Xml::Attribute::Name object_polygon_points{"points"sv};

constexpr Xml::Element::Name object_polyline{"polyline"sv};
constexpr Xml::Attribute::Name object_polyline_points{"points"sv};

constexpr Xml::Element::Name image_layer{"imagelayer"sv};

constexpr Xml::Element::Name properties{"properties"sv};

constexpr Xml::Element::Name property{"property"sv};
constexpr Xml::Attribute::Name property_name{"name"sv};
constexpr Xml::Attribute::Name property_value{"value"sv};
constexpr Xml::Attribute::Value property_value_true{"true"sv};
constexpr Xml::Attribute::Value property_value_false{"false"sv};
constexpr Xml::Attribute::Name property_alternative{"type"sv};
constexpr Xml::Attribute::Value property_alternative_string{"string"sv};
constexpr Xml::Attribute::Value property_alternative_int{"int"sv};
constexpr Xml::Attribute::Value property_alternative_double{"float"sv};
constexpr Xml::Attribute::Value property_alternative_bool{"bool"sv};
constexpr Xml::Attribute::Value property_alternative_color{"color"sv};
constexpr Xml::Attribute::Value property_alternative_file{"file"sv};

} // namespace tmxpp::impl::tmx_info

#endif // TMXPP_IMPL_TMX_INFO_HPP
