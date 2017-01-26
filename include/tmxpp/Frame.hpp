#ifndef TMXPP_FRAME_HPP
#define TMXPP_FRAME_HPP

#include <chrono>
#include <tmxpp/Tile_id.hpp>

namespace tmxpp {

struct Frame {
    Tile_id id;
    std::chrono::milliseconds duration;
};

constexpr bool operator==(Frame l, Frame r) noexcept
{
    return l.id == r.id && l.duration == r.duration;
}

constexpr bool operator!=(Frame l, Frame r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_FRAME_HPP
