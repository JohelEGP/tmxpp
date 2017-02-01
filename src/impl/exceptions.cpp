#include <iomanip>
#include <sstream>
#include <string>
#include <string_view>
#include <tmxpp/impl/exceptions.hpp>

namespace tmxpp::impl {

namespace {

std::string quoted(std::string_view s)
{
    std::stringstream ss;
    ss << std::quoted(std::string{s});
    return ss.str();
}

} // namespace

Invalid_attribute::Invalid_attribute(Name name)
  : Exception{"Invalid attribute " + quoted(get(name))}
{
}

Invalid_attribute::Invalid_attribute(Name name, Value value)
  : Exception{"Invalid attribute value " + quoted(get(name)) + '=' +
              quoted(get(value))}
{
}

Invalid_element::Invalid_element(Name name)
  : Exception{"Invalid element " + std::string{get(name)}}
{
}

Invalid_element::Invalid_element(Name name, Value value)
  : Exception{"Invalid element value <" + std::string{get(name)} + ">\n" +
              std::string{get(value)} + "\n<" + std::string{get(name)} + '>'}
{
}

} // namespace tmxpp::impl
