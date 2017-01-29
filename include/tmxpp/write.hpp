#ifndef TMXPP_WRITE_HPP
#define TMXPP_WRITE_HPP

#include <string>
#include <tmxpp/Image_collection.hpp>
#include <tmxpp/Map.hpp>
#include <tmxpp/Tile_set.hpp>

namespace tmxpp {

void write(const Map&, const std::string& path);

void write(const Map::Tile_set&, const std::string& path);
void write(const Tile_set&, const std::string& path);
void write(const Image_collection&, const std::string& path);

} // namespace tmxpp

#endif // TMXPP_WRITE_HPP
