#ifndef TMXPP_PIXEL_HPP
#define TMXPP_PIXEL_HPP

#include <tmxpp/Strong_typedef.hpp>

namespace tmxpp {

class Pixel : public Strong_typedef<double, Pixel>,
              type_safe::strong_typedef_op::floating_point_arithmetic<Pixel> {
public:
    using Strong_typedef::Strong_typedef;
};

} // namespace tmxpp

#endif // TMXPP_PIXEL_HPP
