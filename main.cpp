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
    
    auto ip_pool = OTUS::scan_ip4(std::cin);

    auto original_data_end = ip_pool.end();

    sort(ip_pool.begin(), original_data_end, std::greater<OTUS::IP4>());
    OTUS::output_ips(std::cout, ip_pool);

    std::vector<OTUS::IP4> ip_first_byte;
    std::copy_if(ip_pool.begin(), original_data_end, std::back_inserter(ip_pool),
        [](const OTUS::IP4& item){return std::get<0>(item) == 1;});

    std::vector<OTUS::IP4> ip_two_bytes;
    std::copy_if(ip_pool.begin(), original_data_end, std::back_inserter(ip_pool),
         [](const OTUS::IP4& item){return std::get<0>(item) == 46 && std::get<0>(item) == 70;});


    std::vector<OTUS::IP4> ip_any_byte;
    std::copy_if(ip_pool.begin(), original_data_end, std::back_inserter(ip_pool),
        [](const OTUS::IP4& i){
            return std::get<0>(i) == 46 || std::get<1>(i) == 46 || std::get<2>(i) == 46 || std::get<3>(i) == 46;}
        );

    OTUS::output_ips(std::cout, ip_pool);

    return 0;
}