#pragma once

#include <vector>
#include <unordered_map>

#include "Matrix.hpp"


auto classify(const Matrix& image, const std::unordered_map<std::size_t, Matrix>& class_centers) -> std::size_t;

auto computeClassCenters(const std::vector<Matrix>& training_data, const std::vector<std::size_t>& labels, std::size_t k = 12)
    -> std::unordered_map<std::size_t, Matrix>;