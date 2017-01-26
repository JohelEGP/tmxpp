#ifndef TMXPP_PIXEL_HPP
#define TMXPP_PIXEL_HPP

#include <type_safe/strong_typedef.hpp>

namespace tmxpp {

class Pixel : public type_safe::strong_typedef<Pixel, double>,
              type_safe::strong_typedef_op::equality_comparison<Pixel, bool>,
              type_safe::strong_typedef_op::relational_comparison<Pixel, bool>,
              type_safe::strong_typedef_op::floating_point_arithmetic<Pixel> {
public:
    using strong_typedef::strong_typedef;
};

} // namespace tmxpp

#endif // TMXPP_PIXEL_HPP
