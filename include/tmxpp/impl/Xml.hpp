#ifndef TMXPP_IMPL_XML_HPP
#define TMXPP_IMPL_XML_HPP

#include <optional>
#include <ostream>
#include <string>
#include <string_view>
#include <utility>
#include <gsl/gsl>
#include <gsl/string_span>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/indirect.hpp>
#include <range/v3/view/iota.hpp>
#include <range/v3/view/transform.hpp>
#include <rapidxml.hpp>
#include <rapidxml_iterators.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml_utils.hpp>
#include <tmxpp/Strong_typedef.hpp>
#include <tmxpp/exceptions.hpp>

namespace tmxpp::impl {

// Represents an xml document.
// All arguments of type `Attribute::Name` and `Element::Name` are required to
// be from the header tmx_info.hpp (`constexpr` and non-empty).
class Xml {
public:
    class Element;

    class Attribute {
    public:
        using Name  = Strong_typedef<std::string_view, struct _attribute_name>;
        using Value = Strong_typedef<std::string_view, struct _attribute_value>;

        Name name() const noexcept
        {
            return Name{attr->name_ref()};
        }

        Value value() const noexcept
        {
            return Value{attr->value_ref()};
        }

    private:
        using underlying_type = rapidxml::xml_attribute<>;

        explicit Attribute(underlying_type* u) noexcept : attr{u}
        {
        }

        underlying_type* attr;

        friend Element;
    };

    class Element {
    public:
        using Name  = Strong_typedef<std::string_view, struct _element_name>;
        using Value = Strong_typedef<std::string_view, struct _element_value>;

        Name name() const noexcept
        {
            return Name{elem->name_ref()};
        }

        Value value() const noexcept
        {
            return Value{elem->value_ref()};
        }

        void value(Value value) const noexcept
        {
            elem->value(get(value));
        }

        void value(std::string&& value) const
        {
            this->value(Value{elem->document()->allocate_string(value)});
        }

        // Returns: An `Attribute` with the given `name`.
        // Throws: `Invalid_attribute` if there is no such `Attribute`.
        Attribute attribute(Attribute::Name name) const;

        // Returns: A child `Element` with the given `name`.
        // Throws: `Invalid_element` if there is no such child `Element`.
        Element child(Name name) const;

        // Returns: An `Attribute` with the given `name`, if any.
        std::optional<Attribute> optional_attribute(Attribute::Name name) const
            noexcept
        {
            if (auto attr{elem->first_attribute(get(name))})
                return Attribute{attr};
            return {};
        }

        // Returns: A child `Element` with the given `name`, if any.
        std::optional<Element> optional_child(Name name) const noexcept
        {
            if (auto child{elem->first_node(get(name))})
                return Element{child};
            return {};
        }

        // Returns: A `ranges::InputView` of the `Attribute`s filtered by
        //          `name`.
        auto attributes(Attribute::Name name) const noexcept
        {
            return ranges::view::iota(
                       rapidxml::attribute_iterator<>{elem},
                       rapidxml::attribute_iterator<>{}) |
                   ranges::view::indirect |
                   ranges::view::filter([name](auto&& attribute) {
                       return attribute.name_ref() == get(name);
                   }) |
                   ranges::view::transform(
                       [](auto&& attribute) { return Attribute{&attribute}; });
        }

        // Returns: A `ranges::InputView` of the children `Element`s.
        auto children() const noexcept
        {
            return ranges::view::iota(
                       rapidxml::node_iterator<>{elem},
                       rapidxml::node_iterator<>{}) |
                   ranges::view::indirect |
                   ranges::view::transform(
                       [](auto&& child) { return Element{&child}; });
        }

        // Returns: A `ranges::InputView` of the children `Element`s filtered by
        //          `name`.
        auto children(Name name) const noexcept
        {
            return ranges::view::iota(
                       rapidxml::node_iterator<>{elem},
                       rapidxml::node_iterator<>{}) |
                   ranges::view::indirect |
                   ranges::view::filter([name](auto&& child) {
                       return child.name_ref() == get(name);
                   }) |
                   ranges::view::transform(
                       [](auto&& child) { return Element{&child}; });
        }

        // Effects: Adds an `Attribute` with the given `name` and `value`.
        void add(Attribute::Name name, Attribute::Value value) const
        {
            auto doc{elem->document()};

            if (!get(value).empty())
                value = Attribute::Value{doc->allocate_string(get(value))};

            elem->append_attribute(
                doc->allocate_attribute(get(name), get(value)));
        }

        // Effects: Adds a child `Element` with the given `name`.
        // Returns: The added `Element`.
        Element add(Name name) const
        {
            elem->append_node(elem->document()->allocate_node(
                rapidxml::node_element, get(name)));

            return Element{elem->last_node()};
        }

    private:
        using underlying_type = rapidxml::xml_node<>;

        explicit Element(underlying_type* u) noexcept : elem{u}
        {
        }

        underlying_type* elem;

        friend Xml;
    };

    // Effects: Loads and parses the `Xml` `path`.
    // Throws: `Exception` in case of parsing error or lack of root element.
    explicit Xml(gsl::not_null<gsl::czstring<>> path) : xml{path}
    {
        try {
            doc.parse<rapidxml::parse_fastest>(std::as_const(xml)->data());
        }
        catch (const rapidxml::parse_error& e) {
            throw Exception{e.what()};
        }

        if (root().elem == nullptr)
            throw Exception{std::string{path} + " has no root element."};
    }

    // Effects: Creates an `Xml` with the root `Element` `name`.
    explicit Xml(Element::Name name)
    {
        doc.append_node(doc.allocate_node(rapidxml::node_element, get(name)));
    }

    Xml(const Xml&) = delete;
    Xml& operator=(const Xml&) = delete;

    Element root() const noexcept
    {
        return Element{doc.first_node()};
    }

    friend std::ostream& operator<<(std::ostream& os, const Xml& xml)
    {
        return os << xml.doc;
    }

private:
    std::optional<rapidxml::file<>> xml;
    rapidxml::xml_document<> doc;
};

} // namespace tmxpp::impl

#endif // TMXPP_IMPL_XML_HPP
