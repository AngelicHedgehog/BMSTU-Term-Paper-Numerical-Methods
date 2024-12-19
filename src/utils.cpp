#include "utils.hpp"


auto readInt(std::ifstream& stream) -> int32_t {
    uint8_t bytes[4];
    stream.read(reinterpret_cast<char*>(bytes), 4);
    return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
}

auto loadMNISTImages(const std::string& filename) -> std::vector<std::vector<uint8_t>> {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }

    int32_t magic = readInt(file);
    if (magic != 2051) {
        throw std::runtime_error("Неверное магическое число для изображений");
    }

    int32_t num_images = readInt(file);
    int32_t rows = readInt(file);
    int32_t cols = readInt(file);

    std::vector<std::vector<uint8_t>> images(num_images, std::vector<uint8_t>(rows * cols));
    for (std::size_t i = 0; i != num_images; ++i) {
        file.read(reinterpret_cast<char*>(images[i].data()), rows * cols);
    }

    return images;
}

auto loadMNISTLabels(const std::string& filename) -> std::vector<uint8_t> {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }

    int32_t magic = readInt(file);
    if (magic != 2049) {
        throw std::runtime_error("Неверное магическое число для меток");
    }

    int32_t num_labels = readInt(file);
    std::vector<uint8_t> labels(num_labels);
    file.read(reinterpret_cast<char*>(labels.data()), num_labels);

    return labels;
}
