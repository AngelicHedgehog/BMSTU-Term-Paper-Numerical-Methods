#pragma once

#include <vecotr>

#include "Matrix.hpp"

auto classify(const Matrix& image, const std::vector<Matrix>& class_centers) -> std::size_t;