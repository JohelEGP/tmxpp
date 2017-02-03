#ifndef TMXPP_IMPL_READ_UTILITY_HPP
#define TMXPP_IMPL_READ_UTILITY_HPP

#include <optional>
#include <string>
#include <string_view>
#include <boost/lexical_cast.hpp>
#include <range/v3/begin_end.hpp>
#include <range/v3/distance.hpp>
#include <range/v3/view/bounded.hpp>
#include <range/v3/view/transform.hpp>
#include <type_safe/strong_typedef.hpp>
#include <tmxpp/Pixel.hpp>
#include <tmxpp/Unique_id.hpp>
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
Pixel from_string<Pixel>(std::string_view s)
{
    return Pixel{from_string<type_safe::underlying_type<Pixel>>(s)};
}

template <>
Unique_id from_string<Unique_id>(std::string_view s)
{
    return Unique_id{from_string<type_safe::underlying_type<Unique_id>>(s)};
}

template <class Arithmetic>
Arithmetic from_string(Xml::Attribute::Value value)
{
    return from_string<Arithmetic>(get(value));
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
