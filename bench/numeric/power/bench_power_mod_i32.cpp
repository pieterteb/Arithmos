#include <benchmark/benchmark.h>
#include <random>
#include <vector>

extern "C" {
#include "arithmos/core/limits.h"
#include "arithmos/core/types.h"
#include "arithmos/numeric/power.h"
}



static std::vector<arith_i32> bases;
static std::vector<arith_u32> exponents;
static std::vector<arith_u32> modulos;

static void generate_inputs(size_t N) {
    std::mt19937 rng(69420);
    std::uniform_int_distribution<arith_i32> base_dist(ARITH_I32_MIN, ARITH_I32_MAX);
    std::uniform_int_distribution<arith_u32> exponent_dist(0, ARITH_U32_MAX);
    std::uniform_int_distribution<arith_u32> modulo_dist(1, (arith_u32)ARITH_I32_MAX + 1);

    bases.resize(N);
    exponents.resize(N);
    modulos.resize(N);

    for (size_t i = 0; i < N; ++i) {
        bases[i]     = base_dist(rng);
        exponents[i] = exponent_dist(rng);
        modulos[i]   = modulo_dist(rng);
    }
}

static void bench(benchmark::State& state) {
    size_t N = 10000;

    generate_inputs(N);

    size_t i = 0;
    for (auto _ : state) {
        benchmark::DoNotOptimize(arith_power_mod_i32(bases[i], exponents[i], modulos[i]));

        i = (i + 1) % N;
    }
}


BENCHMARK(bench);

BENCHMARK_MAIN();
