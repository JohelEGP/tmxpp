#ifndef TMXPP_READ_HPP
#define TMXPP_READ_HPP

#include <experimental/filesystem>
#include <tmxpp/File.hpp>
#include <tmxpp/Image_collection.hpp>
#include <tmxpp/Map.hpp>
#include <tmxpp/Tile_id.hpp>
#include <tmxpp/Tile_set.hpp>

namespace tmxpp {

Map read_tmx(const std::experimental::filesystem::path&);

Map::Tile_set read_tsx(
    Global_tile_id first_id, File tsx,
    const std::experimental::filesystem::path& base =
        std::experimental::filesystem::current_path());
Tile_set read_tile_set(
    Global_tile_id first_id, File tsx,
    const std::experimental::filesystem::path& base =
        std::experimental::filesystem::current_path());
Image_collection read_image_collection(
    Global_tile_id first_id, File tsx,
    const std::experimental::filesystem::path& base =
        std::experimental::filesystem::current_path());

} // namespace tmxpp

#endif // TMXPP_READ_HPP
