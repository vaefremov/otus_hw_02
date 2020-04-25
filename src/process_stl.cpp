#include "utilities.h"

using namespace OTUS;

VIP<IP4>& OTUS::hw2_stl(VIP<IP4>& ip_pool)
{
    sort(ip_pool.begin(), ip_pool.end(), std::greater<OTUS::IP4>());

    auto original_sz = ip_pool.size();

    std::copy_if(ip_pool.cbegin(), std::next(ip_pool.cbegin(),original_sz), std::back_inserter(ip_pool),
        [](const auto& item) { return std::get<0>(item) == 1; });

    std::copy_if(ip_pool.cbegin(), ip_pool.cbegin() + original_sz, std::back_inserter(ip_pool),
        [](const auto& item) {
            return std::get<0>(item) == 46 && std::get<1>(item) == 70;
        });

    std::copy_if(ip_pool.cbegin(), ip_pool.cbegin() + original_sz, std::back_inserter(ip_pool),
        [](const auto& i) {
            return std::get<0>(i) == 46 || std::get<1>(i) == 46 || std::get<2>(i) == 46 || std::get<3>(i) == 46;
        });
    return ip_pool;
}