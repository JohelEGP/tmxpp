#ifndef TMXPP_TILE_ID_HPP
#define TMXPP_TILE_ID_HPP

#include <cstdint>
#include <type_safe/strong_typedef.hpp>

namespace tmxpp {

class Tile_id
    : public type_safe::strong_typedef<Tile_id, std::int_least32_t>,
      public type_safe::strong_typedef_op::equality_comparison<Tile_id, bool>,
      public type_safe::strong_typedef_op::relational_comparison<Tile_id, bool>,
      public type_safe::strong_typedef_op::integer_arithmetic<Tile_id> {
public:
    using strong_typedef::strong_typedef;
};

} // namespace tmxpp

#endif // TMXPP_TILE_ID_HPP
