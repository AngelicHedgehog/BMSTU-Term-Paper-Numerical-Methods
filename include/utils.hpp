#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <cstdint>

#include "Matrix.hpp"


auto readInt(std::ifstream& stream) -> int32_t;

auto loadMNISTImages(const std::string& filename) -> std::vector<Matrix>;

auto loadMNISTLabels(const std::string& filename) -> std::vector<std::size_t>;

auto filterData(std::vector<Matrix>& images, std::vector<std::size_t>& labels) -> void;

auto findTopKIndices(const std::vector<double>& data, std::size_t k) -> std::vector<std::size_t>;
