#ifndef TMXPP_IMPL_XML_HPP
#define TMXPP_IMPL_XML_HPP

#include <optional>
#include <ostream>
#include <string>
#include <string_view>
#include <utility>
#include <gsl/gsl_assert>
#include <rapidxml.hpp>
#include <rapidxml_iterators.hpp>
#include <rapidxml_print.hpp>
#include <rapidxml_utils.hpp>
#include <tmxpp/impl/Strong_typedef.hpp>

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

        // Returns: An `Attribute` with the given `name`.
        // Throws: `Invalid_attribute` if there is no such `Attribute`.
        Attribute attribute(Attribute::Name name) const;

        // Returns: A child `Element` with the given `name`.
        // Throws: `Invalid_attribute` if there is no such child `Element`.
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

        // Returns: A range of the `Attribute`s filtered by `name`.
        auto attributes(Attribute::Name name) const noexcept
        {
            return attribute_range(elem, get(name));
        }

        // Returns: A range of the children `Element`s filtered by `name`.
        auto children(Name name) const noexcept
        {
            return node_range(elem, get(name));
        }

        // Effects: Adds an `Attribute` with the given `name` and `value`.
        void add(Attribute::Name name, Attribute::Value value) const
        {
            Expects(!get(value).empty());

            auto doc{elem->document()};

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

        // Effects: Adds a child `Element` with the given `name` and `value`.
        // Returns: The added `Element`.
        Element add(Name name, Value value) const
        {
            Expects(!get(value).empty());

            auto doc{elem->document()};

            value = Value{doc->allocate_string(get(value))};

            elem->append_node(doc->allocate_node(
                rapidxml::node_element, get(name), get(value)));

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
    explicit Xml(const std::string& path) : xml{path.c_str()}
    {
        using namespace rapidxml;

        doc.parse<parse_fastest | parse_trim_whitespace>(
            std::as_const(xml)->data());

        Ensures(root().elem != nullptr);
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
