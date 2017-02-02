#ifndef TMXPP_IMPL_TO_COLOR_HPP
#define TMXPP_IMPL_TO_COLOR_HPP

#include <cstdint>
#include <ios>
#include <regex>
#include <sstream>
#include <string>
#include <string_view>
#include <tmxpp/exceptions.hpp>

namespace tmxpp::impl {

namespace color {

// Returns: `true` if `s` has the format of a TMX color, and `false` otherwise.
// Notes: A TMX color has the format "#AARRGGBB" or "#RRGGBB".
bool is_well_formatted(std::string_view s)
{
    static const std::regex format{"#[[:xdigit:]]{2}?[[:xdigit:]]{6}",
                                   std::regex::nosubs};

    return std::regex_match(s.begin(), s.end(), format);
}

// Requires: `is_well_formatted(color)`
// Returns: The hexadecimal substring in `color`.
constexpr std::string_view hex_substr(std::string_view color) noexcept
{
    return color.substr(1);
}

using Channels = std::uint_least32_t;

// Requires: `is_well_formatted(color)`
// Returns: `hex_substr(color)` as `Channels`.
// Throws: `Exception` if it could not be converted.
Channels to_channels(std::string_view color)
{
    std::stringstream ss;
    ss << std::noskipws << std::hex << hex_substr(color);
    Channels num;
    ss >> num;
    if (!ss || !ss.eof())
        throw Exception{"Hexadecimal " + std::string{hex_substr(color)} +
                        " could not be converted to Arithmetic."};
    return num;
}

// Requires: `is_well_formatted(color)`
// Returns: `true` if `color` has an alpha channel, and `false` otherwise.
constexpr bool has_alpha(std::string_view color) noexcept
{
    constexpr std::string_view format_with_alpha{"#AARRGGBB"};

    return color.size() == format_with_alpha.size();
}

Color to_color(std::string_view color)
{
    if (!is_well_formatted(color))
        throw Exception{"Color with bad format: " + std::string{color}};

    auto channels{to_channels(color)};

    constexpr Color::Channel default_alpha{255};

    return {
        has_alpha(color) ? static_cast<Color::Channel>(channels >> 24 & 0xFF)
                         : default_alpha,
        static_cast<Color::Channel>(channels >> 16 & 0xFF),
        static_cast<Color::Channel>(channels >> 8 & 0xFF),
        static_cast<Color::Channel>(channels & 0xFF),
    };
}

Color to_color(Xml::Attribute::Value value)
{
    return to_color(get(value));
}

} // namespace color

using color::to_color;

} // namespace tmxpp::impl

#endif // TMXPP_IMPL_TO_COLOR_HPP
