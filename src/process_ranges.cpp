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

VIP<IP4>& OTUS::hw2_ranges(VIP<IP4>& ip_pool)
{
    actions::sort(ip_pool, std::greater<OTUS::IP4>());
    auto tmp1 = ip_pool | views::filter([](const IP4& ip){return std::get<0>(ip) == 1;});
    auto tmp2 = ip_pool | views::filter([](const IP4& ip){return std::get<0>(ip) == 46 && std::get<1>(ip) == 70;});
    auto tmp3 = ip_pool | views::filter([](const IP4& ip){return std::get<0>(ip) == 46 || std::get<1>(ip) == 46 || std::get<2>(ip) == 46 || std::get<3>(ip) == 46;});
    auto tmp4 = views::concat(ip_pool, tmp1, tmp2, tmp3);
    ip_pool = ranges::to<VIP<IP4>>(tmp4);
    return ip_pool;
}