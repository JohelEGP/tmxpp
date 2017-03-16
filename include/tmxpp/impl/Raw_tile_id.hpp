#ifndef TMXPP_IMPL_RAW_TILE_ID_HPP
#define TMXPP_IMPL_RAW_TILE_ID_HPP

#include <cstdint>
#include <optional>
#include <tmxpp/Strong_typedef.hpp>
#include <tmxpp/Tile_id.hpp>

namespace tmxpp::impl {

/// Low-level representation of an `std::optional<Flipped_tile_id>`. See
/// `is_valid(Raw_tile_id)`.
using Raw_tile_id = Strong_typedef<std::uint_least32_t, struct _raw_tile_id>;

constexpr auto _global_mask{
    Global_tile_id::constraint_predicate::upper_bound::value};

inline Raw_tile_id _to_raw(Global_tile_id id) noexcept
{
    return static_cast<Raw_tile_id>(*id);
}

inline Global_tile_id _to_global(Raw_tile_id id) noexcept
{
    return static_cast<Global_tile_id>(get(id) & _global_mask);
}

static constexpr int _first_flip_bit{29};

constexpr Raw_tile_id _to_raw(Flip f) noexcept
{
    return Raw_tile_id{static_cast<type_safe::underlying_type<Raw_tile_id>>(f)
                       << _first_flip_bit};
}

constexpr Flip _to_flip(Raw_tile_id id) noexcept
{
    return static_cast<Flip>(get(id) >> _first_flip_bit);
}

/// \returns `true` if the id is a valid TMX global tile id with flip state,
///          and `false` otherwise.
/// \remarks `true` is returned for an id of value `0` which represents the
///          empty tile.
constexpr bool is_valid(Raw_tile_id id_) noexcept
{
    const auto id{get(id_)};
    return id == 0 || (id <= 0xFFFF'FFFF && (id & _global_mask) != 0);
}

/// \requires `is_valid(id)`.
inline std::optional<Flipped_tile_id> to_flipped(Raw_tile_id id) noexcept
{
    if (get(id) == 0)
        return {};
    return {{_to_flip(id), _to_global(id)}};
}

inline Raw_tile_id to_raw(Flipped_tile_id id) noexcept
{
    return Raw_tile_id{get(_to_raw(id.flip)) | get(_to_raw(id.id))};
}

} // namespace tmxpp::impl

#endif // TMXPP_IMPL_RAW_TILE_ID_HPP
