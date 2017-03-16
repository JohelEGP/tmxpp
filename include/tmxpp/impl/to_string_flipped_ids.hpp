#ifndef TMXPP_IMPL_TO_STRING_FLIPPED_IDS
#define TMXPP_IMPL_TO_STRING_FLIPPED_IDS

#include <string>
#include <range/v3/numeric/accumulate.hpp>
#include <range/v3/view/chunk.hpp>
#include <range/v3/view/intersperse.hpp>
#include <range/v3/view/join.hpp>
#include <range/v3/view/transform.hpp>
#include <tmxpp/Data.hpp>
#include <tmxpp/Size.hpp>
#include <tmxpp/exceptions.hpp>
#include <tmxpp/impl/Raw_tile_id.hpp>

namespace tmxpp::impl {

std::string to_string(const Data::Flipped_ids& ids, iSize sz)
{
    if (ids.size() / *sz.h - *sz.w != 0)
        throw Exception{"Data size does not match layer size."};

    auto data{ids | ranges::view::transform([](auto id) {
                  if (id)
                      return std::to_string(get(to_raw(*id)));
                  return std::string{'0'};
              }) |
              ranges::view::intersperse(std::string{','}) |
              ranges::view::chunk(2 * *sz.w) |
              ranges::view::join(std::string{'\n'})};

    return ranges::accumulate(data, std::string{'\n'}) + '\n';
}

} // namespace tmxpp::impl

#endif // TMXPP_IMPL_TO_STRING_FLIPPED_IDS
