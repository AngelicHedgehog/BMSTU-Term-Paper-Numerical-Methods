#pragma once

#include <vector>
#include <utility>
#include <iostream>


class Matrix {
private:
    std::vector<std::vector<double>> data;
    std::size_t rows;
    std::size_t cols;

public:
    Matrix(std::size_t rows, std::size_t cols, double init_value = 0.0);
    Matrix(const std::vector<std::vector<double>>& input_data);

    auto getRows() const -> std::size_t;
    auto getCols() const -> std::size_t;
    
    auto at(size_t row, size_t col) -> double&;
    auto at(size_t row, size_t col) const -> const double&;
    
    auto frobeniusNorm() const -> double;
    auto determinant() const -> double;
    auto trace() const -> double;

    auto transpose() const -> Matrix;
    auto operator+(const Matrix& other) const -> Matrix;
    auto operator-(const Matrix& other) const -> Matrix;
    auto operator*(const Matrix& other) const -> Matrix;

    auto qrDecomposition() const -> std::pair<Matrix, Matrix>;
    auto eigenvaluesAndVectors(std::size_t max_iterations = 1000, double tolerance = 1e-9) const -> std::pair<std::vector<double>, Matrix>;
    auto svdDecomposition(std::size_t max_iterations = 1000, double tolerance = 1e-9) const -> std::tuple<Matrix, Matrix, Matrix>;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
};
