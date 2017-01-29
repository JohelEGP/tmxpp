#ifndef TMXPP_READ_HPP
#define TMXPP_READ_HPP

#include <string>
#include <tmxpp/Image_collection.hpp>
#include <tmxpp/Map.hpp>
#include <tmxpp/Tile_set.hpp>

namespace tmxpp {

Map read_tmx(const std::string& path);

Map::Tile_set read_tsx(const std::string& path);
Tile_set read_tile_set(const std::string& path);
Image_collection read_image_collection(const std::string& path);

} // namespace tmxpp

#endif // TMXPP_READ_HPP
