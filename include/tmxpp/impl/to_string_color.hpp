#ifndef TMXPP_IMPL_TO_STRING_COLOR_HPP
#define TMXPP_IMPL_TO_STRING_COLOR_HPP

#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>
#include <tmxpp/Color.hpp>

namespace tmxpp::impl {

std::string to_string(Color c)
{
    using Channels = std::uint_least32_t;

    Channels channels{static_cast<Channels>(c.a) << 24 |
                      static_cast<Channels>(c.r) << 16 |
                      static_cast<Channels>(c.g) << 8 | c.b};

    std::stringstream ss;
    ss << std::hex << channels;

    auto hex{ss.str()};

    std::string s{"#00000000"};
    std::copy_backward(hex.begin(), hex.end(), s.end());

    return s;
}

} // namespace tmxpp::impl

#endif // TMXPP_IMPL_TO_STRING_COLOR_HPP
