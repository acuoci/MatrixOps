#include <benchmark/benchmark.h>
#include "matrixops/matrix.h"

using namespace matrixops;

// Benchmark matrix multiplication for different sizes
static void BM_MatrixMultiplication(benchmark::State& state) {
    const size_t n = state.range(0);
    Matrix a(n, n, 1.0);
    Matrix b(n, n, 2.0);

    for (auto _ : state) {
        Matrix c = a * b;
        benchmark::DoNotOptimize(c);
    }

    state.SetComplexityN(n);
}

BENCHMARK(BM_MatrixMultiplication)
    ->RangeMultiplier(2)
    ->Range(8, 128)
    ->Complexity();

// Benchmark matrix transpose
static void BM_MatrixTranspose(benchmark::State& state) {
    const size_t n = state.range(0);
    Matrix m(n, n, 1.5);

    for (auto _ : state) {
        Matrix t = m.transpose();
        benchmark::DoNotOptimize(t);
    }

    state.SetComplexityN(n);
}

BENCHMARK(BM_MatrixTranspose)
    ->RangeMultiplier(2)
    ->Range(8, 512)
    ->Complexity();

// Benchmark matrix addition
static void BM_MatrixAddition(benchmark::State& state) {
    const size_t n = state.range(0);
    Matrix a(n, n, 1.0);
    Matrix b(n, n, 2.0);

    for (auto _ : state) {
        Matrix c = a + b;
        benchmark::DoNotOptimize(c);
    }

    state.SetComplexityN(n);
}

BENCHMARK(BM_MatrixAddition)
    ->RangeMultiplier(2)
    ->Range(8, 1024)
    ->Complexity();

// Benchmark norm calculation
static void BM_MatrixNorm(benchmark::State& state) {
    const size_t n = state.range(0);
    Matrix m(n, n, 3.14);

    for (auto _ : state) {
        double norm = m.norm();
        benchmark::DoNotOptimize(norm);
    }

    state.SetComplexityN(n);
}

BENCHMARK(BM_MatrixNorm)
    ->RangeMultiplier(2)
    ->Range(8, 1024)
    ->Complexity();

BENCHMARK_MAIN();
