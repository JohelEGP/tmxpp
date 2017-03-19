#ifndef TMXPP_WRITE_HPP
#define TMXPP_WRITE_HPP

#include <experimental/filesystem>
#include <type_traits>
#include <tmxpp/Image_collection.hpp>
#include <tmxpp/Map.hpp>
#include <tmxpp/Tile_set.hpp>

namespace tmxpp {

void write(const Map&, const std::experimental::filesystem::path&);

template <class Tile_set_>
std::enable_if_t<
    std::is_same_v<Tile_set_, Map::Tile_set> ||
    std::is_same_v<Tile_set_, Tile_set> ||
    std::is_same_v<Tile_set_, Image_collection>>
write(
    const Tile_set_&, const std::experimental::filesystem::path& base =
                          std::experimental::filesystem::current_path());

} // namespace tmxpp

#endif // TMXPP_WRITE_HPP
