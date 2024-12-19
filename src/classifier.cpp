#include <cmath>
#include <limits>

#include "classifier.hpp"


auto classify(const Matrix& image, const std::vector<Matrix>& class_centers) -> std::size_t {
    auto [U, S, V] = image.svdDecomposition();
    Matrix F_new = U * S;

    double min_distance = std::numeric_limits<double>::max();
    std::size_t best_class = 0;

    for (size_t i = 0; i != class_centers.size(); ++i) {
        double distance = (F_new - class_centers[i]).frobeniusNorm();
        if (distance < min_distance) {
            min_distance = distance;
            best_class = i;
        }
    }

    return best_class;
}

auto computeClassCenters(const std::vector<Matrix>& training_data, const std::vector<std::size_t>& labels) -> std::unordered_map<std::size_t, Matrix> {
    // const std::size_t k = 12;

    std::unordered_map<std::size_t, std::vector<Matrix>> class_features;
    for (std::size_t i = 0; i != training_data.size(); ++i) {
        auto [U, S, V] = training_data[i].svdDecomposition();
        Matrix feature_vector = U * S;
        class_features[labels[i]].push_back(feature_vector);
    }

    std::unordered_map<std::size_t, Matrix> class_centers;
    for (const auto& [label, features] : class_features) {
        Matrix mean_vector(features[0].getRows(), features[0].getCols(), 0.0);

        for (const auto& feature : features) {
            mean_vector = mean_vector + feature;
        }

        class_centers[label] = mean_vector / features.size();
    }

    return class_centers;
}
