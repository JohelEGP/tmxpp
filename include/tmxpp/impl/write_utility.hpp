#ifndef TMXPP_IMPL_WRITE_UTILITY_HPP
#define TMXPP_IMPL_WRITE_UTILITY_HPP

#include <optional>
#include <string>
#include <string_view>
#include <type_traits>
#include <boost/lexical_cast.hpp>
#include <type_safe/constrained_type.hpp>
#include <type_safe/strong_typedef.hpp>
#include <tmxpp/File.hpp>
#include <tmxpp/exceptions.hpp>
#include <tmxpp/impl/Xml.hpp>
#include <tmxpp/impl/to_string_color.hpp>

namespace tmxpp::impl {

void add(Xml::Element elem, Xml::Attribute::Name name, std::string_view value)
{
    elem.add(name, Xml::Attribute::Value{value});
}

void non_empty_add(
    Xml::Element elem, Xml::Attribute::Name name, std::string_view value)
{
    if (!value.empty())
        add(elem, name, value);
}

void non_empty_add(
    Xml::Element elem, Xml::Attribute::Name name, const File& value)
{
    if (!value.empty())
        add(elem, name, value.string());
}

template <
    class Arithmetic,
    class = std::enable_if_t<std::is_arithmetic_v<Arithmetic>>>
std::string to_string(Arithmetic num) try {
    return boost::lexical_cast<std::string>(num);
}
catch (const boost::bad_lexical_cast& e) {
    throw Exception{
        std::string{"Could not convert Arithmetic to std::string. "} +
        e.what()};
}

template <class T, class Phantom>
std::string to_string(type_safe::strong_typedef<Phantom, T> x)
{
    return to_string(get(x));
}

template <class T, class C, class V>
std::string to_string(type_safe::constrained_type<T, C, V> x)
{
    return to_string(x.get_value());
}

template <
    class T,
    class = std::enable_if_t<!std::is_convertible_v<T, std::string_view>>>
void add(Xml::Element elem, Xml::Attribute::Name name, T value)
{
    add(elem, name, to_string(value));
}

template <class T>
void add(Xml::Element elem, Xml::Attribute::Name name, std::optional<T> value)
{
    if (value)
        add(elem, name, *value);
}

template <class T>
struct Default {
    explicit constexpr Default(T val) noexcept : value{val}
    {
    }

    T value;
};

template <class T>
void non_default_add(
    Xml::Element elem, Xml::Attribute::Name name, T value,
    Default<T> def = Default{T{}})
{
    if (value != def.value)
        add(elem, name, value);
}

template <class T>
void write(const std::optional<T>& value, Xml::Element elem)
{
    if (value)
        write(*value, elem);
}

} // namespace tmxpp::impl

#endif // TMXPP_IMPL_WRITE_UTILITY_HPP
