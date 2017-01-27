#ifndef TMXPP_FLIPPED_GID_HPP
#define TMXPP_FLIPPED_GID_HPP

#include <tmxpp/Flip.hpp>
#include <tmxpp/Tile_id.hpp>

namespace tmxpp {

struct Flipped_gid {
    Flip flip{};
    Tile_id gid{};
};

constexpr bool ok(Flipped_gid f) noexcept
{
    return f.gid != Tile_id{} || f.flip == Flip{};
}

constexpr bool operator==(Flipped_gid l, Flipped_gid r) noexcept
{
    return l.flip == r.flip && l.gid == r.gid;
}
constexpr bool operator!=(Flipped_gid l, Flipped_gid r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_FLIPPED_GID_HPP
