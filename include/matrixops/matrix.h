#pragma once

#include <vector>
#include <stdexcept>
#include <cmath>

namespace matrixops {

/**
 * @brief A simple matrix class for demonstrating CI/CD workflows
 * 
 * This class provides basic matrix operations for educational purposes.
 */
class Matrix {
public:
    /**
     * @brief Construct a matrix with given dimensions
     * @param rows Number of rows
     * @param cols Number of columns
     * @param init_value Initial value for all elements (default: 0.0)
     */
    Matrix(size_t rows, size_t cols, double init_value = 0.0);

    /**
     * @brief Get number of rows
     */
    size_t rows() const { return rows_; }

    /**
     * @brief Get number of columns
     */
    size_t cols() const { return cols_; }

    /**
     * @brief Access element at (i, j)
     */
    double& operator()(size_t i, size_t j);

    /**
     * @brief Access element at (i, j) (const version)
     */
    double operator()(size_t i, size_t j) const;

    /**
     * @brief Matrix addition
     */
    Matrix operator+(const Matrix& other) const;

    /**
     * @brief Matrix multiplication
     */
    Matrix operator*(const Matrix& other) const;

    /**
     * @brief Scalar multiplication
     */
    Matrix operator*(double scalar) const;

    /**
     * @brief Transpose matrix
     */
    Matrix transpose() const;

    /**
     * @brief Calculate Frobenius norm
     */
    double norm() const;

    /**
     * @brief Check if matrix is square
     */
    bool is_square() const { return rows_ == cols_; }

private:
    size_t rows_;
    size_t cols_;
    std::vector<double> data_;

    size_t index(size_t i, size_t j) const {
        return i * cols_ + j;
    }
};

/**
 * @brief Create an identity matrix
 * @param n Dimension of the square identity matrix
 */
Matrix identity(size_t n);

} // namespace matrixops
