#include <cmath>
#include <limits>

#include "classifier.hpp"
#include "utils.hpp"


auto classify(const Matrix& image, const std::unordered_map<std::size_t, Matrix>& classCenters) -> std::size_t {
    const std::size_t k = classCenters.at(0).getCols();
    auto [U, Sigma, V] = image.svdDecomposition();
    
    std::vector<double> singularValues;
    for (std::size_t j = 0; j != image.getCols(); ++j) {
        singularValues.push_back(image.at(j, j));
    }
    auto maxKSingularIndexes = findTopKIndices(singularValues, k);

    Matrix U_k(U.getRows(), k);
    Matrix Sigma_k(k, k);
    for (std::size_t j = 0; j != k; ++j) {
        for (std::size_t r = 0; r != U.getRows(); ++r) {
            U_k.at(r, j) = U.at(r, maxKSingularIndexes[j]);
        }
        Sigma_k.at(j, j) = Sigma.at(maxKSingularIndexes[j], maxKSingularIndexes[j]);
    }

    Matrix Fnew = U_k * Sigma_k;

    double minDistance;
    std::size_t bestClass = 10;

    for (const auto& [label, classCenter] : classCenters) {
        double distance = (Fnew - classCenter).frobeniusNorm();
        if (bestClass == 10 || distance < minDistance) {
            minDistance = distance;
            bestClass = label;
        }
    }

    return bestClass;
}

auto computeClassCenters(const std::vector<Matrix>& trainingData, const std::vector<std::size_t>& labels, std::size_t k)
    -> std::unordered_map<std::size_t, Matrix> {

    std::unordered_map<std::size_t, std::vector<Matrix>> classFeatures;
    for (std::size_t i = 0; i != trainingData.size(); ++i) {
        auto [U, Sigma, V] = trainingData[i].svdDecomposition();
        
        std::vector<double> singularValues;
        for (std::size_t j = 0; j != trainingData[i].getCols(); ++j) {
            singularValues.push_back(trainingData[i].at(j, j));
        }
        auto maxKSingularIndexes = findTopKIndices(singularValues, k);

        Matrix U_k(U.getRows(), k);
        Matrix Sigma_k(k, k);
        for (std::size_t j = 0; j != k; ++j) {
            for (std::size_t r = 0; r != U.getRows(); ++r) {
                U_k.at(r, j) = U.at(r, maxKSingularIndexes[j]);
            }
            Sigma_k.at(j, j) = Sigma.at(maxKSingularIndexes[j], maxKSingularIndexes[j]);
        }

        classFeatures[labels[i]].emplace_back(U_k * Sigma_k);
    }

    std::unordered_map<std::size_t, Matrix> classCenters;
    for (const auto& [label, features] : classFeatures) {
        Matrix meanVector(features[0].getRows(), features[0].getCols(), 0.0);

        for (const auto& feature : features) {
            meanVector = meanVector + feature;
        }

        classCenters[label] = meanVector / features.size();
    }

    return classCenters;
}
