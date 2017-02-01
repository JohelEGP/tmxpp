#include <tmxpp/impl/Xml.hpp>
#include <tmxpp/impl/exceptions.hpp>

namespace tmxpp::impl {

auto Xml::Element::attribute(Attribute::Name name) const -> Attribute
{
    if (auto attr{elem->first_attribute(get(name))})
        return Attribute{attr};

    throw Invalid_attribute{name};
}

auto Xml::Element::child(Name name) const -> Element
{
    if (auto child{elem->first_node(get(name))})
        return Element{child};

    throw Invalid_element{name};
}

} // namespace tmxpp::impl
