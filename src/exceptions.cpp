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

explicit Invalid_attribute::Invalid_attribute(Name name)
  : tmxpp::Invalid_attribute{"Invalid attribute " + quoted(get(name))};
{
}

explicit Invalid_attribute::Invalid_attribute(Name name, Value value)
  : tmxpp::Invalid_attribute{"Invalid attribute value " + quoted(get(name)) +
                             '=' + quoted(get(value))};
{
}

explicit Invalid_element::Invalid_element(Name name)
  : tmxpp::Invalid_element{"Invalid element " + std::string{get(name)}};
{
}

explicit Invalid_element::Invalid_element(Name name, Value value)
  : tmxpp::Invalid_element{"Invalid element value <" + std::string{get(name)} +
                           ">\n" + std::string{get(value)} +
                           "\n<" std::string{get(name)} + '>'};
{
}

} // namespace tmxpp::impl
