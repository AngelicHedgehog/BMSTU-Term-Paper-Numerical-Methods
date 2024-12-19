#include <stdexcept>

#include "matrix.hpp"


Matrix::Matrix(std::size_t rows, std::size_t cols, double init_value)
    : rows_(rows), cols_(cols), data_(rows, std::vector<double>(cols, init_value)) {}

Matrix::Matrix(const std::vector<std::vector<double>>& input_data)
    : rows_(input_data.size()), cols_(input_data.empty() ? 0 : input_data[0].size()), data_(input_data) {}

auto Matrix::getRows() const -> std::size_t {
    return rows_;
}

auto Matrix::getCols() const -> std::size_t {
    return cols_;
}

auto Matrix::at(size_t row, size_t col) -> double& {
    if (row >= rows_ || col >= cols_) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    return data_[row][col];
}

auto Matrix::at(size_t row, size_t col) const -> const double& {
    if (row >= rows_ || col >= cols_) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    return data_[row][col];
}

auto Matrix::transpose() const -> Matrix {
    Matrix transposed(cols_, rows_);
    for (std::size_t i = 0; i != rows_; ++i) {
        for (std::size_t j = 0; j != cols_; ++j) {
            transposed.at(j, i) = data_[i][j];
        }
    }
    return transposed;
}

auto Matrix::operator*(const Matrix& other) const -> Matrix {
    if (cols_ != other.rows_) {
        throw std::invalid_argument("Размеры матриц не совместимы для умножения");
    }
    Matrix result(rows_, other.cols_);
    for (std::size_t i = 0; i != rows_; ++i) {
        for (std::size_t j = 0; j != other.cols_; ++j) {
            for (std::size_t k = 0; k != cols_; ++k) {
                result.at(i, j) += data_[i][k] * other.at(k, j);
            }
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (const auto& row : matrix.data_) {
        for (const auto& val : row) {
            os << val << "\t";
        }
        os << "\n";
    }
    return os;
}
