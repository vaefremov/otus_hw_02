#include "utilities.h"
#include "utilities_impl.h"
#include "config.h"

#include <iostream>
#include <sstream>
#include <sstream>
#include <exception>

std::string OTUS::version_str() 
{
    return std::string(VERSION_NUMBER);
}


std::vector<OTUS::IP4> OTUS::scan_ip4(std::istream& in, size_t column)
{
    std::vector<OTUS::IP4> ip_pool;
    int line_no = 1;
    for (std::string line; std::getline(in, line); ++line_no)
    {
        try 
        {
          auto v = OTUS::split(line, '\t');
          if (v.size() <= column)
          {
            throw std::runtime_error("Number of columns is less than the specified column number");
          }
          ip_pool.push_back(OTUS::string_to_ip(v.at(column)));
        }
        catch(std::exception& ex)
        {
          std::cerr << "Warning, bad input string " << line_no << "." << column << ": " << line << std::endl;
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
    int tmp = std::stoi(item);
    if(tmp < 0 || tmp > 255)
    {
      throw std::invalid_argument("IP address element out of range");
    }
    elems.push_back(tmp);
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
    ss << static_cast<unsigned>(std::get<0>(ip)) << ".";
    ss << static_cast<unsigned>(std::get<1>(ip)) << ".";
    ss << static_cast<unsigned>(std::get<2>(ip)) << ".";
    ss << static_cast<unsigned>(std::get<3>(ip));
    return ss.str();
}