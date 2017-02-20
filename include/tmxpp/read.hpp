#ifndef TMXPP_READ_HPP
#define TMXPP_READ_HPP

#include <gsl/gsl>
#include <gsl/string_span>
#include <tmxpp/Image_collection.hpp>
#include <tmxpp/Map.hpp>
#include <tmxpp/Tile_set.hpp>

namespace tmxpp {

Map read_tmx(gsl::not_null<gsl::czstring<>> path);

Map::Tile_set read_tsx(gsl::not_null<gsl::czstring<>> path);
Tile_set read_tile_set(gsl::not_null<gsl::czstring<>> path);
Image_collection read_image_collection(gsl::not_null<gsl::czstring<>> path);

} // namespace tmxpp

#endif // TMXPP_READ_HPP
