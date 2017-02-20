#ifndef TMXPP_WRITE_HPP
#define TMXPP_WRITE_HPP

#include <gsl/gsl>
#include <gsl/string_span>
#include <tmxpp/Image_collection.hpp>
#include <tmxpp/Map.hpp>
#include <tmxpp/Tile_set.hpp>

namespace tmxpp {

void write(const Map&, gsl::not_null<gsl::czstring<>> path);

void write(const Map::Tile_set&, gsl::not_null<gsl::czstring<>> path);
void write(const Tile_set&, gsl::not_null<gsl::czstring<>> path);
void write(const Image_collection&, gsl::not_null<gsl::czstring<>> path);

} // namespace tmxpp

#endif // TMXPP_WRITE_HPP
