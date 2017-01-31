#ifndef TMXPP_UNIT_INTERVAL_HPP
#define TMXPP_UNIT_INTERVAL_HPP

#include <boost/hana/integral_constant.hpp>
#include <type_safe/bounded_type.hpp>
#include <type_safe/constrained_type.hpp>

namespace tmxpp {

// A `double` that is in the [`0`,`1`] range.
using Unit_interval = type_safe::constrained_type<
    double, type_safe::constraints::closed_interval<
                int, boost::hana::int_<0>, boost::hana::int_<1>>>;

} // namespace tmxpp

#endif // TMXPP_UNIT_INTERVAL_HPP
