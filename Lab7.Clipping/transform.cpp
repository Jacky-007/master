#include <iostream>
#include "geometry.hpp"
using namespace GEO;

int main() {
    GEO::Vector2i test_int_vec;
    // std::cin >> test_int_vec;

    GEO::Matrix3 test_one = GEO::Matrix3::identity();
    GEO::Matrix3 test_mat;
    std::cin >> test_mat;
    std::cout << test_mat * test_one << "\n";
    return 0;
}