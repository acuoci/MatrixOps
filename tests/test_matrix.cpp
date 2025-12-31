#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "matrixops/matrix.h"

using namespace matrixops;
using Catch::Approx;

TEST_CASE("Matrix construction", "[matrix][construction]") {
    SECTION("Valid dimensions") {
        Matrix m(3, 4);
        REQUIRE(m.rows() == 3);
        REQUIRE(m.cols() == 4);
    }

    SECTION("Initialization with value") {
        Matrix m(2, 3, 5.0);
        for (size_t i = 0; i < 2; ++i) {
            for (size_t j = 0; j < 3; ++j) {
                REQUIRE(m(i, j) == 5.0);
            }
        }
    }

    SECTION("Invalid dimensions throw exception") {
        REQUIRE_THROWS_AS(Matrix(0, 5), std::invalid_argument);
        REQUIRE_THROWS_AS(Matrix(5, 0), std::invalid_argument);
    }
}

TEST_CASE("Matrix element access", "[matrix][access]") {
    Matrix m(3, 3, 0.0);
    
    SECTION("Read and write") {
        m(1, 2) = 7.5;
        REQUIRE(m(1, 2) == 7.5);
    }

    SECTION("Out of bounds access throws") {
        REQUIRE_THROWS_AS(m(3, 0), std::out_of_range);
        REQUIRE_THROWS_AS(m(0, 3), std::out_of_range);
    }
}

TEST_CASE("Matrix addition", "[matrix][addition]") {
    Matrix a(2, 2, 1.0);
    Matrix b(2, 2, 2.0);

    SECTION("Valid addition") {
        Matrix c = a + b;
        REQUIRE(c(0, 0) == 3.0);
        REQUIRE(c(1, 1) == 3.0);
    }

    SECTION("Dimension mismatch throws") {
        Matrix d(2, 3, 1.0);
        REQUIRE_THROWS_AS(a + d, std::invalid_argument);
    }
}

TEST_CASE("Matrix multiplication", "[matrix][multiplication]") {
    SECTION("Valid matrix multiplication") {
        Matrix a(2, 3);
        a(0, 0) = 1; a(0, 1) = 2; a(0, 2) = 3;
        a(1, 0) = 4; a(1, 1) = 5; a(1, 2) = 6;

        Matrix b(3, 2);
        b(0, 0) = 7;  b(0, 1) = 8;
        b(1, 0) = 9;  b(1, 1) = 10;
        b(2, 0) = 11; b(2, 1) = 12;

        Matrix c = a * b;
        
        REQUIRE(c.rows() == 2);
        REQUIRE(c.cols() == 2);
        REQUIRE(c(0, 0) == 58);  // 1*7 + 2*9 + 3*11
        REQUIRE(c(0, 1) == 64);  // 1*8 + 2*10 + 3*12
        REQUIRE(c(1, 0) == 139); // 4*7 + 5*9 + 6*11
        REQUIRE(c(1, 1) == 154); // 4*8 + 5*10 + 6*12
    }

    SECTION("Dimension mismatch throws") {
        Matrix a(2, 3);
        Matrix b(2, 2);
        REQUIRE_THROWS_AS(a * b, std::invalid_argument);
    }
}

TEST_CASE("Scalar multiplication", "[matrix][scalar]") {
    Matrix m(2, 2, 3.0);
    Matrix result = m * 2.0;

    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            REQUIRE(result(i, j) == 6.0);
        }
    }
}

TEST_CASE("Matrix transpose", "[matrix][transpose]") {
    Matrix m(2, 3);
    m(0, 0) = 1; m(0, 1) = 2; m(0, 2) = 3;
    m(1, 0) = 4; m(1, 1) = 5; m(1, 2) = 6;

    Matrix t = m.transpose();

    REQUIRE(t.rows() == 3);
    REQUIRE(t.cols() == 2);
    REQUIRE(t(0, 0) == 1);
    REQUIRE(t(1, 0) == 2);
    REQUIRE(t(2, 0) == 3);
    REQUIRE(t(0, 1) == 4);
    REQUIRE(t(1, 1) == 5);
    REQUIRE(t(2, 1) == 6);
}

TEST_CASE("Matrix norm", "[matrix][norm]") {
    Matrix m(2, 2);
    m(0, 0) = 3; m(0, 1) = 4;
    m(1, 0) = 0; m(1, 1) = 0;

    REQUIRE(m.norm() == Approx(5.0)); // sqrt(9 + 16) = 5
}

TEST_CASE("Identity matrix", "[matrix][identity]") {
    Matrix I = identity(3);

    REQUIRE(I.rows() == 3);
    REQUIRE(I.cols() == 3);
    REQUIRE(I.is_square());

    for (size_t i = 0; i < 3; ++i) {
        for (size_t j = 0; j < 3; ++j) {
            if (i == j) {
                REQUIRE(I(i, j) == 1.0);
            } else {
                REQUIRE(I(i, j) == 0.0);
            }
        }
    }
}

TEST_CASE("Matrix is_square", "[matrix][property]") {
    Matrix square(3, 3);
    Matrix rect(3, 4);

    REQUIRE(square.is_square());
    REQUIRE_FALSE(rect.is_square());
}
