#ifndef TMXPP_UNIQUE_ID_HPP
#define TMXPP_UNIQUE_ID_HPP

#include <tmxpp/Strong_typedef.hpp>

namespace tmxpp {

class Unique_id : public Strong_typedef<int, Unique_id>,
                  type_safe::strong_typedef_op::integer_arithmetic<Unique_id> {
public:
    using Strong_typedef::Strong_typedef;
};

} // namespace tmxpp

#endif // TMXPP_UNIQUE_ID_HPP
