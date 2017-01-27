#ifndef TMXPP_DEGREES_HPP
#define TMXPP_DEGREES_HPP

#include <type_safe/strong_typedef.hpp>

namespace tmxpp {

class Degrees
    : public type_safe::strong_typedef<Degrees, double>,
      public type_safe::strong_typedef_op::equality_comparison<Degrees, bool>,
      public type_safe::strong_typedef_op::relational_comparison<Degrees, bool>,
      public type_safe::strong_typedef_op::floating_point_arithmetic<Degrees> {
public:
    using strong_typedef::strong_typedef;
};

} // namespace tmxpp

#endif // TMXPP_DEGREES_HPP
