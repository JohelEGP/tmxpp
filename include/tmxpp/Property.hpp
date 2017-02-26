#ifndef TMXPP_PROPERTY_HPP
#define TMXPP_PROPERTY_HPP

#include <string>
#include <variant>
#include <tmxpp/Color.hpp>
#include <tmxpp/Constrained.hpp>
#include <tmxpp/File.hpp>

namespace tmxpp {

struct Property {
    using Value = std::variant<std::string, int, double, bool, Color, File>;

    Non_empty<std::string> name;
    Value value;
};

inline bool operator==(const Property& l, const Property& r) noexcept
{
    return l.name == r.name && l.value == r.value;
}

inline bool operator!=(const Property& l, const Property& r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_PROPERTY_HPP
