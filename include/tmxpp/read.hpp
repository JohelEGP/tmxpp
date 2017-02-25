#ifndef TMXPP_READ_HPP
#define TMXPP_READ_HPP

#include <gsl/gsl>
#include <gsl/string_span>
#include <tmxpp/File.hpp>
#include <tmxpp/Image_collection.hpp>
#include <tmxpp/Map.hpp>
#include <tmxpp/Tile_id.hpp>
#include <tmxpp/Tile_set.hpp>

namespace tmxpp {

Map read_tmx(gsl::not_null<gsl::czstring<>> path);

Map::Tile_set read_tsx(Global_tile_id first_id, File tsx);
Tile_set read_tile_set(Global_tile_id first_id, File tsx);
Image_collection read_image_collection(Global_tile_id first_id, File tsx);

} // namespace tmxpp

#endif // TMXPP_READ_HPP
