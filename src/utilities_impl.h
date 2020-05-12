#pragma once

#include "utilities.h"

#include <algorithm>
#include <istream>
#include <iterator>
#include <ostream>
#include <string>
#include <tuple>
#include <vector>

namespace OTUS {

// Auxilary functions used for input/output IPv4 addresses.
std::vector<std::string> split(const std::string& str, char d);
IP4 string_to_ip(const std::string& str);
}