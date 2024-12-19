#pragma once

#include <vector>
#include <unordered_map>

#include "Matrix.hpp"


auto classify(const Matrix& image, const std::vector<Matrix>& class_centers) -> std::size_t;

auto computeClassCenters(const std::vector<Matrix>& training_data, const std::vector<std::size_t>& labels) -> std::unordered_map<std::size_t, Matrix>;