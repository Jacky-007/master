#include "geometry.hpp"
#include "windows.h"
#include <string>

namespace GEO {

// implement transform basic function in 2D here
Matrix3 rotate_matrix(float alpha) {
  // @Note: Rotate alpha(in radian measure) around the origin O
  return {cos(alpha), sin(alpha), 0, -sin(alpha), cos(alpha), 0, 0, 0, 1};
}

Matrix3 translate_matrix(float dx, float dy) {
  // @Note: Move (dx, dy)
  return {1, 0, 0, 0, 1, 0, dx, dy, 1};
}

Matrix3 scale_matrix(float sx, float sy) {
  // @Note: scale (sx, sy)
  return {sx, 0, 0, 0, sy, 0, 0, 0, 1};
}

double cross_product(const Vector2 &u, const Vector2 &v) {
  return u.x() * v.y() - v.x() * u.y();
}

// check if point u, v, w make a turn left
bool is_turn_left(const Vector2 &u, const Vector2 &v, const Vector2 &w) {
  return cross_product(v - u, w - u) < 0;
}

} // namespace GEO
