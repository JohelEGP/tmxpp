#ifndef TMXPP_UNIQUE_ID_HPP
#define TMXPP_UNIQUE_ID_HPP

#include <type_safe/strong_typedef.hpp>

namespace tmxpp {

class Unique_id
    : public type_safe::strong_typedef<Unique_id, int>,
      public type_safe::strong_typedef_op::equality_comparison<Unique_id, bool>,
      public type_safe::strong_typedef_op::relational_comparison<
          Unique_id, bool>,
      public type_safe::strong_typedef_op::integer_arithmetic<Unique_id> {
public:
    using strong_typedef::strong_typedef;
};

} // namespace tmxpp

#endif // TMXPP_UNIQUE_ID_HPP
