#ifndef TMXPP_LAYER_HPP
#define TMXPP_LAYER_HPP

#include <string>
#include <tmxpp/Offset.hpp>
#include <tmxpp/Properties.hpp>
#include <tmxpp/Unit_interval.hpp>

namespace tmxpp {

struct Layer {
    std::string name;
    Unit_interval opacity;
    bool visible;
    Offset offset;
    Properties properties;
};

inline bool operator==(const Layer& l, const Layer& r) noexcept
{
    return l.name == r.name && l.opacity == r.opacity &&
           l.visible == r.visible && l.offset == r.offset &&
           l.properties == r.properties;
}

inline bool operator!=(const Layer& l, const Layer& r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_LAYER_HPP
