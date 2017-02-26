#ifndef TMXPP_OBJECT_HPP
#define TMXPP_OBJECT_HPP

#include <optional>
#include <string>
#include <variant>
#include <vector>
#include <tmxpp/Degrees.hpp>
#include <tmxpp/Point.hpp>
#include <tmxpp/Properties.hpp>
#include <tmxpp/Size.hpp>
#include <tmxpp/Tile_id.hpp>
#include <tmxpp/Unique_id.hpp>

namespace tmxpp {

struct Object {
    struct Rectangle {
        pxSize size;
    };
    struct Ellipse {
        pxSize size;
    };
    struct Polygon {
        using Points = std::vector<Point>;
        Points points;
    };
    struct Polyline {
        using Points = Polygon::Points;
        Points points;
    };

    using Shape = std::variant<Rectangle, Ellipse, Polygon, Polyline>;

    Unique_id unique_id;
    std::string name;
    std::string type;
    Point position;
    Shape shape;
    Degrees clockwise_rotation;
    std::optional<Global_tile_id> global_id;
    bool visible;
    Properties properties;
};

inline bool operator==(Object::Rectangle l, Object::Rectangle r) noexcept
{
    return l.size == r.size;
}
inline bool operator!=(Object::Rectangle l, Object::Rectangle r) noexcept
{
    return !(l == r);
}

inline bool operator==(Object::Ellipse l, Object::Ellipse r) noexcept
{
    return l.size == r.size;
}
inline bool operator!=(Object::Ellipse l, Object::Ellipse r) noexcept
{
    return !(l == r);
}

inline bool
operator==(const Object::Polygon& l, const Object::Polygon& r) noexcept
{
    return l.points == r.points;
}
inline bool
operator!=(const Object::Polygon& l, const Object::Polygon& r) noexcept
{
    return !(l == r);
}

inline bool
operator==(const Object::Polyline& l, const Object::Polyline& r) noexcept
{
    return l.points == r.points;
}
inline bool
operator!=(const Object::Polyline& l, const Object::Polyline& r) noexcept
{
    return !(l == r);
}

inline bool operator==(const Object& l, const Object& r) noexcept
{
    return l.unique_id == r.unique_id && l.name == r.name && l.type == r.type &&
           l.position == r.position && l.shape == r.shape &&
           l.clockwise_rotation == r.clockwise_rotation &&
           l.global_id == r.global_id && l.visible == r.visible &&
           l.properties == r.properties;
}
inline bool operator!=(const Object& l, const Object& r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_OBJECT_HPP
