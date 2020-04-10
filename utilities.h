#pragma once

#include <vector>
#include <string>
#include <tuple>
#include <ostream>
#include <istream>
#include <algorithm>

namespace OTUS {
   typedef std::tuple<int, int, int, int> IP4;

   std::vector<std::string> split(const std::string &str, char d);

    std::vector<IP4> scan_ip4(std::istream& in, unsigned int column = 0);

    IP4 string_to_ip(const std::string &str);

    std::string ip_to_string(const IP4& ip);

    template <typename T> void output_ips(std::ostream& out, const std::vector<T>& ips)
    {
        std::transform(ips.begin(), ips.end(), 
            std::ostream_iterator<std::string>(out, "\n"),
            [](const T& ip){return ip_to_string(ip);}
        );
    }
}