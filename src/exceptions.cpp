#include <utility>
#include <tmxpp/exceptions.hpp>

namespace tmxpp {

Exception::Exception(std::string what) noexcept : what_{std::move(what)}
{
}

const char* Exception::what() const noexcept
{
    return what_.c_str();
}

} // namespace tmxpp
