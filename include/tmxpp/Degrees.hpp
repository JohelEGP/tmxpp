#ifndef TMXPP_DEGREES_HPP
#define TMXPP_DEGREES_HPP

#include <tmxpp/Strong_typedef.hpp>

namespace tmxpp {

class Degrees
    : public Strong_typedef<double, Degrees>,
      type_safe::strong_typedef_op::floating_point_arithmetic<Degrees> {
public:
    using Strong_typedef::Strong_typedef;
};

} // namespace tmxpp

#endif // TMXPP_DEGREES_HPP
