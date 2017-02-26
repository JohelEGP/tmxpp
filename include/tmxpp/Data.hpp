#ifndef TMXPP_DATA_HPP
#define TMXPP_DATA_HPP

#include <optional>
#include <vector>
#include <tmxpp/Flipped_global_id.hpp>

namespace tmxpp {

struct Data {
    enum class Encoding : unsigned char { csv, base64 };
    enum class Compression : unsigned char { none, zlib };

    using Flipped_global_ids = std::vector<std::optional<Flipped_global_id>>;

    Encoding encoding;
    Compression compression;
    Flipped_global_ids ids;
};

inline bool operator==(const Data& l, const Data& r) noexcept
{
    return l.encoding == r.encoding && l.compression == r.compression &&
           l.ids == r.ids;
}

inline bool operator!=(const Data& l, const Data& r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_DATA_HPP
