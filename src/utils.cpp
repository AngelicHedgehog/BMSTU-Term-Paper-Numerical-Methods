#include <numeric>
#include <algorithm>

#include "utils.hpp"
#include "matrix.hpp"


auto readInt(std::ifstream& stream) -> std::int32_t {
    std::uint8_t bytes[4];
    stream.read(reinterpret_cast<char*>(bytes), 4);
    return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
}

auto loadMNISTImages(const std::string& filename) -> std::vector<Matrix> {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }

    std::int32_t magic = readInt(file);
    if (magic != 2051) {
        throw std::runtime_error("Неверное магическое число для изображений");
    }

    std::int32_t numImages = readInt(file);
    std::int32_t rows = readInt(file);
    std::int32_t cols = readInt(file);

    std::vector<Matrix> images(numImages, Matrix(rows, cols));
    for (std::size_t i = 0; i != numImages; ++i) {
        std::vector<unsigned char> buffer(rows * cols);
        file.read(reinterpret_cast<char*>(buffer.data()), rows * cols);
        
        for (std::size_t j = 0; j != buffer.size(); ++j) {
            images[i].at(j % rows, j / rows) = static_cast<double>(buffer[j]) / 255.0;
        }
    }

    return images;
}

auto loadMNISTLabels(const std::string& filename) -> std::vector<std::size_t> {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }

    std::int32_t magic = readInt(file);
    if (magic != 2049) {
        throw std::runtime_error("Неверное магическое число для меток");
    }

    std::int32_t numLabels = readInt(file);
    std::vector<std::uint8_t> labels(numLabels);
    file.read(reinterpret_cast<char*>(labels.data()), numLabels);

    std::vector<std::size_t> formatedLabels(numLabels);
    for (std::size_t i = 0; i != numLabels; ++i) {
        formatedLabels[i] = labels[i];
    }

    return formatedLabels;
}

auto findTopKIndices(const std::vector<double>& data, std::size_t k) -> std::vector<std::size_t> {
    std::vector<std::size_t> indices(data.size());
    std::iota(indices.begin(), indices.end(), 0);

    std::partial_sort(indices.begin(), indices.begin() + k, indices.end(),
        [&data](std::size_t i1, std::size_t i2) {
            return data[i1] > data[i2];
        });

    return std::vector<std::size_t>(indices.begin(), indices.begin() + k);
}
