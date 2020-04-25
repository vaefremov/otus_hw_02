#pragma once

#include <algorithm>
#include <istream>
#include <iterator>
#include <ostream>
#include <string>
#include <tuple>
#include <vector>

namespace OTUS {
using IP4 = std::tuple<unsigned char, unsigned char, unsigned char, unsigned char>;
template<typename IPrepr> using VIP = std::vector<IPrepr>;

std::string version_str();
std::vector<IP4> scan_ip4(std::istream& in, size_t column = 0);
std::string ip_to_string(const IP4& ip);
template <typename T>
void output_ips(std::ostream& out, const std::vector<T>& ips)
{
    std::transform(ips.cbegin(), ips.cend(),
        std::ostream_iterator<std::string>(out, "\n"),
        [](const T& ip) { return ip_to_string(ip); });
}
VIP<IP4>& hw2_stl(VIP<IP4>& ips);
}