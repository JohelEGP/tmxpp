#ifndef TMXPP_IMPL_TO_STRING_COLOR_HPP
#define TMXPP_IMPL_TO_STRING_COLOR_HPP

#include <algorithm>
#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>
#include <tmxpp/Color.hpp>
#include <tmxpp/exceptions.hpp>

namespace tmxpp::impl {

std::string to_string(Color c)
{
    auto checked = [](Color::Channel c) {
        if (c > 255)
            throw Exception{"Color::Channel value over 8 bits."};
        return c;
    };

    using Channels = std::uint_least32_t;

    Channels channels{static_cast<Channels>(checked(c.a)) << 24 |
                      static_cast<Channels>(checked(c.r)) << 16 |
                      static_cast<Channels>(checked(c.g)) << 8 | checked(c.b)};

    std::stringstream ss;
    ss << std::hex << channels;

    auto hex{ss.str()};

    std::string s{"#00000000"};
    std::copy_backward(hex.begin(), hex.end(), s.end());

    return s;
}

} // namespace tmxpp::impl

#endif // TMXPP_IMPL_TO_STRING_COLOR_HPP
