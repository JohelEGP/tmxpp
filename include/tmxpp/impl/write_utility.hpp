#ifndef TMXPP_IMPL_WRITE_UTILITY_HPP
#define TMXPP_IMPL_WRITE_UTILITY_HPP

#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>
#include <boost/lexical_cast.hpp>
#include <tmxpp/Constrained.hpp>
#include <tmxpp/File.hpp>
#include <tmxpp/Strong_typedef.hpp>
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

template <class File_, class = std::enable_if_t<std::is_same_v<File_, File>>>
void non_empty_add(
    Xml::Element elem, Xml::Attribute::Name name, const File_& value)
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

std::string to_string(double d)
{
    std::stringstream ss;
    ss << d;
    return ss.str();
}

template <class T, class C>
std::string to_string(const Constrained<T, C>& x)
{
    return to_string(*x);
}

template <class T, class P>
std::string to_string(Strong_typedef<T, P> x)
{
    return to_string(get(x));
}

template <
    class T,
    class = std::enable_if_t<!std::is_convertible_v<T, std::string_view>>>
void add(Xml::Element elem, Xml::Attribute::Name name, T value)
{
    add(elem, name, to_string(value));
}

template <class T, class C>
void add(
    Xml::Element elem, Xml::Attribute::Name name, const Constrained<T, C>& x)
{
    return add(elem, name, *x);
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

template <class T, class C>
void non_default_add(
    Xml::Element elem, Xml::Attribute::Name name,
    const Constrained<T, C>& value, Default<T> def = Default{T{}})
{
    if (*value != def.value)
        add(elem, name, *value);
}

template <class T>
void write(const std::optional<T>& value, Xml::Element elem)
{
    if (value)
        write(*value, elem);
}

} // namespace tmxpp::impl

#endif // TMXPP_IMPL_WRITE_UTILITY_HPP
