#include "utilities.h"
#include "utilities_impl.h"
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <Poco/MD5Engine.h>
#include <Poco/DigestStream.h>
#include <string>

TEST(ProcessingWithRanges, result)
{
    std::ifstream in;
    in.open("./tests/ip.tsv");
    if(!in.good())
    {
        in.close();
        in.open("../tests/ip.tsv");
    }

    auto ip_pool = OTUS::scan_ip4(in);
    Poco::MD5Engine md5;
    Poco::DigestOutputStream ds(md5);
    OTUS::hw2_ranges(ip_pool);
    OTUS::output_ips(ds, ip_pool);
    ds.close();
    std::string md5_out = Poco::DigestEngine::digestToHex(md5.digest());
    std::string md5_exp{"24e7a7b2270daee89c64d3ca5fb3da1a"};
    GTEST_ASSERT_EQ(md5_exp, md5_out);
}