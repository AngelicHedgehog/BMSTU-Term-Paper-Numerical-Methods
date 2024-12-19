#pragma once

#include <vector>
#include <iostream>


class Matrix {
private:
    std::vector<std::vector<double>> data_;
    std::size_t rows_;
    std::size_t cols_;

public:
    Matrix(std::size_t rows, std::size_t cols, double init_value = 0.0);
    Matrix(const std::vector<std::vector<double>>& input_data);

    auto getRows() const -> std::size_t;
    auto getCols() const -> std::size_t;
    
    auto at(size_t row, size_t col) -> double&;
    auto at(size_t row, size_t col) const -> const double&;
    
    auto transpose() const -> Matrix;
    auto operator*(const Matrix& other) const -> Matrix;

    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
};
