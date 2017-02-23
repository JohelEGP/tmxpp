#ifndef TMXPP_IMPL_WRITE_POLY_HPP
#define TMXPP_IMPL_WRITE_POLY_HPP

#include <string>
#include <type_traits>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/intersperse.hpp>
#include <range/v3/view/transform.hpp>
#include <tmxpp/Object.hpp>
#include <tmxpp/impl/Xml.hpp>
#include <tmxpp/impl/tmx_info.hpp>
#include <tmxpp/impl/write_utility.hpp>

namespace tmxpp::impl {

template <class Poly>
std::enable_if_t<
    std::is_same_v<Poly, Object::Polygon> ||
    std::is_same_v<Poly, Object::Polyline>>
write(const Poly& p, Xml::Element obj)
{
    auto elem{obj.add(
        std::is_same_v<Poly, Object::Polygon> ? tmx_info::object_polygon
                                              : tmx_info::object_polyline)};

    auto points{p.points | ranges::view::transform([](auto pt) {
                    return to_string(pt.x) + ',' + to_string(pt.y);
                }) |
                ranges::view::intersperse(std::string{' '})};

    add(elem, tmx_info::object_polygon_points,
        ranges::accumulate(points, std::string{}));
}

} // namespace tmxpp::impl

#endif // TMXPP_IMPL_WRITE_POLY_HPP
