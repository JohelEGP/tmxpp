#ifndef TMXPP_FRAME_HPP
#define TMXPP_FRAME_HPP

#include <chrono>
#include <tmxpp/Constrained.hpp>
#include <tmxpp/Tile_id.hpp>

namespace tmxpp {

struct Frame {
    using Duration = std::chrono::milliseconds;

    Local_tile_id id;
    Non_negative<Duration> duration;
};

inline bool operator==(Frame l, Frame r) noexcept
{
    return l.id == r.id && l.duration == r.duration;
}

inline bool operator!=(Frame l, Frame r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_FRAME_HPP
