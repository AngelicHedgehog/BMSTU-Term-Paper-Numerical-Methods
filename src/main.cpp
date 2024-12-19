#include <iostream>

#include "utils.hpp"


int main() {    
    auto trainImages = loadMNISTImages("../data/train-images-idx3-ubyte");
    auto trainLabels = loadMNISTLabels("../data/train-labels-idx1-ubyte");

    auto testImages = loadMNISTImages("../data/t10k-images-idx3-ubyte");
    auto testLabels = loadMNISTLabels("../data/t10k-labels-idx1-ubyte");

    


    return 0;
}
