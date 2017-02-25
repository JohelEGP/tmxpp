#ifndef TMXPP_IMPL_READ_UTILITY_HPP
#define TMXPP_IMPL_READ_UTILITY_HPP

#include <ios>
#include <optional>
#include <sstream>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <gsl/gsl>
#include <gsl/string_span>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/begin_end.hpp>
#include <range/v3/distance.hpp>
#include <range/v3/view/bounded.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/transform.hpp>
#include <jegp/utility.hpp>
#include <tmxpp/Constrained.hpp>
#include <tmxpp/Strong_typedef.hpp>
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

template <template <class> class Op, class T, class = std::void_t<>>
struct detector {
};

template <template <class> class Op, class T>
struct detector<Op, T, std::void_t<Op<T>>> {
    using type = T;
};

template <template <class> class Op, class T>
using detected_t = typename detector<Op, T>::type;

template <class T>
struct From_string {
    // Returns: `s` as an `Integral`.
    // Throws: `Exception` if it could not be converted.
    template <class Integral = T>
    std::enable_if_t<std::is_integral_v<Integral>, Integral>
    operator()(std::string_view s) try {
        return boost::lexical_cast<Integral>(s);
    }
    catch (const boost::bad_lexical_cast& e) {
        throw Exception{std::string{s} +
                        " could not be converted to Integral. " + e.what()};
    }

    // Returns: `s` as an `FloatingPoint`.
    // Throws: `Exception` if it could not be converted.
    template <class FloatingPoint = T>
    std::enable_if_t<std::is_floating_point_v<FloatingPoint>, FloatingPoint>
    operator()(std::string_view s)
    {
        std::stringstream ss;
        ss << std::noskipws << std::scientific << s;
        FloatingPoint num;
        ss >> num;
        if (!ss || !ss.eof())
            throw Exception{std::string{s} +
                            " could not be converted to FloatingPoint."};
        return num;
    }

    template <class StrongTypedef = T>
    detected_t<type_safe::underlying_type, StrongTypedef>
    operator()(std::string_view s)
    {
        return StrongTypedef{
            From_string<type_safe::underlying_type<StrongTypedef>>{}(s)};
    }

    template <class Constrained = T>
    detected_t<jegp::Value_type, Constrained> operator()(std::string_view s)
    {
        return Constrained{From_string<jegp::Value_type<Constrained>>{}(s)};
    }
};

template <class T>
T from_string(std::string_view s)
{
    return From_string<T>{}(s);
}

template <class T>
T from_string(Xml::Attribute::Value value)
{
    return from_string<T>(get(value));
}

// Returns: The range of `element`'s children whose names are in `names`.
auto children(
    Xml::Element element, std::initializer_list<Xml::Element::Name> names)
{
    return element.children() | ranges::view::filter([names](auto&& child) {
               return ranges::any_of(
                   names, [child](auto name) { return name == child.name(); });
           });
}

// Requires: `ReservableContainer` is a STL `SequenceContainer` with a `reserve`
//           member. `View` is a range-v3 view. `Function` takes an element of
//           the `view` and returns an element of the `ReservableContainer`.
// Returns: The `view` `transform`ed into the `ReservableContainer`.
template <class ReservableContainer, class View, class Function>
ReservableContainer transform(View view, Function transform)
{
    ReservableContainer container;
    container.reserve(ranges::distance(view));

    auto elements{view | ranges::view::transform(transform) |
                  ranges::view::bounded};

    container.assign(ranges::begin(elements), ranges::end(elements));
    return container;
}

// Returns: A range-v3 range of `std::string`s where the elements are the
//          substrings in `to_tokenize` separated by the characters in
//          `separators`.
auto tokenize(
    std::string_view to_tokenize, gsl::not_null<gsl::czstring<>> separators)
{
    using TokenizerFunction = boost::char_separator<char>;
    using Tokenizer =
        boost::tokenizer<TokenizerFunction, std::string_view::iterator>;

    return Tokenizer{to_tokenize, TokenizerFunction{separators}};
}

} // namespace tmxpp::impl

#endif // TMXPP_IMPL_READ_UTILITY_HPP
