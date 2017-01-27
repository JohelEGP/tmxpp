#ifndef TMXPP_DATA_HPP
#define TMXPP_DATA_HPP

#include <vector>
#include <tmxpp/Flipped_gid.hpp>

namespace tmxpp {

struct Data {
    enum class Encoding : unsigned char { csv, base64 };
    enum class Compression : unsigned char { none, zlib };

    using Flipped_gids = std::vector<Flipped_gid>;

    Encoding encoding;
    Compression compression;
    Flipped_gids flipped_gids;
};

inline bool operator==(const Data& l, const Data& r) noexcept
{
    return l.encoding == r.encoding && l.compression == r.compression &&
           l.flipped_gids == r.flipped_gids;
}

inline bool operator!=(const Data& l, const Data& r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_DATA_HPP
