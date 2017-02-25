#ifndef TMXPP_TILE_ID_HPP
#define TMXPP_TILE_ID_HPP

#include <cstdint>
#include <tmxpp/Strong_typedef.hpp>

namespace tmxpp {

class Local_tile_id
    : public Strong_typedef<std::int_least32_t, Local_tile_id>,
      type_safe::strong_typedef_op::integer_arithmetic<Local_tile_id> {
public:
    using Strong_typedef::Strong_typedef;
};

class Global_tile_id
    : public Strong_typedef<std::int_least32_t, Global_tile_id>,
      type_safe::strong_typedef_op::integer_arithmetic<Global_tile_id> {
public:
    using Strong_typedef::Strong_typedef;
};

} // namespace tmxpp

#endif // TMXPP_TILE_ID_HPP
