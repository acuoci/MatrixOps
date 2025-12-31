cmake_minimum_required(VERSION 3.15)

# Fetch Google Benchmark
include(FetchContent)

FetchContent_Declare(
    benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.8.3
)

set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(benchmark)

# Add benchmark executable
add_executable(matrixops_benchmarks
    bench_matrix.cpp
)

target_link_libraries(matrixops_benchmarks
    PRIVATE
        MatrixOps::matrixops
        benchmark::benchmark
)
