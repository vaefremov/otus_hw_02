#pragma once

#include <vector>
#include <string>
#include <tuple>
#include <ostream>

namespace OTUS {
   std::vector<std::string> split(const std::string &str, char d);
   typedef std::tuple<int, int, int, int> IP4;
    IP4 string_to_ip(const std::string &str);
    std::string ip_to_string(const IP4& ip);
    template <typename T> void output_ips(std::ostream& out, const std::vector<T>& ips)
    {
        for(const auto& v: ips)
        {
            out << ip_to_string(v) << std::endl;
        }
    }
}