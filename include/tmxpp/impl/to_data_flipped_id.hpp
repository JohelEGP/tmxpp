#ifndef TMXPP_IMPL_TO_DATA_FLIPPED_ID
#define TMXPP_IMPL_TO_DATA_FLIPPED_ID

#include <string_view>
#include <tmxpp/exceptions.hpp>
#include <tmxpp/impl/Raw_tile_id.hpp>
#include <tmxpp/impl/read_utility.hpp>

namespace tmxpp::impl {

auto to_data_flipped_id(std::string_view s)
{
    auto id{from_string<Raw_tile_id>(s)};

    if (!is_valid(id))
        throw Exception{"Invalid raw tile id."};

    return to_flipped(id);
}

} // namespace tmxpp::impl

#endif // TMXPP_IMPL_TO_DATA_FLIPPED_ID
