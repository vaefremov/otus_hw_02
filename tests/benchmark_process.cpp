#include <benchmark/benchmark.h>
#include <iostream>
#include <fstream>
#include "utilities.h"

class IPListFixture : public benchmark::Fixture {
public:
  void SetUp(const ::benchmark::State& state) {
    std::ifstream in;
    in.open("./tests/ip.tsv");
    if(!in.good())
    {
        in.close();
        in.open("../tests/ip.tsv");
    }
    ip_pool = OTUS::scan_ip4(in);
    in.close();
  }

  OTUS::VIP<OTUS::IP4> ip_pool;
};

BENCHMARK_DEFINE_F(IPListFixture, Stl)(benchmark::State& state)
{
    for (auto _ : state)
    {
        auto ip_pool_wrk = ip_pool;
        OTUS::hw2_stl(ip_pool_wrk);
    }
}
BENCHMARK_REGISTER_F(IPListFixture, Stl)->Unit(benchmark::kMicrosecond);

BENCHMARK_DEFINE_F(IPListFixture, Ranges)(benchmark::State& state)
{
    for (auto _ : state)
    {
        auto ip_pool_wrk = ip_pool;
        OTUS::hw2_ranges(ip_pool_wrk);
    }    
}
BENCHMARK_REGISTER_F(IPListFixture, Ranges)->Unit(benchmark::kMicrosecond);

static void BM_copy(benchmark::State& state)
{
    std::ifstream in;
    in.open("./tests/ip.tsv");
    if(!in.good())
    {
        in.close();
        in.open("../tests/ip.tsv");
    }
    auto ip_pool = OTUS::scan_ip4(in);

    for(auto _: state)
    {
        auto ip_pool_wrk = ip_pool;
    }
}
BENCHMARK(BM_copy);



BENCHMARK_MAIN();
