#ifndef TMXPP_TILE_ID_HPP
#define TMXPP_TILE_ID_HPP

#include <cstdint>
#include <boost/hana/integral_constant.hpp>
#include <tmxpp/Constrained.hpp>
#include <tmxpp/Flip.hpp>

namespace tmxpp {

using Local_tile_id = Closed_interval<
    std::int_least32_t, boost::hana::long_<0>, boost::hana::long_<0x1FFF'FFFE>>;

using Global_tile_id = Closed_interval<
    std::int_least32_t, boost::hana::long_<1>, boost::hana::long_<0x1FFF'FFFF>>;

struct Flipped_tile_id {
    Flip flip;
    Global_tile_id id;
};

inline bool operator==(Flipped_tile_id l, Flipped_tile_id r) noexcept
{
    return l.flip == r.flip && l.id == r.id;
}
inline bool operator!=(Flipped_tile_id l, Flipped_tile_id r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_TILE_ID_HPP
