#ifndef TMXPP_FLIPPED_GLOBAL_ID_HPP
#define TMXPP_FLIPPED_GLOBAL_ID_HPP

#include <tmxpp/Flip.hpp>
#include <tmxpp/Tile_id.hpp>

namespace tmxpp {

struct Flipped_global_id {
    Flip flip;
    Tile_id global_id;
};

constexpr bool ok(Flipped_global_id f) noexcept
{
    return f.global_id != Tile_id{} || f.flip == Flip{};
}

constexpr bool operator==(Flipped_global_id l, Flipped_global_id r) noexcept
{
    return l.flip == r.flip && l.global_id == r.global_id;
}
constexpr bool operator!=(Flipped_global_id l, Flipped_global_id r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_FLIPPED_GLOBAL_ID_HPP
