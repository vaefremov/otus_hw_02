#pragma once

#include <vector>
#include <string>
#include <tuple>

namespace OTUS {
   std::vector<std::string> split(const std::string &str, char d);
   typedef std::tuple<int, int, int, int> IP4;
    IP4 string_to_ip(const std::string &str);
    std::string ip_to_string(const IP4& ip);
}