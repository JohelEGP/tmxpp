#ifndef TMXPP_FLIPPED_GLOBAL_ID_HPP
#define TMXPP_FLIPPED_GLOBAL_ID_HPP

#include <tmxpp/Flip.hpp>
#include <tmxpp/Tile_id.hpp>

namespace tmxpp {

struct Flipped_global_id {
    Flip flip;
    Global_tile_id id;
};

inline bool operator==(Flipped_global_id l, Flipped_global_id r) noexcept
{
    return l.flip == r.flip && l.id == r.id;
}
inline bool operator!=(Flipped_global_id l, Flipped_global_id r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_FLIPPED_GLOBAL_ID_HPP
