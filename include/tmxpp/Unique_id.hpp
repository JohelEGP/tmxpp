#ifndef TMXPP_UNIQUE_ID_HPP
#define TMXPP_UNIQUE_ID_HPP

#include <tmxpp/Constrained.hpp>
#include <tmxpp/Strong_typedef.hpp>

namespace tmxpp {

using Unique_id = Strong_typedef<Non_negative<int>, struct _unique_id>;

} // namespace tmxpp

#endif // TMXPP_UNIQUE_ID_HPP
