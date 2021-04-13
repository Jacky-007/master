#include <iostream>
#include "geometry.hpp"
using namespace GEO;

int main() {
    GEO::Matrix3x3 test_mat = GEO::Matrix3x3::one();
    std::cout << test_mat;
    auto result = test_mat * test_mat;
    std::cout << result;
    return 0;
}