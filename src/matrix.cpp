#include <stdexcept>
#include <cmath>

#include "matrix.hpp"


Matrix::Matrix(std::size_t rows, std::size_t cols, double init_value)
    : rows(rows), cols(cols), data(rows, std::vector<double>(cols, init_value)) {}

Matrix::Matrix(const std::vector<std::vector<double>>& input_data)
    : rows(input_data.size()), cols(input_data.empty() ? 0 : input_data[0].size()), data(input_data) {}

auto Matrix::getRows() const -> std::size_t {
    return rows;
}

auto Matrix::getCols() const -> std::size_t {
    return cols;
}

auto Matrix::at(size_t row, size_t col) -> double& {
    if (row >= rows || col >= cols) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    return data[row][col];
}

auto Matrix::at(size_t row, size_t col) const -> const double& {
    if (row >= rows || col >= cols) {
        throw std::out_of_range("Индекс вне диапазона");
    }
    return data[row][col];
}

auto Matrix::frobeniusNorm() const -> double {
    double sum = 0.0;
    for (const auto& row : data) {
        for (const auto& val : row) {
            sum += val * val;
        }
    }
    return std::sqrt(sum);
}

auto Matrix::determinant() const -> double {
    if (rows != cols) {
        throw std::invalid_argument("Определитель можно вычислить только для квадратных матриц");
    }

    if (rows == 1) {
        return data[0][0];
    }

    if (rows == 2) {
        return data[0][0] * data[1][1] - data[0][1] * data[1][0];
    }

    double det = 0.0;
    for (size_t col = 0; col != cols; ++col) {
        Matrix minor(rows - 1, cols - 1);

        for (std::size_t i = 1; i != rows; ++i) {
            std::size_t minor_col = 0;
            for (std::size_t j = 0; j != cols; ++j) {
                if (j == col) continue;
                minor.at(i - 1, minor_col++) = data[i][j];
            }
        }

        det += (col % 2 == 0 ? 1 : -1) * data[0][col] * minor.determinant();
    }

    return det;
}

auto Matrix::trace() const -> double {
    double diagonalElemsSum = 0;

    for (std::size_t i = 0; i != rows; ++i) {
        diagonalElemsSum += data[i][i];
    }
    
    return diagonalElemsSum;
}

auto Matrix::transpose() const -> Matrix {
    Matrix transposed(cols, rows);
    for (std::size_t i = 0; i != rows; ++i) {
        for (std::size_t j = 0; j != cols; ++j) {
            transposed.at(j, i) = data[i][j];
        }
    }
    return transposed;
}

auto Matrix::operator+(const Matrix& other) const -> Matrix {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Размеры матриц не совместимы для сложения");
    }
    Matrix result(rows, other.cols);
    for (std::size_t i = 0; i != rows; ++i) {
        for (std::size_t j = 0; j != cols; ++j) {
            result.at(i, j) = data[i][j] + other.at(i, j);
        }
    }
    return result;
}

auto Matrix::operator-(const Matrix& other) const -> Matrix {
    if (rows != other.rows || cols != other.cols) {
        throw std::invalid_argument("Размеры матриц не совместимы для разности");
    }
    Matrix result(rows, other.cols);
    for (std::size_t i = 0; i != rows; ++i) {
        for (std::size_t j = 0; j != cols; ++j) {
            result.at(i, j) = data[i][j] - other.at(i, j);
        }
    }
    return result;
}

auto Matrix::operator*(const Matrix& other) const -> Matrix {
    if (cols != other.rows) {
        throw std::invalid_argument("Размеры матриц не совместимы для умножения");
    }
    Matrix result(rows, other.cols);
    for (std::size_t i = 0; i != rows; ++i) {
        for (std::size_t j = 0; j != other.cols; ++j) {
            for (std::size_t k = 0; k != cols; ++k) {
                result.at(i, j) += data[i][k] * other.at(k, j);
            }
        }
    }
    return result;
}

auto Matrix::operator/(double k) const -> Matrix {
    Matrix result = *this;

    for (auto& row : result.data) {
        for (auto& element : row) {
            element /= k;
        }
    }

    return result;
}

auto Matrix::qrDecomposition() const -> std::pair<Matrix, Matrix> {
    if (rows != cols) {
        throw std::invalid_argument("QR-разложение возможно только для квадратных матриц");
    }

    Matrix Q = *this;
    Matrix R(rows, cols);

    for (std::size_t k = 0; k != cols; ++k) {
        double norm = 0.0;
        for (std::size_t i = 0; i != rows; ++i) {
            norm += Q.at(i, k) * Q.at(i, k);
        }
        norm = std::sqrt(norm);
        R.at(k, k) = norm;

        for (std::size_t i = 0; i != rows; ++i) {
            Q.at(i, k) /= norm;
        }

        for (size_t j = k + 1; j != cols; ++j) {
            double dot = 0.0;
            for (size_t i = 0; i != rows; ++i) {
                dot += Q.at(i, k) * Q.at(i, j);
            }
            R.at(k, j) = dot;

            for (size_t i = 0; i != rows; ++i) {
                Q.at(i, j) -= dot * Q.at(i, k);
            }
        }
    }

    return {Q, R};
}

auto Matrix::eigenvaluesAndVectors(std::size_t max_iterations, double tolerance) const -> std::pair<std::vector<double>, Matrix> {
    if (rows != cols) {
        throw std::invalid_argument("Собственные значения можно вычислить только для квадратных матриц");
    }

    Matrix A = *this;
    Matrix Q_total(rows, rows, 0.0);
    for (std::size_t i = 0; i != rows; ++i) {
        Q_total.at(i, i) = 1.0;
    }

    for (size_t iter = 0; iter < max_iterations; ++iter) {
        auto [Q, R] = A.qrDecomposition();
        A = R * Q;
        Q_total = Q_total * Q;

        bool converged = true;
        for (size_t i = 0; i < rows; ++i) {
            if (std::abs(A.at(i, i) - Q_total.at(i, i)) > tolerance) {
                converged = false;
                break;
            }
        }
        if (converged) {
            break;
        }
    }

    std::vector<double> eigenvalues;
    for (std::size_t i = 0; i != rows; ++i) {
        eigenvalues.push_back(A.at(i, i));
    }

    return {eigenvalues, Q_total};
}

auto Matrix::svdDecomposition(std::size_t max_iterations, double tolerance) const -> std::tuple<Matrix, Matrix, Matrix> {
    Matrix AAT = (*this) * this->transpose(); // A * A^T
    Matrix ATA = this->transpose() * (*this); // A^T * A

    auto [left_eigenvalues, U] = AAT.eigenvaluesAndVectors(max_iterations, tolerance);
    auto [right_eigenvalues, V] = ATA.eigenvaluesAndVectors(max_iterations, tolerance);

    Matrix Sigma(rows, cols, 0.0);

    for (size_t i = 0; i < std::min(rows, cols); ++i) {
        Sigma.at(i, i) = std::sqrt(left_eigenvalues[i]);
    }

    return {U, Sigma, V};
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (const auto& row : matrix.data) {
        for (const auto& val : row) {
            os << val << "\t";
        }
        os << "\n";
    }
    return os;
}
