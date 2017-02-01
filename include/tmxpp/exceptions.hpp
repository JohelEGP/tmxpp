#ifndef TMXPP_EXCEPTIONS_HPP
#define TMXPP_EXCEPTIONS_HPP

#include <stdexcept>
#include <tmxpp/impl/Xml.hpp>

namespace tmxpp {

class Invalid_attribute : public std::invalid_argument {
public:
    using Name  = impl::Xml::Attribute::Name;
    using Value = impl::Xml::Attribute::Value;

    explicit Invalid_attribute(Name);
    explicit Invalid_attribute(Name, Value);
};

class Invalid_element : public std::invalid_argument {
public:
    using Name  = impl::Xml::Element::Name;
    using Value = impl::Xml::Element::Value;

    explicit Invalid_element(Name);
    explicit Invalid_element(Name, Value);
};

} // namespace tmxpp

#endif // TMXPP_EXCEPTIONS_HPP
