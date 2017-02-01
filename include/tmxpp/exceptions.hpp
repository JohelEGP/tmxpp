#ifndef TMXPP_EXCEPTIONS_HPP
#define TMXPP_EXCEPTIONS_HPP

#include <stdexcept>

namespace tmxpp {

class Invalid_attribute : public std::invalid_argument {
public:
    using std::invalid_argument::invalid_argument;
};

class Invalid_element : public std::invalid_argument {
public:
    using std::invalid_argument::invalid_argument;
};

} // namespace tmxpp

#endif // TMXPP_EXCEPTIONS_HPP
