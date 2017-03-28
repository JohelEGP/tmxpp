# <a name="tmxpp"/>1 TMX++ library [tmxpp]

This Clause describes components that C++ programs may use to perform input/output operations of [TMX](http://doc.mapeditor.org/reference/tmx-map-format/) and [TSX](http://doc.mapeditor.org/reference/tmx-map-format/#tileset) documents.

The following subclauses describe the TMX-format abstracting types, I/O functions, utilities, and exception types, as summarized in Table [1](#table-1).

<a name="table-1"/>Table 1 -- TMX++ library summary

 . | Subclause | Header(s)
--- | --- | ---
[1.1](#tmxpp_hpp) | Convenience header | `<tmxpp.hpp>`
[1.2](#type) | TMX-format abstracting types | `<tmxpp/Map.hpp>`<br/>`<tmxpp/Image_layer.hpp>`<br/>`<tmxpp/Object_layer.hpp>`<br/>`<tmxpp/Object.hpp>`<br/>`<tmxpp/Point.hpp>`<br/>`<tmxpp/Degrees.hpp>`<br/>`<tmxpp/Unique_id.hpp>`<br/>`<tmxpp/Tile_layer.hpp>`<br/>`<tmxpp/Layer.hpp>`<br/>`<tmxpp/Unit_interval.hpp>`<br/>`<tmxpp/Data.hpp>`<br/>`<tmxpp/Image_collection.hpp>`<br/>`<tmxpp/Tile_set.hpp>`<br/>`<tmxpp/Offset.hpp>`<br/>`<tmxpp/Animation.hpp>`<br/>`<tmxpp/Frame.hpp>`<br/>`<tmxpp/Tile_id.hpp>`<br/>`<tmxpp/Flip.hpp>`<br/>`<tmxpp/Image.hpp>`<br/>`<tmxpp/Size.hpp>`<br/>`<tmxpp/Pixels.hpp>`<br/>`<tmxpp/Properties.hpp>`<br/>`<tmxpp/Property.hpp>`<br/>`<tmxpp/File.hpp>`<br/>`<tmxpp/Color.hpp>`
[1.3](#io) | I/O functions | `<tmxpp/read.hpp>`<br/>`<tmxpp/write.hpp>`
[1.4](#utilities) | Utilities | `<tmxpp/Strong_typedef.hpp>`<br/>`<tmxpp/Constrained.hpp>`
[1.5](#exceptions) | Exception types | `<tmxpp/exceptions.hpp>`

## <a name="tmxpp_hpp"/>1.1 Convenience header [tmxpp_hpp]

This subclause provides the synopsis of the header `<tmxpp.hpp>`, which includes the headers of the TMX-format abstracting types ([1.2](#type)) and I/O functions ([1.3](#io)).

### <a name="tmxpp_hpp.syn"/>1.1.1 Header `<tmxpp.hpp>` synopsis [tmxpp_hpp.syn]

```C++
// 1.2, TMX-format abstracting types
#include <tmxpp/Map.hpp>
#include <tmxpp/Image_layer.hpp>
#include <tmxpp/Object_layer.hpp>
#include <tmxpp/Object.hpp>
#include <tmxpp/Point.hpp>
#include <tmxpp/Degrees.hpp>
#include <tmxpp/Unique_id.hpp>
#include <tmxpp/Tile_layer.hpp>
#include <tmxpp/Layer.hpp>
#include <tmxpp/Unit_interval.hpp>
#include <tmxpp/Data.hpp>
#include <tmxpp/Image_collection.hpp>
#include <tmxpp/Tile_set.hpp>
#include <tmxpp/Offset.hpp>
#include <tmxpp/Animation.hpp>
#include <tmxpp/Frame.hpp>
#include <tmxpp/Tile_id.hpp>
#include <tmxpp/Flip.hpp>
#include <tmxpp/Image.hpp>
#include <tmxpp/Size.hpp>
#include <tmxpp/Pixels.hpp>
#include <tmxpp/Properties.hpp>
#include <tmxpp/Property.hpp>
#include <tmxpp/File.hpp>
#include <tmxpp/Color.hpp>

// 1.3, I/O functions
#include <tmxpp/read.hpp>
#include <tmxpp/write.hpp>
```

## <a name="type"/>1.2 TMX-format abstracting types [type]

This subclause describes the types that abstract the TMX format.

Unless otherwise specified,

- the structs' equality operators return the equality for each base or member subobject.
- empty structs compare equal.

### <a name="type.map.syn"/>1.2.1 Header `<tmxpp/Map.hpp>` synopsis [type.map.syn]

```C++
namespace tmxpp {

// 1.2.26
struct Map;

constexpr bool operator==(Map::Orthogonal, Map::Orthogonal) noexcept;
constexpr bool operator!=(Map::Orthogonal, Map::Orthogonal) noexcept;

constexpr bool operator==(Map::Isometric, Map::Isometric) noexcept;
constexpr bool operator!=(Map::Isometric, Map::Isometric) noexcept;

constexpr bool operator==(Map::Staggered, Map::Staggered) noexcept;
constexpr bool operator!=(Map::Staggered, Map::Staggered) noexcept;

constexpr bool operator==(Map::Hexagonal, Map::Hexagonal) noexcept;
constexpr bool operator!=(Map::Hexagonal, Map::Hexagonal) noexcept;

bool operator==(const Map&, const Map&) noexcept;
bool operator!=(const Map&, const Map&) noexcept;

} // namespace tmxpp
```

### <a name="type.image_layer.syn"/>1.2.2 Header `<tmxpp/Image_layer.hpp>` synopsis [type.image_layer.syn]

```C++
namespace tmxpp {

// 1.2.27
struct Image_layer;

bool operator==(const Image_layer&, const Image_layer&) noexcept;
bool operator!=(const Image_layer&, const Image_layer&) noexcept;

} // namespace tmxpp
```

### <a name="type.object_layer.syn"/>1.2.3 Header `<tmxpp/Object_layer.hpp>` synopsis [type.object_layer.syn]

```C++
namespace tmxpp {

// 1.2.28
struct Object_layer;

bool operator==(const Object_layer&, const Object_layer&) noexcept;
bool operator!=(const Object_layer&, const Object_layer&) noexcept;

} // namespace tmxpp
```

### <a name="type.object.syn"/>1.2.4 Header `<tmxpp/Object.hpp>` synopsis [type.object.syn]

```C++
namespace tmxpp {

// 1.2.29
struct Object;

bool operator==(Object::Rectangle, Object::Rectangle) noexcept;
bool operator!=(Object::Rectangle, Object::Rectangle) noexcept;

bool operator==(Object::Ellipse, Object::Ellipse) noexcept;
bool operator!=(Object::Ellipse, Object::Ellipse) noexcept;

bool operator==(const Object::Polygon&, const Object::Polygon&) noexcept;
bool operator!=(const Object::Polygon&, const Object::Polygon&) noexcept;

bool operator==(const Object::Polyline&, const Object::Polyline&) noexcept;
bool operator!=(const Object::Polyline&, const Object::Polyline&) noexcept;

bool operator==(const Object&, const Object&) noexcept;
bool operator!=(const Object&, const Object&) noexcept;

} // namespace tmxpp
```

### <a name="type.point.syn"/>1.2.5 Header `<tmxpp/Point.hpp>` synopsis [type.point.syn]

```C++
namespace tmxpp {

// 1.2.30
struct Point;

constexpr bool operator==(Point, Point) noexcept;
constexpr bool operator!=(Point, Point) noexcept;

} // namespace tmxpp
```

### <a name="type.degrees.syn"/>1.2.6 Header `<tmxpp/Degrees.hpp>` synopsis [type.degrees.syn]

```C++
namespace tmxpp {

// 1.2.31
using Degrees = Strong_typedef<double, /*see below*/>;

} // namespace tmxpp
```

### <a name="type.unique_id.syn"/>1.2.7 Header `<tmxpp/Unique_id.hpp>` synopsis [type.unique_id.syn]

```C++
namespace tmxpp {

// 1.2.32
using Unique_id = Strong_typedef<Non_negative<int>, /*see below*/>;

} // namespace tmxpp
```

### <a name="type.tile_layer.syn"/>1.2.8 Header `<tmxpp/Tile_layer.hpp>` synopsis [type.tile_layer.syn]

```C++
namespace tmxpp {

// 1.2.33
struct Tile_layer;

bool operator==(const Tile_layer&, const Tile_layer&) noexcept;
bool operator!=(const Tile_layer&, const Tile_layer&) noexcept;

} // namespace tmxpp
```

### <a name="type.layer.syn"/>1.2.9 Header `<tmxpp/Layer.hpp>` synopsis [type.layer.syn]

```C++
namespace tmxpp {

// 1.2.34
struct Layer;

bool operator==(const Layer&, const Layer&) noexcept;
bool operator!=(const Layer&, const Layer&) noexcept;

} // namespace tmxpp
```

### <a name="type.unit_interval.syn"/>1.2.10 Header `<tmxpp/Unit_interval.hpp>` synopsis [type.unit_interval.syn]

```C++
namespace tmxpp {

// 1.2.35
using Unit_interval =
    Closed_interval<double, boost::hana::int_<0>, boost::hana::int_<1>>;

} // namespace tmxpp
```

### <a name="type.data.syn"/>1.2.11 Header `<tmxpp/Data.hpp>` synopsis [type.data.syn]

```C++
namespace tmxpp {

// 1.2.36
struct Data;

// 1.2.36.2
constexpr bool operator==(Data::Format, Data::Format) noexcept;
constexpr bool operator!=(Data::Format, Data::Format) noexcept;

bool operator==(const Data&, const Data&) noexcept;
bool operator!=(const Data&, const Data&) noexcept;

} // namespace tmxpp
```

### <a name="type.image_collection.syn"/>1.2.12 Header `<tmxpp/Image_collection.hpp>` synopsis [type.image_collection.syn]

```C++
namespace tmxpp {

// 1.2.37
struct Image_collection;

bool operator==(
    const Image_collection::Tile&, const Image_collection::Tile&) noexcept;
bool operator!=(
    const Image_collection::Tile&, const Image_collection::Tile&) noexcept;

bool operator==(const Image_collection&, const Image_collection&) noexcept;
bool operator!=(const Image_collection&, const Image_collection&) noexcept;

} // namespace tmxpp
```

### <a name="type.tile_set.syn"/>1.2.13 Header `<tmxpp/Tile_set.hpp>` synopsis [type.tile_set.syn]

```C++
namespace tmxpp {

// 1.2.38
struct Tile_set;

bool operator==(const Tile_set::Tile&, const Tile_set::Tile&) noexcept;
bool operator!=(const Tile_set::Tile&, const Tile_set::Tile&) noexcept;

bool operator==(const Tile_set&, const Tile_set&) noexcept;
bool operator!=(const Tile_set&, const Tile_set&) noexcept;

} // namespace tmxpp
```

### <a name="type.offset.syn"/>1.2.14 Header `<tmxpp/Offset.hpp>` synopsis [type.offset.syn]

```C++
namespace tmxpp {

// 1.2.39
struct Offset;

constexpr bool operator==(Offset, Offset) noexcept;
constexpr bool operator!=(Offset, Offset) noexcept;

} // namespace tmxpp
```

### <a name="type.animation.syn"/>1.2.15 Header `<tmxpp/Animation.hpp>` synopsis [type.animation.syn]

```C++
namespace tmxpp {

// 1.2.40
using Animation = std::vector<Frame>;

} // namespace tmxpp
```

### <a name="type.frame.syn"/>1.2.16 Header `<tmxpp/Frame.hpp>` synopsis [type.frame.syn]

```C++
namespace tmxpp {

// 1.2.41
struct Frame;

bool operator==(Frame, Frame) noexcept;
bool operator!=(Frame, Frame) noexcept;

} // namespace tmxpp
```

### <a name="type.tile_id.syn"/>1.2.17 Header `<tmxpp/Tile_id.hpp>` synopsis [type.tile_id.syn]

```C++
namespace tmxpp {

// 1.2.42.1
using Local_tile_id = Closed_interval<
    std::int_least32_t, boost::hana::long_<0>, boost::hana::long_<0x1FFF'FFFE>>;

// 1.2.42.2
using Global_tile_id = Closed_interval<
    std::int_least32_t, boost::hana::long_<1>, boost::hana::long_<0x1FFF'FFFF>>;

// 1.2.42.3
struct Flipped_tile_id;

bool operator==(Flipped_tile_id, Flipped_tile_id) noexcept;
bool operator!=(Flipped_tile_id, Flipped_tile_id) noexcept;

} // namespace tmxpp
```

### <a name="type.flip.syn"/>1.2.18 Header `<tmxpp/Flip.hpp>` synopsis [type.flip.syn]

```C++
namespace tmxpp {

// 1.2.43
enum class Flip : unsigned char;

constexpr Flip operator&(Flip, Flip) noexcept;
constexpr Flip operator|(Flip, Flip) noexcept;
constexpr Flip operator^(Flip, Flip) noexcept;

constexpr Flip operator~(Flip) noexcept;

constexpr Flip& operator&=(Flip&, Flip) noexcept;
constexpr Flip& operator|=(Flip&, Flip) noexcept;
constexpr Flip& operator^=(Flip&, Flip) noexcept;

} // namespace tmxpp
```

### <a name="type.image.syn"/>1.2.19 Header `<tmxpp/Image.hpp>` synopsis [type.image.syn]

```C++
namespace tmxpp {

// 1.2.44
struct Image;

bool operator==(const Image&, const Image&) noexcept;
bool operator!=(const Image&, const Image&) noexcept;

} // namespace tmxpp
```

### <a name="type.size.syn"/>1.2.20 Header `<tmxpp/Size.hpp>` synopsis [type.size.syn]

```C++
namespace tmxpp {

// 1.2.45
template <class T>
struct Size;

using pxSize = Size<Pixels>;
using iSize  = Size<int>;

template <class T>
bool operator==(Size<T>, Size<T>) noexcept;
template <class T>
bool operator!=(Size<T>, Size<T>) noexcept;

} // namespace tmxpp
```

### <a name="type.pixel.syn"/>1.2.21 Header `<tmxpp/Pixels.hpp>` synopsis [type.pixel.syn]

```C++
namespace tmxpp {

// 1.2.46
using Pixels = Strong_typedef<double, /*see below*/>;

} // namespace tmxpp
```

### <a name="type.properties.syn"/>1.2.22 Header `<tmxpp/Properties.hpp>` synopsis [type.properties.syn]

```C++
namespace tmxpp {

// 1.2.47
using Properties = std::vector<Property>;

} // namespace tmxpp
```

### <a name="type.property.syn"/>1.2.23 Header `<tmxpp/Property.hpp>` synopsis [type.property.syn]

```C++
namespace tmxpp {

// 1.2.48
struct Property;

bool operator==(const Property&, const Property&) noexcept;
bool operator!=(const Property&, const Property&) noexcept;

} // namespace tmxpp
```

### <a name="type.file.syn"/>1.2.24 Header `<tmxpp/File.hpp>` synopsis [type.file.syn]

```C++
namespace tmxpp {

// 1.2.49
using File = std::experimental::filesystem::path;

} // namespace tmxpp
```

### <a name="type.color.syn"/>1.2.25 Header `<tmxpp/Color.hpp>` synopsis [type.color.syn]

```C++
namespace tmxpp {

// 1.2.50
struct Color;

constexpr bool operator==(Color, Color) noexcept;
constexpr bool operator!=(Color, Color) noexcept;

} // namespace tmxpp
```

### <a name="type.map"/>1.2.26 Struct `Map` [type.map]

The struct `Map` represents the [`map`](http://doc.mapeditor.org/reference/tmx-map-format/#map) element of the TMX format.

```C++
struct Map {
    struct Orthogonal {
    };
    struct Isometric {
    };
    struct Staggered {
        enum class Axis : unsigned char { x, y };
        enum class Index : unsigned char { even, odd };
        Axis axis;
        Index index;
    };
    struct Hexagonal : Staggered {
        Pixels side_length;
    };

    using Orientation =
        std::variant<Orthogonal, Isometric, Staggered, Hexagonal>;

    enum class Render_order : unsigned char {
        right_down,
        right_up,
        left_down,
        left_up
    };

    using Tile_set  = std::variant<tmxpp::Tile_set, Image_collection>;
    using Tile_sets = std::vector<Tile_set>;

    using Layer  = std::variant<Tile_layer, Object_layer, Image_layer>;
    using Layers = std::vector<Layer>;

    std::string version;
    Orientation orientation;
    Render_order render_order;
    iSize size;
    pxSize general_tile_size;
    std::optional<Color> background;
    Unique_id next_id;
    Properties properties;
    Tile_sets tile_sets;
    Layers layers;
};
```

### <a name="type.image_layer"/>1.2.27 Struct `Image_layer` [type.image_layer]

The struct `Image_layer` represents the [`imagelayer`](http://doc.mapeditor.org/reference/tmx-map-format/#imagelayer) element of the TMX format.

```C++
struct Image_layer : Layer {
    std::optional<Image> image;
};
```

### <a name="type.object_layer"/>1.2.28 Struct `Object_layer` [type.object_layer]

The struct `Object_layer` represents the [`objectgroup`](http://doc.mapeditor.org/reference/tmx-map-format/#objectgroup) element of the TMX format.

```C++
struct Object_layer : Layer {
    enum class Draw_order : unsigned char { top_down, index };

    using Objects = std::vector<Object>;

    std::optional<Color> color;
    Draw_order draw_order;
    Objects objects;
};
```

### <a name="type.object"/>1.2.29 Struct `Object` [type.object]

The struct `Object` represents the [`object`](http://doc.mapeditor.org/reference/tmx-map-format/#object) element of the TMX format.

```C++
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
    std::optional<Shape> shape;
    Degrees clockwise_rotation;
    std::optional<Global_tile_id> global_id;
    bool visible;
    Properties properties;
};
```

### <a name="type.point"/>1.2.30 Struct `Point` [type.point]

The struct `Point` represents a two-dimensional point.

```C++
struct Point {
    using Coordinate = Pixels;

    Coordinate x;
    Coordinate y;
};
```

### <a name="type.degrees"/>1.2.31 Alias `Degrees` [type.degrees]

The alias `Degrees` represents degrees of arc.

```C++
using Degrees = Strong_typedef<double, /*see below*/>;
```

The second template argument to `Strong_typedef` is unique to this declaration.

### <a name="type.unique_id"/>1.2.32 Alias `Unique_id` [type.unique_id]

The alias `Unique_id` represents a unique identifier.

```C++
using Unique_id = Strong_typedef<Non_negative<int>, /*see below*/>;
```

The second template argument to `Strong_typedef` is unique to this declaration.

### <a name="type.tile_layer"/>1.2.33 Struct `Tile_layer` [type.tile_layer]

The struct `Tile_layer` represents the [`layer`](http://doc.mapeditor.org/reference/tmx-map-format/#layer) element of the TMX format.

```C++
struct Tile_layer : Layer {
    iSize size;
    Data data;
};
```

### <a name="type.layer"/>1.2.34 Struct `Layer` [type.layer]

The struct `Layer` stores the common members of the *`_layer` types.

```C++
struct Layer {
    std::string name;
    Unit_interval opacity;
    bool visible;
    Offset offset;
    Properties properties;
};
```

### <a name="type.unit_interval"/>1.2.35 Alias `Unit_interval` [type.unit_interval]

The alias `Unit_interval` represents a `double` in the [`0`,`1`] interval.

```C++
using Unit_interval =
    Closed_interval<double, boost::hana::int_<0>, boost::hana::int_<1>>;
```

### <a name="type.data"/>1.2.36 Struct `Data` [type.data]

The struct `Data` represents the [`data`](http://doc.mapeditor.org/reference/tmx-map-format/#data) element of the TMX format.

```C++
struct Data {
    enum class Encoding : unsigned char { csv, base64 };
    enum class Compression : unsigned char { none, zlib };

    // 1.2.36.1
    class Format;

    using Flipped_ids = std::vector<std::optional<Flipped_tile_id>>;

    Format format;
    Flipped_ids ids;
};
```

#### <a name="type.data.format"/>1.2.36.1 Class `Data::Format` [type.data.format]

The class `Data::Format` represents an (`Encoding`, `Compression`) ordered pair.

```C++
class Format {
public:
    // 1.2.36.1.1, constructor
    [[implicit]] constexpr Format(Encoding, Compression = Compression::none);

    // 1.2.36.1.2, modifiers
    constexpr void encoding(Encoding) noexcept;
    constexpr void compression(Compression);

    constexpr Encoding encoding() const noexcept;
    constexpr Compression compression() const noexcept;
};
```

When the encoding is `csv`, the only valid compression is `none`.

##### <a name="type.data.format.constructor"/>1.2.36.1.1 `Format` constructor [type.data.format.constructor]

```C++
constexpr Format(Encoding e, Compression c = Compression::none);
```

_Requires:_ `e != Encoding::csv || c == Compression::none` is `true`.<br/>
_Postconditions:_ `encoding() == e && compression() == c` is `true`.<br/>
_Throws:_ `Invalid_argument` if `e == Encoding::csv && c != Compression::none` is `true`.

##### <a name="type.data.format.modifiers"/>1.2.36.1.2 `Format` modifiers [type.data.format.modifiers]

```C++
constexpr void encoding(Encoding e) noexcept;
```

_Postconditions:_

- `encoding() == e` is `true`.
- If `e == Encoding::csv` is `true`, then `compression() == Compression::none` is `true`.

```C++
constexpr void compression(Compression c);
```

_Requires:_ `encoding() != Encoding::csv || c == Compression::none` is `true`.<br/>
_Postconditions:_ `compression() == c` is `true`.<br/>
_Throws:_ `Invalid_argument` if `encoding() == Encoding::csv && c != Compression::none` is `true`.<br/>
_Remarks:_ If an exception is thrown there are no postconditions.

#### <a name="type.data.comp"/>1.2.36.2 Comparison operators [type.data.comp]

```C++
constexpr bool operator==(Data::Format l, Data::Format r) noexcept;
```

_Returns:_ `l.encoding() == r.encoding() && l.compression() == r.compression()`.

```C++
constexpr bool operator!=(Data::Format l, Data::Format r) noexcept;
```

_Returns:_ `!(l == r)`.

### <a name="type.image_collection"/>1.2.37 Struct `Image_collection` [type.image_collection]

The struct `Image_collection` represents the [`tileset`](http://doc.mapeditor.org/reference/tmx-map-format/#tileset) element of the TMX format when used as an image collection.

```C++
struct Image_collection {
    // 1.2.37.1
    struct Tile;

    using Tiles = std::vector<Tile>;

    Global_tile_id first_id;
    File tsx;
    std::string name;
    pxSize max_tile_size;
    Non_negative<int> tile_count;
    Non_negative<int> columns;
    Offset tile_offset;
    Properties properties;
    Tiles tiles;
};
```

#### <a name="type.image_collection.tile"/>1.2.37.1 Struct `Image_collection::Tile` [type.image_collection.tile]

The struct `Image_collection::Tile` represents the [`tile`](http://doc.mapeditor.org/reference/tmx-map-format/#tile) element of the TMX format when it is child of an image collection.

```C++
struct Tile {
    Local_tile_id id;
    Properties properties;
    Image image;
    std::optional<Object_layer> collision_shape;
    Animation animation;
};
```

### <a name="type.tile_set"/>1.2.38 Struct `Tile_set` [type.tile_set]

The struct `Tile_set` represents the [`tileset`](http://doc.mapeditor.org/reference/tmx-map-format/#tileset) element of the TMX format when used as a tile set.

```C++
struct Tile_set {
    // 1.2.38.1
    struct Tile;

    using Tiles = std::vector<Tile>;

    Global_tile_id first_id;
    File tsx;
    std::string name;
    pxSize tile_size;
    Non_negative<Pixels> spacing;
    Non_negative<Pixels> margin;
    iSize size;
    Offset tile_offset;
    Properties properties;
    Image image;
    Tiles tiles;
};
```

#### <a name="type.tile_set.tile"/>1.2.38.1 Struct `Tile_set::Tile` [type.tile_set.tile]

The struct `Tile_set::Tile` represents the [`tile`](http://doc.mapeditor.org/reference/tmx-map-format/#tile) element of the TMX format when it is child of a tile set.

```C++
struct Tile {
    Local_tile_id id;
    Properties properties;
    std::optional<Object_layer> collision_shape;
    Animation animation;
};
```

### <a name="type.offset"/>1.2.39 Struct `Offset` [type.offset]

The struct `Offset` represents a drawing offset.

```C++
struct Offset {
    Pixels x;
    Pixels y;
};
```

### <a name="type.animation"/>1.2.40 Alias `Animation` [type.animation]

The alias `Animation` represents the [`animation`](http://doc.mapeditor.org/reference/tmx-map-format/#animation) element of the TMX format.

```C++
using Animation = std::vector<Frame>;
```

### <a name="type.frame"/>1.2.41 Struct `Frame` [type.frame]

The struct `Frame` represents the [`frame`](http://doc.mapeditor.org/reference/tmx-map-format/#frame) element of the TMX format.

```C++
struct Frame {
    using Duration =
        std::chrono::duration<int, std::chrono::milliseconds::period>;

    Local_tile_id id;
    Non_negative<Duration> duration;
};
```

### <a name="type.tile_id"/>1.2.42 Tile id types [type.tile_id]

The tile id types abstract the different tile ids of the TMX format.

#### <a name="type.tile_id.local"/>1.2.42.1 Alias `Local_tile_id` [type.tile_id.local]

The alias `Local_tile_id` represents the identifier of a tile in the containing [`tileset`](http://doc.mapeditor.org/reference/tmx-map-format/#tileset) element of the TMX format.

```C++
using Local_tile_id = Closed_interval<
    std::int_least32_t, boost::hana::long_<0>, boost::hana::long_<0x1FFF'FFFE>>;
```

#### <a name="type.tile_id.global"/>1.2.42.2 Alias `Global_tile_id` [type.tile_id.global]

The alias `Global_tile_id` represents the identifier of a tile in any of the [`tileset`](http://doc.mapeditor.org/reference/tmx-map-format/#tileset) elements in the containing [`map`](http://doc.mapeditor.org/reference/tmx-map-format/#map) element of the TMX format.

```C++
using Global_tile_id = Closed_interval<
    std::int_least32_t, boost::hana::long_<1>, boost::hana::long_<0x1FFF'FFFF>>;
```

#### <a name="type.tile_id.flipped"/>1.2.42.3 Struct `Flipped_tile_id` [type.tile_id.flipped]

The struct `Flipped_tile_id` represents the tile ids stored in the [`data`](http://doc.mapeditor.org/reference/tmx-map-format/#data) element of the TMX format.

```C++
struct Flipped_tile_id {
    Flip flip;
    Global_tile_id id;
};
```

### <a name="type.flip"/>1.2.43 Enum class `Flip` [type.flip]

The enum class `Flip` is a [bitmask type](http://en.cppreference.com/w/cpp/concept/BitmaskType) for stating how a tile is to be flipped.

```C++
enum class Flip : unsigned char {
    horizontal = 0b100,
    vertical   = 0b010,
    diagonal   = 0b001
};
```

### <a name="type.image"/>1.2.44 Struct `Image` [type.image]

The struct `Image` represents the [`image`](http://doc.mapeditor.org/reference/tmx-map-format/#image) element of the TMX format.

```C++
struct Image {
    File source;
    std::optional<Color> transparent;
    std::optional<pxSize> size;
};
```

### <a name="type.size"/>1.2.45 Class template `Size` [type.size]

The class template `Size` describes a (width, height) ordered pair.

```C++
template <class T>
struct Size {
    using Dimension = Positive<T>;

    Dimension w;
    Dimension h;
};
```

### <a name="type.pixel"/>1.2.46 Alias `Pixels` [type.pixel]

The alias `Pixels` represents a unit of measurement for pixels.

```C++
using Pixels = Strong_typedef<double, /*see below*/>;
```

The second template argument to `Strong_typedef` is unique to this declaration.

### <a name="type.properties"/>1.2.47 Alias `Properties` [type.properties]

The alias `Properties` represents the [`properties`](http://doc.mapeditor.org/reference/tmx-map-format/#properties) element of the TMX format.

```C++
using Properties = std::vector<Property>;
```

### <a name="type.property"/>1.2.48 Struct `Property` [type.property]

The struct `Property` represents the [`property`](http://doc.mapeditor.org/reference/tmx-map-format/#property) element of the TMX format.

```C++
struct Property {
    using Value = std::variant<std::string, int, double, bool, Color, File>;

    Non_empty<std::string> name;
    Value value;
};
```

### <a name="type.file"/>1.2.49 Alias `File` [type.file]

The alias `File` represents a path to a file.

```C++
using File = std::experimental::filesystem::path;
```

### <a name="type.color"/>1.2.50 Struct `Color` [type.color]

The struct `Color` represents an ARGB color.

```C++
struct Color {
    using Channel = std::uint_least8_t;

    Channel a;
    Channel r;
    Channel g;
    Channel b;
};
```

## <a name="io"/>1.3 I/O functions [io]

This subclause describes the functions used to perform input/output of [TMX](http://doc.mapeditor.org/reference/tmx-map-format/) and [TSX](http://doc.mapeditor.org/reference/tmx-map-format/#tileset) documents.

### <a name="io.read.syn"/>1.3.1 Header `<tmxpp/read.hpp>` synopsis [io.read.syn]

```C++
namespace tmxpp {

// 1.3.3
Map read_tmx(const std::experimental::filesystem::path&);

// 1.3.3
Map::Tile_set read_tsx(
    Global_tile_id first_id, File tsx,
    const std::experimental::filesystem::path& base =
        std::experimental::filesystem::current_path());
Tile_set read_tile_set(
    Global_tile_id first_id, File tsx,
    const std::experimental::filesystem::path& base =
        std::experimental::filesystem::current_path());
Image_collection read_image_collection(
    Global_tile_id first_id, File tsx,
    const std::experimental::filesystem::path& base =
        std::experimental::filesystem::current_path());

} // namespace tmxpp
```

### <a name="io.write.syn"/>1.3.2 Header `<tmxpp/write.hpp>` synopsis [io.write.syn]

```C++
namespace tmxpp {

// 1.3.4
void write(const Map&, const std::experimental::filesystem::path&);

// 1.3.4
template <class Tile_set_>
void write(
    const Tile_set_&, const std::experimental::filesystem::path& base =
                          std::experimental::filesystem::current_path());

} // namespace tmxpp
```

### <a name="io.read"/>1.3.3 Read functions [io.read]

```C++
Map read_tmx(const std::experimental::filesystem::path& tmx);
```

_Returns:_ The read TMX `tmx` as a `Map`.<br/>
_Throws:_ `Exception` in case of error.

```C++
Map::Tile_set read_tsx(
    Global_tile_id first_id, File tsx,
    const std::experimental::filesystem::path& base =
        std::experimental::filesystem::current_path());
```

_Returns:_ The read TSX `absolute(tsx, base)` as a `Map::Tile_set` whose alternative has the given `first_id` and `tsx`.<br/>
_Throws:_ `Exception` in case of error.

```C++
Tile_set read_tile_set(
    Global_tile_id first_id, File tsx,
    const std::experimental::filesystem::path& base =
        std::experimental::filesystem::current_path());
```

_Returns:_ The read TSX `absolute(tsx, base)` as a `Tile_set` with the given `first_id` and `tsx`.<br/>
_Throws:_ `Exception` in case of error.

```C++
Image_collection read_image_collection(
    Global_tile_id first_id, File tsx,
    const std::experimental::filesystem::path& base =
        std::experimental::filesystem::current_path());
```

_Returns:_ The read TSX `absolute(tsx, base)` as an `Image_collection` with the given `first_id` and `tsx`.<br/>
_Throws:_ `Exception` in case of error.

### <a name="io.write"/>1.3.4 Write functions [io.write]

```C++
void write(const Map& map, const std::experimental::filesystem::path& tmx);
```

_Effects:_ Writes `map` as the TMX `tmx`.<br/>
_Throws:_ `Exception` in case of error.

```C++
template <class Tile_set_>
void write(
    const Tile_set_& tset, const std::experimental::filesystem::path& base =
                               std::experimental::filesystem::current_path());
```

_Effects:_ Writes `tset` as the TSX `absolute(tset.tsx, base)`.<br/>
_Throws:_ `Exception` in case of error.<br/>
_Remarks:_ This function shall not participate in overload resolution unless `Tile_set_` is `Map::Tile_set`, `Tile_set`, or `Image_collection`.

## <a name="utilities"/>1.4 Utilities [utilities]

This subclause describes utilities used to simplify the definition of the TMX-format abstracting types ([1.2](#type)).

### <a name="utilities.strong_typedef.syn"/>1.4.1 Header `<tmxpp/Strong_typedef.hpp>` synopsis [utilities.strong_typedef.syn]

```C++
#include <type_safe/strong_typedef.hpp>

namespace tmxpp {

// 1.4.3
template <class T, class Phantom>
class Strong_typedef;

} // namespace tmxpp
```

### <a name="utilities.constrained.syn"/>1.4.2 Header `<tmxpp/Constrained.hpp>` synopsis [utilities.constrained.syn]

```C++
#include <type_safe/constrained_type.hpp>

namespace tmxpp {

// 1.4.4.1
struct Verifier;

template <class T, class Constraint>
using Constrained = type_safe::constrained_type<T, Constraint, Verifier>;

template <class T>
using Non_empty = Constrained<T, type_safe::constraints::non_empty>;

template <class T, class LowerConstant, class UpperConstant>
using Closed_interval = Constrained<
    T, type_safe::constraints::closed_interval<
           jegp::Value_type<LowerConstant>, LowerConstant, UpperConstant>>;

template <class T, class ZeroConstant = jegp::Literal_constant<T>>
using Positive = Constrained<
    T, type_safe::constraints::greater<
           jegp::Value_type<ZeroConstant>, ZeroConstant>>;

template <class T, class ZeroConstant = jegp::Literal_constant<T>>
using Non_negative = Constrained<
    T, type_safe::constraints::greater_equal<
           jegp::Value_type<ZeroConstant>, ZeroConstant>>;

} // namespace tmxpp
```

### <a name="utilities.strong_typedef"/>1.4.3 Class template `Strong_typedef` [utilities.strong_typedef]

The class template `Strong_typedef` is a convenience wrapper over [`type_safe::strong_typedef`](http://foonathan.net/doc/type_safe/doc_strong_typedef.html#ts::strong_typedef-Tag,T-).

```C++
template <class T, class Phantom>
class Strong_typedef
  : public type_safe::strong_typedef<Phantom, T>
  , public type_safe::strong_typedef_op::equality_comparison<
        Strong_typedef<T, Phantom>>
  , public type_safe::strong_typedef_op::relational_comparison<
        Strong_typedef<T, Phantom>> {
public:
    using type_safe::strong_typedef<Phantom, T>::strong_typedef;
};
```

### <a name="utilities.constrained"/>1.4.4 `Constrained` components [utilities.constrained]

The header `<tmxpp/Constrained.hpp>` declares alias templates to [`type_safe::constrained_type`](http://foonathan.net/doc/type_safe/doc_constrained_type.html#ts::constrained_type-T,Constraint,Verifier-).

#### <a name="utilities.constrained.verifier"/>1.4.4.1 Struct `Verifier` [utilities.constrained.verifier]

The struct `Verifier` is the [`Verifier`](http://foonathan.net/doc/type_safe/doc_constrained_type.html#ts::constrained_type-T,Constraint,Verifier-) used by `Constrained`.

```C++
struct Verifier {
    template <class T, class Predicate>
    static void verify(const T&, const Predicate&);
};
```

##### <a name="utilities.constrained.verifier.verify"/>1.4.4.1.1 Member function `verify` [utilities.constrained.verifier.verify]

```C++
template <class T, class Predicate>
static void verify(const T& value, const Predicate& pred);
```

_Throws:_ `Invalid_argument` if `pred(value)` is `false`.

## <a name="exceptions"/>1.5 Exception types [exceptions]

This subclause describes the exception types thrown by the types and functions in TMX++.

### <a name="exceptions.syn"/>1.5.1 Header `<tmxpp/exceptions.hpp>` synopsis [exceptions.syn]

```C++
namespace tmxpp {

// 1.5.2
class Exception;

// 1.5.3
class Invalid_argument;

} // namespace tmxpp
```

### <a name="exceptions.exception"/>1.5.2 Class `Exception` [exceptions.exception]

The class `Exception` is thrown by the I/O functions ([1.3](#io)).

```C++
class Exception : public std::exception {
public:
    explicit Exception(std::string what) noexcept;

    const char* what() const noexcept override;
};
```

### <a name="exceptions.exception.constructor"/>1.5.2.1 `Exception` constructor [exceptions.exception.constructor]

```C++
Exception(std::string what) noexcept;
```

_Postconditions:_ `this->what() == what` is `true`.

### <a name="exceptions.invalid_argument"/>1.5.3 Class `Invalid_argument` [exceptions.invalid_argument]

The class `Invalid_argument` is thrown by the the `Verifier` ([1.4.4.1](#utilities.constrained.verifier)).

```C++
class Invalid_argument : public Exception {
public:
    using Exception::Exception;
};
```
