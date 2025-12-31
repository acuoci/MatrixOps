cmake_minimum_required(VERSION 3.15)

# Project definition
project(MatrixOps
    VERSION 1.0.0
    DESCRIPTION "A tutorial project for professional C++ GitHub workflows"
    LANGUAGES CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Options
option(MATRIXOPS_BUILD_TESTS "Build tests" ON)
option(MATRIXOPS_BUILD_BENCHMARKS "Build benchmarks" ON)
option(MATRIXOPS_BUILD_DOCS "Build documentation" OFF)
option(MATRIXOPS_ENABLE_COVERAGE "Enable code coverage" OFF)
option(MATRIXOPS_ENABLE_SANITIZERS "Enable sanitizers" OFF)

# Code coverage setup (must be before add_library)
if(MATRIXOPS_ENABLE_COVERAGE)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        add_compile_options(--coverage)
        add_link_options(--coverage)
    endif()
endif()

# Create library
add_library(matrixops
    src/matrix.cpp
)

# Add alias for consistency
add_library(MatrixOps::matrixops ALIAS matrixops)

# Include directories
target_include_directories(matrixops
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# Compiler warnings
if(MSVC)
    target_compile_options(matrixops PRIVATE /W4 /WX)
else()
    target_compile_options(matrixops PRIVATE
        -Wall -Wextra -Wpedantic -Werror
    )
endif()

# Sanitizers
if(MATRIXOPS_ENABLE_SANITIZERS)
    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
        target_compile_options(matrixops PRIVATE
            -fsanitize=address,undefined
            -fno-omit-frame-pointer
        )
        target_link_options(matrixops PRIVATE
            -fsanitize=address,undefined
        )
    endif()
endif()


# Testing
if(MATRIXOPS_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# Benchmarks
if(MATRIXOPS_BUILD_BENCHMARKS)
    add_subdirectory(benchmarks)
endif()

# Documentation
if(MATRIXOPS_BUILD_DOCS)
    find_package(Doxygen)
    if(DOXYGEN_FOUND)
        add_subdirectory(docs)
    else()
        message(WARNING "Doxygen not found, documentation will not be built")
    endif()
endif()

# Installation
include(GNUInstallDirs)

install(TARGETS matrixops
    EXPORT MatrixOpsTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT MatrixOpsTargets
    FILE MatrixOpsTargets.cmake
    NAMESPACE MatrixOps::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MatrixOps
)

# Create package config file
include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/MatrixOpsConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/MatrixOpsConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MatrixOps
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/MatrixOpsConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/MatrixOpsConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/MatrixOpsConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MatrixOps
)