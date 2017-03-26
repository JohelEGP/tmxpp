# TMX++

[TMX](http://doc.mapeditor.org/reference/tmx-map-format/) & [TSX](http://doc.mapeditor.org/reference/tmx-map-format/#tileset) I/O library.

## Requirements

- C++17
- Libraries
    + [GSL](https://github.com/Microsoft/GSL)
    + [Boost.Hana](https://github.com/boostorg/hana)
    + [Range-v3](https://github.com/ericniebler/range-v3)
    + [type_safe](https://github.com/foonathan/type_safe)
    + [jegp](https://github.com/johelegp/jegp)
    + [johelegp/RapidXml](https://github.com/johelegp/RapidXml)
- [CMake](https://cmake.org/) to build TMX++

## Building TMX++

Running these CMake commands from the root directory of your TMX++ clone will compile and install it.

    cmake -E make_directory build
    cmake -E chdir build cmake .. -DCMAKE_BUILD_TYPE=Release
    cmake --build build --target install

## Using TMX++

After building, you can `#include <tmxpp.hpp>` and link with `tmxpp` to `read()` and `write()` TMXs and TSXs.

## Documentation

Coming soon.
