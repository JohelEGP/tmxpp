#ifndef TMXPP_FRAME_HPP
#define TMXPP_FRAME_HPP

#include <chrono>
#include <tmxpp/Tile_id.hpp>

namespace tmxpp {

struct Frame {
    using Duration = std::chrono::milliseconds;

    Tile_id local_id;
    Duration duration;
};

constexpr bool operator==(Frame l, Frame r) noexcept
{
    return l.local_id == r.local_id && l.duration == r.duration;
}

constexpr bool operator!=(Frame l, Frame r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_FRAME_HPP
