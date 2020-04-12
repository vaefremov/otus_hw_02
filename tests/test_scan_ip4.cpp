#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <regex>
#include "utilities.h"
#include "utilities_impl.h"

TEST(Miscellanious, version_string)
{
    auto version = OTUS::version_str();
    const std::regex version_regex("^\\d+\\.\\d+\\.\\d+$");
    EXPECT_TRUE(std::regex_match(version, version_regex));
}

TEST(ScanIPTests, regular_case)
{
     std::istringstream str("113.162.145.156	111	0\n157.39.22.224	5	6\n");
     std::vector<OTUS::IP4> ips = OTUS::scan_ip4(str);
     OTUS::IP4 t0_exp(113, 162, 145, 156);
     OTUS::IP4 t1_exp(157, 39, 22, 224);
     EXPECT_EQ(2, ips.size());
     EXPECT_EQ(t0_exp, ips.at(0));
     EXPECT_EQ(t1_exp, ips.at(1));
}

TEST(ScanIPTests, bad_string)
{
     std::istringstream str("113.162.145.qq	111	0\n157.39.22.224	5	6\n");
     std::vector<OTUS::IP4> ips;
     ASSERT_NO_THROW(ips = OTUS::scan_ip4(str));
     EXPECT_EQ(1, ips.size());
     OTUS::IP4 t1_exp(157, 39, 22, 224);
     EXPECT_EQ(t1_exp, ips.at(0));
}

TEST(ScanIPTests, ip_elt_outofrange)
{
     std::istringstream str("113.1620.145.156	111	0\n157.39.22.224	5	6\n");
     std::vector<OTUS::IP4> ips;
     ASSERT_NO_THROW(ips = OTUS::scan_ip4(str));
     EXPECT_EQ(1, ips.size());
     OTUS::IP4 t1_exp(157, 39, 22, 224);
     EXPECT_EQ(t1_exp, ips.at(0));
}

TEST(ScanIPTests, empty_strings)
{
     std::istringstream str("113.162.145.156	111	0\n\n	\n157.39.22.224	5	6\n\n\n");
     std::vector<OTUS::IP4> ips = OTUS::scan_ip4(str);
     OTUS::IP4 t0_exp(113, 162, 145, 156);
     OTUS::IP4 t1_exp(157, 39, 22, 224);
     EXPECT_EQ(2, ips.size());
     EXPECT_EQ(t0_exp, ips.at(0));
     EXPECT_EQ(t1_exp, ips.at(1));
}


TEST(OutputIPs, regular_case)
{
     OTUS::IP4 t0(113, 162, 145, 156);
     OTUS::IP4 t1(157, 39, 22, 224);
    std::vector<OTUS::IP4> ips{t0, t1};
    std::stringstream out;
    OTUS::output_ips(out, ips);
    ASSERT_STREQ("113.162.145.156\n157.39.22.224\n", out.str().c_str());
}

TEST(Conversions, ip_to_string)
{
    OTUS::IP4 t0(113, 162, 145, 156);
    ASSERT_STREQ("113.162.145.156", OTUS::ip_to_string(t0).c_str());
}

TEST(Conversions, str_to_ip)
{
    OTUS::IP4 t0_exp(113, 162, 145, 156);
    std::string t0_str("113.162.145.156");
    OTUS::IP4 t0 = OTUS::string_to_ip(t0_str);
    ASSERT_EQ(t0_exp, t0);
}

TEST(Conversions, str_to_ip_bad_input)
{
    std::string t0_str("113.162.145");
    ASSERT_THROW(OTUS::string_to_ip(t0_str), std::invalid_argument);
    std::string t1_str("");
    ASSERT_THROW(OTUS::string_to_ip(t1_str), std::invalid_argument);
    std::string t2_str("weqwer");
    ASSERT_THROW(OTUS::string_to_ip(t2_str), std::invalid_argument);
}

