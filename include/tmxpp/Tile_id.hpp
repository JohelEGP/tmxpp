#ifndef TMXPP_TILE_ID_HPP
#define TMXPP_TILE_ID_HPP

#include <cstdint>
#include <boost/hana/integral_constant.hpp>
#include <tmxpp/Constrained.hpp>

namespace tmxpp {

using Local_tile_id = Closed_range<
    std::int_least32_t, boost::hana::long_<0>, boost::hana::long_<0x1FFF'FFFE>>;

using Global_tile_id = Closed_range<
    std::int_least32_t, boost::hana::long_<1>, boost::hana::long_<0x1FFF'FFFF>>;

} // namespace tmxpp

#endif // TMXPP_TILE_ID_HPP
