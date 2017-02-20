#ifndef TMXPP_IMPL_TO_POINT_HPP
#define TMXPP_IMPL_TO_POINT_HPP

#include <string>
#include <string_view>
#include <range/v3/begin_end.hpp>
#include <range/v3/view/bounded.hpp>
#include <range/v3/view/transform.hpp>
#include <tmxpp/Point.hpp>
#include <tmxpp/exceptions.hpp>
#include <tmxpp/impl/read_utility.hpp>

namespace tmxpp::impl {

Point to_point(std::string_view point) try {
    auto coordinates{tokenize(point, ",")};
    auto range{coordinates |
               ranges::view::transform([](std::string_view coordinate) {
                   return from_string<Point::Coordinate>(coordinate);
               }) |
               ranges::view::bounded};

    std::vector<Point::Coordinate> xy{ranges::begin(range), ranges::end(range)};

    if (xy.size() != 2)
        throw Exception{"Bad poly point: " + std::string{point}};

    return {xy[0], xy[1]};
}
catch (const Exception& e) {
    throw Exception{"Bad poly point: " + std::string{point} + ". " + e.what()};
}

} // namespace tmxpp::impl

#endif // TMXPP_IMPL_TO_POINT_HPP
