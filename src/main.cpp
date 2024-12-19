#include <iostream>

#include "classifier.hpp"
#include "utils.hpp"


int main() {    
    auto trainImages = loadMNISTImages("../data/train-images-idx3-ubyte");
    auto trainLabels = loadMNISTLabels("../data/train-labels-idx1-ubyte");

    auto testImages = loadMNISTImages("../data/t10k-images-idx3-ubyte");
    auto testLabels = loadMNISTLabels("../data/t10k-labels-idx1-ubyte");

    std::cout << "MNIST data prepared.\n";

    auto trainClassCenters = computeClassCenters(testImages, testLabels, 14);
    std::cout << "Centers calculated.\n";

    std::size_t predicted = 0;
    for (std::size_t i = 0; i != testImages.size(); ++i) {
        auto res = classify(testImages[i], trainClassCenters);
        if (res != testLabels[i]) {
            ++predicted;
        }
    }

    std::cout << "Quality: " << predicted * 1.0 / testImages.size() << std::endl;

    return 0;
}
