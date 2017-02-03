#ifndef TMXPP_IMPL_READ_UTILITY_HPP
#define TMXPP_IMPL_READ_UTILITY_HPP

#include <chrono>
#include <optional>
#include <string>
#include <string_view>
#include <boost/lexical_cast.hpp>
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/begin_end.hpp>
#include <range/v3/distance.hpp>
#include <range/v3/view/bounded.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/transform.hpp>
#include <type_safe/strong_typedef.hpp>
#include <tmxpp/Pixel.hpp>
#include <tmxpp/Tile_id.hpp>
#include <tmxpp/Unique_id.hpp>
#include <tmxpp/Unit_interval.hpp>
#include <tmxpp/exceptions.hpp>
#include <tmxpp/impl/Xml.hpp>

namespace tmxpp::impl {

Xml::Attribute::Value value(Xml::Element element, Xml::Attribute::Name name)
{
    return element.attribute(name).value();
}

// Returns: The value of the `name` attribute in `element`, if there is such an
//          attribute.
std::optional<Xml::Attribute::Value>
optional_value(Xml::Element element, Xml::Attribute::Name name) noexcept
{
    if (auto attribute{element.optional_attribute(name)})
        return attribute->value();
    return {};
}

// Returns: `s` as an `Arithmetic`.
// Throws: `Exception` if it could not be converted.
template <class Arithmetic>
Arithmetic from_string(std::string_view s) try {
    return boost::lexical_cast<Arithmetic>(s);
}
catch (const boost::bad_lexical_cast& e) {
    throw Exception{std::string{s} + " could not be converted to Arithmetic. " +
                    e.what()};
}

template <>
Tile_id from_string<Tile_id>(std::string_view s)
{
    return Tile_id{from_string<type_safe::underlying_type<Tile_id>>(s)};
}

template <>
Pixel from_string<Pixel>(std::string_view s)
{
    return Pixel{from_string<type_safe::underlying_type<Pixel>>(s)};
}

template <>
Unit_interval from_string<Unit_interval>(std::string_view s)
{
    return Unit_interval{from_string<Unit_interval::value_type>(s)};
}

template <>
Unique_id from_string<Unique_id>(std::string_view s)
{
    return Unique_id{from_string<type_safe::underlying_type<Unique_id>>(s)};
}

template <>
std::chrono::milliseconds
from_string<std::chrono::milliseconds>(std::string_view s)
{
    return std::chrono::milliseconds{
        from_string<std::chrono::milliseconds::rep>(s)};
}

template <class Arithmetic>
Arithmetic from_string(Xml::Attribute::Value value)
{
    return from_string<Arithmetic>(get(value));
}

// Returns: The range of `element`'s children whose names are in `names`.
auto filter(
    Xml::Element element, std::initializer_list<Xml::Element::Name> names)
{
    return element.children() | ranges::view::filter([names](auto&& child) {
               return ranges::any_of(
                   names, [child](auto name) { return name == child.name(); });
           });
}

// Requires: `ReservableContainer` is a STL `SequenceContainer` with a `reserve`
//           member. `Range` is a range-v3 range. `Function` takes an element of
//           the `range` and returns an element of the `ReservableContainer`.
// Returns: The `range` `transform`ed into the `ReservableContainer`.
template <class ReservableContainer, class Range, class Function>
ReservableContainer transform(Range range, Function transform)
{
    ReservableContainer container;
    container.reserve(ranges::distance(range));

    auto elements{range | ranges::view::transform(transform) |
                  ranges::view::bounded};

    container.assign(ranges::begin(elements), ranges::end(elements));
    return container;
}

} // namespace tmxpp::impl

#endif // TMXPP_IMPL_READ_UTILITY_HPP
