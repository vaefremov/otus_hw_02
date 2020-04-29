#include <iostream>
#include <string>
#include <vector>
#include <range/v3/range/conversion.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/view/transform.hpp>
#include <range/v3/view/concat.hpp>
#include <range/v3/action/sort.hpp>
#include <range/v3/action/unique.hpp>

#include "utilities.h"

using namespace OTUS;
using namespace ranges;

static inline bool pred_1(const IP4& ip)
{
  return std::get<0>(ip) == 1;
}

static inline bool pred_2(const IP4& ip)
{
  return std::get<0>(ip) == 46 && std::get<1>(ip) == 70;
}

static inline bool pred_3(const IP4& ip)
{
  return std::get<0>(ip) == 46 || std::get<1>(ip) == 46 || std::get<2>(ip) == 46 || std::get<3>(ip) == 46;
}



VIP<IP4>& OTUS::hw2_ranges(VIP<IP4>& ip_pool)
{
    actions::sort(ip_pool, std::greater<OTUS::IP4>());
    auto tmp1 = views::all(ip_pool) | views::filter(pred_1);
    auto tmp2 = views::all(ip_pool) | views::filter(pred_2);
    auto tmp3 = views::all(ip_pool) | views::filter(pred_3);

    // The following 3 lines if uncommented cause cryptic errors on gcc 5.4, like
    // /tmp/ccTpJzbe.s: Assembler messages:
    // /tmp/ccTpJzbe.s:65048: Error: symbol `_ZN4meta6detailL9is_trait_E' is already defined
    // /tmp/ccTpJzbe.s:65476: Error: symbol `_ZN4meta6detailL9is_trait_E' is already defined
    // So I had to replace labdas with static predicates
    // Lines causing errors:
    // auto tmp1 = ip_pool | views::filter([](const IP4& ip){return std::get<0>(ip) == 1;});
    // auto tmp2 = ip_pool | views::filter([](const IP4& ip){return std::get<0>(ip) == 46 && std::get<1>(ip) == 70;});
    // auto tmp3 = ip_pool | views::filter([](const IP4& ip){return std::get<0>(ip) == 46 || std::get<1>(ip) == 46 || std::get<2>(ip) == 46 || std::get<3>(ip) == 46;});

   auto tmp4 = views::concat(ip_pool, tmp1, tmp2, tmp3);
   ip_pool = ranges::to<VIP<IP4>>(tmp4);
    return ip_pool;
}
