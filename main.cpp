#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>
#include <string>

#include <iterator>
#include <vector>

#include "config.h"
#include "utilities.h"

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
    std::vector<OTUS::IP4> ip_pool;
    for (std::string line; std::getline(std::cin, line);)
    {
        std::vector<std::string> v = OTUS::split(line, '\t');
        ip_pool.push_back(OTUS::string_to_ip(v.at(0)));
    }


    sort(ip_pool.begin(), ip_pool.end(), std::greater<OTUS::IP4>());

    for (auto v: ip_pool)
    {
        std::cout << OTUS::ip_to_string(v) << std::endl;
    }

    std::vector<OTUS::IP4> ip_first_byte;
    std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(ip_first_byte),
    [](const OTUS::IP4& item){return std::get<0>(item) == 1;});
    for (auto v: ip_first_byte)
    {
        std::cout << OTUS::ip_to_string(v) << std::endl;
    }

    std::vector<OTUS::IP4> ip_two_bytes;
    std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(ip_two_bytes),
         [](const OTUS::IP4& item){return std::get<0>(item) == 46 && std::get<0>(item) == 70;});
    for (auto v: ip_first_byte)
    {
        std::cout << OTUS::ip_to_string(v) << std::endl;
    }


    std::vector<OTUS::IP4> ip_any_byte;
    std::copy_if(ip_pool.begin(), ip_pool.end(), std::back_inserter(ip_any_byte),
        [](const OTUS::IP4& i){
            return std::get<0>(i) == 46 || std::get<1>(i) == 46 || std::get<2>(i) == 46 || std::get<3>(i) == 46;}
        );
    for (auto v: ip_any_byte)
    {
        std::cout << OTUS::ip_to_string(v) << std::endl;
    }

    // std::copy(ip_any_byte.cbegin(), ip_any_byte.cend(), std::ostream_iterator<std::string>(std::cout, "\n"));

    return 0;
}