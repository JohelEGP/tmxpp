#ifndef TMXPP_STRONG_TYPEDEF_HPP
#define TMXPP_STRONG_TYPEDEF_HPP

#include <type_safe/strong_typedef.hpp>

namespace tmxpp {

template <class T, class Phantom>
class Strong_typedef
  : public type_safe::strong_typedef<Phantom, T>
  , type_safe::strong_typedef_op::equality_comparison<
        Strong_typedef<T, Phantom>, bool>
  , type_safe::strong_typedef_op::relational_comparison<
        Strong_typedef<T, Phantom>, bool> {
public:
    using type_safe::strong_typedef<Phantom, T>::strong_typedef;
};

} // namespace tmxpp

#endif // TMXPP_STRONG_TYPEDEF_HPP
