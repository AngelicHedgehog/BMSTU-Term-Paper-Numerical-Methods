#include <iostream>

#include "matrix.hpp"

int main() {

    Matrix m(2, 3, -1);

    m.at(0, 0) = 1.5;
    m.at(1, 2) = 100.001;

    std::cout << m * m.transpose() << '\n';

    return 0;
}