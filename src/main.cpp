#include <algorithm>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>

#include <iterator>
#include <vector>

#include "utilities.h"

bool is_option_set(int argc, const char** argv, const std::string& opt)
{
    auto end = argv+argc;
    return std::find(std::next(argv), end, opt) != end;
}

static void usage()
{
    std::cout << "Version: " << OTUS::version_str() << std::endl;
    std::cout << "Usage: "
              << "ip_filter < input_file.txt" << std::endl;
    std::exit(1);
}

int main(int argc, const char** argv)
{
    if (is_option_set(argc, argv, "-h")) {
        usage();
    }

    auto ip_pool = OTUS::scan_ip4(std::cin);
    
    ip_pool = OTUS::hw2_stl(ip_pool);
    
    OTUS::output_ips(std::cout, ip_pool);

    return 0;
}