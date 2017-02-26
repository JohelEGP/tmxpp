#ifndef TMXPP_IMPL_TO_STRING_FLIPPED_GLOBAL_IDS
#define TMXPP_IMPL_TO_STRING_FLIPPED_GLOBAL_IDS

#include <cstdint>
#include <string>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/chunk.hpp>
#include <range/v3/view/intersperse.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/view/transform.hpp>
#include <tmxpp/Data.hpp>
#include <tmxpp/Flipped_global_id.hpp>
#include <tmxpp/Size.hpp>
#include <tmxpp/exceptions.hpp>

namespace tmxpp::impl {

std::string to_string(Flipped_global_id fgid)
{
    using Raw_id = std::uint_least32_t;

    constexpr int first_flip_bit{29};

    Raw_id id{static_cast<Raw_id>(fgid.flip) << first_flip_bit |
              static_cast<Raw_id>(*fgid.id)};

    return std::to_string(id);
}

std::string to_string(const Data::Flipped_global_ids& ids, iSize sz)
{
    if (ids.size() / *sz.h - *sz.w != 0)
        throw Exception{"Data size does not match layer size."};

    auto data{ids | ranges::view::transform([](auto id) {
                  if (id)
                      return to_string(*id);
                  return std::string{'0'};
              }) |
              ranges::view::intersperse(std::string{','}) |
              ranges::view::chunk(2 * *sz.w) |
              ranges::view::join(std::string{'\n'})};

    return ranges::accumulate(data, std::string{'\n'}) + '\n';
}

} // namespace tmxpp::impl

#endif // TMXPP_IMPL_TO_STRING_FLIPPED_GLOBAL_IDS
