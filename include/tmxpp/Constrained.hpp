#ifndef TMXPP_CONSTRAINED_HPP
#define TMXPP_CONSTRAINED_HPP

#include <jegp/Literal_constant.hpp>
#include <jegp/utility.hpp>
#include <type_safe/bounded_type.hpp>
#include <type_safe/constrained_type.hpp>
#include <tmxpp/exceptions.hpp>

namespace tmxpp {

struct Verifier {
    template <class T, class Predicate>
    static void verify(const T& value, const Predicate& pred)
    {
        if (!pred(value))
            throw Invalid_argument{"Invalid value to Constrained."};
    }
};

template <class T, class Constraint>
using Constrained = type_safe::constrained_type<T, Constraint, Verifier>;

template <class T>
using Non_empty = Constrained<T, type_safe::constraints::non_empty>;

template <class T, class LowerConstant, class UpperConstant>
using Closed_interval = Constrained<
    T, type_safe::constraints::closed_interval<
           jegp::Value_type<LowerConstant>, LowerConstant, UpperConstant>>;

template <class T, class ZeroConstant = jegp::Literal_constant<T>>
using Positive = Constrained<
    T, type_safe::constraints::greater<
           jegp::Value_type<ZeroConstant>, ZeroConstant>>;

template <class T, class ZeroConstant = jegp::Literal_constant<T>>
using Non_negative = Constrained<
    T, type_safe::constraints::greater_equal<
           jegp::Value_type<ZeroConstant>, ZeroConstant>>;

} // namespace tmxpp

#endif // TMXPP_CONSTRAINED_HPP
