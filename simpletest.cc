// RUN: g++ mybenchmark.cc -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o mybenchmark

#include<benchmark/benchmark.h>
#include <stdio.h>
#include <string.h>

static void BM_StringCreation(benchmark::State& state) {
    for (auto _ : state) {
        std::string empty_string;
    }
}
// Register the function as benchmark
BENCHMARK(BM_StringCreation);

// Define another benchmark
static void BM_StringCopy(benchmark::State& state) {
    std::string x = "hello";
    for (auto _ : state) {
        std::string copy(x);
    }
}

BENCHMARK(BM_StringCopy);

static void BM_memcpy(benchmark::State& state) {
    char* src = new char[state.range(0)];
    char* dst = new char[state.range(0)];
    memset(src, 'x', state.range(0));
    for (auto _ : state) {
        memcpy(dst, src, state.range(0));
    }
    state.SetBytesProcessed(int64_t(int64_t(state.iterations()) *
                          int64_t(state.range(0))));
    delete[] src;
    delete[] dst;
}
// BENCHMARK(BM_memcpy)->Arg(8)->Arg(64)->Arg(512)->Arg(1<<10)->Arg(8<<10);
// BENCHMARK(BM_memcpy)->Range(8, 8<<10);  // [8, 64, 512, 4k, 8k]
BENCHMARK(BM_memcpy)->RangeMultiplier(2)->Range(8, 8<<10); // [8, 16, 32, 64, 128, 256, 512, 1024, 2k, 4k, 8k]

static void BM_DenseRange(benchmark::State& state) {
    for (auto _ : state) {
        std::vector<int> v(state.range(0), state.range(0));
        benchmark::DoNotOptimize(v.data());
        benchmark::ClobberMemory();
    }
}
BENCHMARK(BM_DenseRange)->DenseRange(0, 1024, 128); // [ 0, 128, 256, 384, 512, 640, 768, 896, 1024 ]

/*
static void BM_SetInsert(benchmark::State& state) {
    std::set<int> data;
    for (auto _ : state) {
        state.PauseTiming();
        data = ConstructRandomSet(state.range(0));
        state.ResumeTiming();
        for (int j = 0; j < state.range(1); ++j)
            data.insert(RandomNumber());
    }
}
// BENCHMARK(BM_SetInsert)->Args({1<<10, 128})->Args({2<<10, 128})
    // ->Args({4<<10, 128})->Args({8<<10, 128})->Args({1<<10, 512})
    // ->Args({2<<10, 512})->Args({4<<10, 512})->Args({8<<10, 512})

BENCHMARK(BM_SetInsert)->Ranges({{1<<10, 8<<10}, {128, 512}});


static void CustomArguments(benchmark::internal::Benchmark* b) {
  for (int i = 0; i <= 10; ++i)
    for (int j = 32; j <= 1024*1024; j *= 8)
      b->Args({i, j});
}
BENCHMARK(BM_SetInsert)->Apply(CustomArguments);
*/

static void BM_StringCompare(benchmark::State& state) {
    std::string s1(state.range(0), '-');
    std::string s2(state.range(0), '-');
    for(auto _ : state) {
        benchmark::DoNotOptimize(s1.compare(s2));
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_StringCompare)
    ->RangeMultiplier(2)->Range(1<<10, 1<<18)->Complexity(benchmark::oN);

// BENCHMARK(BM_StringCompare)
    // ->RangeMultiplier(2)->Range(1<<10, 1<<18)->Complexity();

// BENCHMARK(BM_StringCompare)->RangeMultiplier(2)
    // ->Range(1<<10, 1<<18)->Complexity([](int64_t n)->double{return n; });
BENCHMARK_MAIN();
