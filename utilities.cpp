#include "utilities.h"

#include <iostream>
#include <sstream>
#include <sstream>
#include <exception>

std::vector<std::string>  OTUS::split(const std::string &str, char d)
{
    // std::vector<std::string> r;

    // decltype(str.find_first_of(d)) start = 0;
    // auto stop = str.find_first_of(d);
    // while(stop != std::string::npos)
    // {
    //     r.push_back(str.substr(start, stop - start));

    //     start = stop + 1;
    //     stop = str.find_first_of(d, start);
    // }

    // r.push_back(str.substr(start));

    // return r;
  std::stringstream ss(str);
  std::string item;
  std::vector<std::string> elems;
  while (std::getline(ss, item, d)) {
    elems.push_back(std::move(item));
  }
  return elems;
}

OTUS::IP4 OTUS::string_to_ip(const std::string &str)
{
  std::stringstream ss(str);
  std::string item;
  std::vector<int> elems;
  while (std::getline(ss, item, '.')) {
    elems.push_back(std::stoi(item));
  }
    if (elems.size() != 4)
    {
        throw std::invalid_argument("Invalid IP address");
    }
  return std::make_tuple(elems.at(0), elems.at(1), elems.at(2), elems.at(3));
}

std::string OTUS::ip_to_string(const IP4& ip)
{
    std::ostringstream ss;
    ss << std::get<0>(ip) << ".";
    ss << std::get<1>(ip) << ".";
    ss << std::get<2>(ip) << ".";
    ss << std::get<3>(ip);
    return ss.str();
}