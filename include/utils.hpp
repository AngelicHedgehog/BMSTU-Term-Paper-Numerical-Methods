#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <cstdint>


auto readInt(std::ifstream& stream) -> int32_t;

auto loadMNISTImages(const std::string& filename) -> std::vector<std::vector<uint8_t>>;

auto loadMNISTLabels(const std::string& filename) -> std::vector<uint8_t>;
