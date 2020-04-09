#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <string>
#include <sstream>
#include <iterator>
#include <vector>

#include "config.h"

auto split(const std::string &str, char d)
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

auto output_ip(const std::vector<std::string>& v)
{
    // std::ostringstream ss;
    // // ss << v.at(0) << "." << v.at(1) << "." << v.at(2) << "." << v.at(3);
    // std::copy(v.begin(), v.end(), std::ostream_iterator<std::string>(ss, "."));
    // return ss.str();
    std::string s = std::accumulate(std::next(v.begin()), v.end(), v.at(0),
                     [](const std::string& a, const std::string& b){
                           return a + "." + b;
                     });
    return s;
}

static void usage()
{
        std::cout << "Version: " << VERSION_NUMBER << std::endl;
        std::cout << "Usage: " << "ip_filter < input_file.txt" << std::endl;
        std::exit(1);
}

int main(int argc, char** argv) 
{
    if(argc > 1)
    {
        usage();
    }
    std::vector<std::vector<std::string> > ip_pool;
    for (std::string line; std::getline(std::cin, line);)
    {
        std::vector<std::string> v = split(line, '\t');
        ip_pool.push_back(split(v.at(0), '.'));
    }


    sort(ip_pool.begin(), ip_pool.end(), std::greater<std::vector<std::string>>());

    for (auto v: ip_pool)
    {
        std::cout << output_ip(v) << std::endl;
    }

    std::vector<std::vector<std::string> > ip_first_byte;
    std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(ip_first_byte),
    [](std::vector<std::string> item){return item.at(0) == "1";});
    for (auto v: ip_first_byte)
    {
        std::cout << output_ip(v) << std::endl;
    }

    std::vector<std::vector<std::string> > ip_two_bytes;
    std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(ip_two_bytes),
    [](std::vector<std::string> item){return item.at(0) == "46" && item.at(1) == "70";});
    for (auto v: ip_two_bytes)
    {
        std::cout << output_ip(v) << std::endl;
    }

    std::vector<std::vector<std::string> > ip_any_byte;
    std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(ip_any_byte),
        [](std::vector<std::string> item){
            return std::any_of(item.begin(), item.end(), [](std::string s){return s == "46";});}
        );
    for (auto v: ip_any_byte)
    {
        std::cout << output_ip(v) << std::endl;
    }

    // std::copy(ip_any_byte.cbegin(), ip_any_byte.cend(), std::ostream_iterator<std::string>(std::cout, "\n"));

    return 0;
}