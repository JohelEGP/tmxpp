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
#include <range/v3/action/concepts.hpp>
#include <range/v3/algorithm/any_of.hpp>
#include <range/v3/begin_end.hpp>
#include <range/v3/distance.hpp>
#include <range/v3/range_concepts.hpp>
#include <range/v3/range_traits.hpp>
#include <range/v3/utility/concepts.hpp>
#include <range/v3/utility/functional.hpp>
#include <range/v3/utility/invoke.hpp>
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
std::optional<Xml::Attribute::Value> optional_value(
    Xml::Element element, Xml::Attribute::Name name) noexcept
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
    CONCEPT_REQUIRES(ranges::Integral<T>())
    T operator()(std::string_view s) try {
        return boost::lexical_cast<T>(s);
    }
    catch (const boost::bad_lexical_cast& e) {
        throw Exception{std::string{s} +
                        " could not be converted to Integral. " + e.what()};
    }

    // Returns: `s` as a `T` floating point.
    // Throws: `Exception` if it could not be converted.
    CONCEPT_REQUIRES(std::is_floating_point_v<T>)
    T operator()(std::string_view s)
    {
        std::stringstream ss;
        ss << std::noskipws << std::scientific << s;
        T num;
        ss >> num;
        if (!ss || !ss.eof())
            throw Exception{std::string{s} +
                            " could not be converted to FloatingPoint."};
        return num;
    }

    template <class Constrained = T>
    detected_t<jegp::Value_type, Constrained> operator()(std::string_view s)
    {
        return Constrained{From_string<jegp::Value_type<Constrained>>{}(s)};
    }

    template <class StrongTypedef = T>
    detected_t<type_safe::underlying_type, StrongTypedef> operator()(
        std::string_view s)
    {
        return StrongTypedef{
            From_string<type_safe::underlying_type<StrongTypedef>>{}(s)};
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

// Returns: A `ranges::InputView` of `element`'s children whose names are in
//          `names`.
auto children(
    Xml::Element element, std::initializer_list<Xml::Element::Name> names)
{
    return element.children() | ranges::view::filter([names](auto&& child) {
               return ranges::any_of(
                   names, [child](auto name) { return name == child.name(); });
           });
}

// Requires: `Cont` is a STL `SequenceContainer`.
// Returns: `rng` `trans`formed into the `Cont`.
template <
    class Cont, class Rng, class Transform,
    CONCEPT_REQUIRES_(
        ranges::Reservable<Cont>() && ranges::InputRange<Rng>() &&
        ranges::RegularInvocable<
            Transform, ranges::range_value_type_t<Rng>>() &&
        ranges::ConvertibleTo<
            ranges::result_of_t<Transform(ranges::range_value_type_t<Rng>)>,
            jegp::Value_type<Cont>>())>
Cont transform(Rng rng, Transform trans)
{
    Cont container;
    container.reserve(ranges::distance(rng));

    auto elements{rng | ranges::view::transform(trans) | ranges::view::bounded};

    CONCEPT_ASSERT(ranges::ReserveAndAssignable<
                   Cont, decltype(ranges::begin(elements))>());
    container.assign(ranges::begin(elements), ranges::end(elements));
    return container;
}

// Returns: A `ranges::InputRange` of `std::string`s where the elements are the
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
