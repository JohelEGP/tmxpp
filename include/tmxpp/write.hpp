#ifndef TMXPP_WRITE_HPP
#define TMXPP_WRITE_HPP

#include <gsl/gsl>
#include <gsl/string_span>
#include <tmxpp/Image_collection.hpp>
#include <tmxpp/Map.hpp>
#include <tmxpp/Tile_set.hpp>

namespace tmxpp {

void write(const Map&, gsl::not_null<gsl::czstring<>> path);

void write(const Map::Tile_set&);
void write(const Tile_set&);
void write(const Image_collection&);

} // namespace tmxpp

#endif // TMXPP_WRITE_HPP
