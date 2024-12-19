#include <iostream>

#include "matrix.hpp"


int main() {

    Matrix m(3, 3, 1);

    m.at(0, 0) = 1.5;
    m.at(2, 2) = 100;

    auto [U, S, V] = m.svdDecomposition();

    std::cout << U << '\n';
    std::cout << S << '\n';
    std::cout << V << '\n';

    std::cout << (m - U * S * V.transpose()).frobeniusNorm() << '\n';

    return 0;
}
