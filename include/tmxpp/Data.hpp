#ifndef TMXPP_DATA_HPP
#define TMXPP_DATA_HPP

#include <optional>
#include <vector>
#include <tmxpp/Tile_id.hpp>
#include <tmxpp/exceptions.hpp>

namespace tmxpp {

struct Data {
    enum class Encoding : unsigned char { csv, base64 };
    enum class Compression : unsigned char { none, zlib };

    class Format {
    public:
        [[implicit]] constexpr Format(
            Encoding e, Compression c = Compression::none)
          : encoding_{e}, compression_{c}
        {
            check_invariant(e, c);
        }

        constexpr Encoding encoding() const noexcept
        {
            return encoding_;
        }
        constexpr void encoding(Encoding e) noexcept
        {
            encoding_ = e;
            if (encoding_ == Encoding::csv)
                compression_ = Compression::none;
        }

        constexpr Compression compression() const noexcept
        {
            return compression_;
        }
        constexpr void compression(Compression c)
        {
            check_invariant(encoding_, c);
            compression_ = c;
        }

    private:
        static constexpr void check_invariant(Encoding e, Compression c)
        {
            if (e == Encoding::csv && c != Compression::none)
                throw Invalid_argument{"Bad Data::Format."};
        }

        Encoding encoding_;
        Compression compression_;
    };

    using Flipped_ids = std::vector<std::optional<Flipped_tile_id>>;

    Format format;
    Flipped_ids ids;
};

constexpr bool operator==(Data::Format l, Data::Format r) noexcept
{
    return l.encoding() == r.encoding() && l.compression() == r.compression();
}
constexpr bool operator!=(Data::Format l, Data::Format r) noexcept
{
    return !(l == r);
}

inline bool operator==(const Data& l, const Data& r) noexcept
{
    return l.format == r.format && l.ids == r.ids;
}
inline bool operator!=(const Data& l, const Data& r) noexcept
{
    return !(l == r);
}

} // namespace tmxpp

#endif // TMXPP_DATA_HPP
