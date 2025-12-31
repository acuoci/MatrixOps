cmake_minimum_required(VERSION 3.15)

# Fetch Catch2
include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.1
)

FetchContent_MakeAvailable(Catch2)

# Add test executable
add_executable(matrixops_tests
    test_matrix.cpp
    test_main.cpp
)

target_link_libraries(matrixops_tests
    PRIVATE
        MatrixOps::matrixops
        Catch2::Catch2
)

# Add tests to CTest
include(CTest)
include(Catch)
catch_discover_tests(matrixops_tests)
