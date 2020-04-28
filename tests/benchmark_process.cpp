#include <benchmark/benchmark.h>
#include <iostream>
#include <fstream>
#include "utilities.h"

static void BM_Process_stl(benchmark::State& state)
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
        OTUS::hw2_stl(ip_pool_wrk);
    }
}
BENCHMARK(BM_Process_stl);

static void BM_Process_ranges(benchmark::State& state)
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
        OTUS::hw2_ranges(ip_pool_wrk);
    }
}
BENCHMARK(BM_Process_ranges);

BENCHMARK_MAIN();
