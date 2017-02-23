#ifndef TMXPP_WRITE_HPP
#define TMXPP_WRITE_HPP

#include <type_traits>
#include <gsl/gsl>
#include <gsl/string_span>
#include <tmxpp/Image_collection.hpp>
#include <tmxpp/Map.hpp>
#include <tmxpp/Tile_set.hpp>

namespace tmxpp {

void write(const Map&, gsl::not_null<gsl::czstring<>> path);

template <class Tile_set_>
std::enable_if_t<
    std::is_same_v<Tile_set_, Map::Tile_set> ||
    std::is_same_v<Tile_set_, Tile_set> ||
    std::is_same_v<Tile_set_, Image_collection>>
write(const Tile_set_&);

} // namespace tmxpp

#endif // TMXPP_WRITE_HPP
