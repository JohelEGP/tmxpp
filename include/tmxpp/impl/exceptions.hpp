#ifndef TMXPP_IMPL_EXCEPTIONS_HPP
#define TMXPP_IMPL_EXCEPTIONS_HPP

#include <string>
#include <utility>
#include <jegp/utility.hpp>
#include <tmxpp/exceptions.hpp>
#include <tmxpp/impl/Xml.hpp>

namespace tmxpp::impl {

class Invalid_attribute : public Exception {
public:
    using Name  = Xml::Attribute::Name;
    using Value = Xml::Attribute::Value;

    explicit Invalid_attribute(Name);
    explicit Invalid_attribute(Name, Value);
};

class Invalid_element : public Exception {
public:
    using Name  = Xml::Element::Name;
    using Value = Xml::Element::Value;

    explicit Invalid_element(Name);
    explicit Invalid_element(Name, Value);
};

class Invalid_enum : public Exception {
public:
    template <class Enum>
    explicit Invalid_enum(std::string what1, Enum e)
      : Exception{std::move(what1) +
                  " Value: " + std::to_string(jegp::underlying(e))}
    {
    }
};

} // namespace tmxpp::impl

#endif // TMXPP_IMPL_EXCEPTIONS_HPP
