#include "utilities.h"

#include <iostream>
#include <sstream>
#include <sstream>
#include <exception>

std::vector<OTUS::IP4> OTUS::scan_ip4(std::istream& in, unsigned int column)
{
    std::vector<OTUS::IP4> ip_pool;
    for (std::string line; std::getline(in, line);)
    {
        try 
        {
          std::vector<std::string> v = OTUS::split(line, '\t');
          ip_pool.push_back(OTUS::string_to_ip(v.at(column)));
        }
        catch(std::exception& ex)
        {
          std::cerr << "Warning, bad input string: " << line << std::endl;
          std::cerr << ex.what() << std::endl;
          continue;
        }
    }
    return ip_pool;
}

std::vector<std::string>  OTUS::split(const std::string &str, char d)
{
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
      throw std::invalid_argument("Incomplete IP address");
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