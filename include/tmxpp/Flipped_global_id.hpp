#ifndef TMXPP_FLIPPED_GLOBAL_ID_HPP
#define TMXPP_FLIPPED_GLOBAL_ID_HPP

#include <tmxpp/Flip.hpp>
#include <tmxpp/Tile_id.hpp>

namespace tmxpp {

struct Flipped_global_id {
    Flip flip;
    Global_tile_id id;
};

constexpr bool ok(Flipped_global_id f) noexcept
{
    return f.id != Global_tile_id{} || f.flip == Flip{};
}

constexpr bool operator==(Flipped_global_id l, Flipped_global_id r) noexcept
{
    return l.flip == r.flip && l.id == r.id;
}
constexpr bool operator!=(Flipped_global_id l, Flipped_global_id r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_FLIPPED_GLOBAL_ID_HPP
