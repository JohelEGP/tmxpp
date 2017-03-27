#ifndef TMXPP_UNIT_INTERVAL_HPP
#define TMXPP_UNIT_INTERVAL_HPP

#include <boost/hana/integral_constant.hpp>
#include <tmxpp/Constrained.hpp>

namespace tmxpp {

// A `double` that is in the [`0`,`1`] range.
using Unit_interval =
    Closed_interval<double, boost::hana::int_<0>, boost::hana::int_<1>>;

} // namespace tmxpp

#endif // TMXPP_UNIT_INTERVAL_HPP
