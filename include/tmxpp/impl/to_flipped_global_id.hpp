#ifndef TMXPP_IMPL_TO_FLIPPED_GLOBAL_ID
#define TMXPP_IMPL_TO_FLIPPED_GLOBAL_ID

#include <cstdint>
#include <optional>
#include <string_view>
#include <tmxpp/Flip.hpp>
#include <tmxpp/Flipped_global_id.hpp>
#include <tmxpp/Tile_id.hpp>
#include <tmxpp/exceptions.hpp>
#include <tmxpp/impl/read_utility.hpp>

namespace tmxpp::impl {

std::optional<Flipped_global_id> to_flipped_global_id(std::string_view s)
{
    using Raw_id = std::uint_least32_t;

    Raw_id value{from_string<Raw_id>(s)};

    if (value == 0)
        return {};

    constexpr int first_flip_bit{29};
    constexpr Raw_id flip_bits{0b111};
    constexpr Raw_id flip_mask{flip_bits << first_flip_bit};

    Flipped_global_id fgid{
        static_cast<Flip>((value >> first_flip_bit) & flip_bits),
        static_cast<Global_tile_id>(value & ~flip_mask)};

    return fgid;
}

} // namespace tmxpp::impl

#endif // TMXPP_IMPL_TO_FLIPPED_GLOBAL_ID
