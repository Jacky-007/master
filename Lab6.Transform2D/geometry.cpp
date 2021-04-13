#include "geometry.hpp"
#include "windows.h"
#include <string>
#include <cmath>
namespace GEO {

// @TODO: implement transform basic function in 2D here
Matrix3x3 rotate_matrix(float alpha) {
  // @Note: Rotate alpha(in radian measure) around the origin O
	Matrix<3, 3> A;
	A = { cos(alpha),sin(alpha),0,-sin(alpha),cos(alpha),0,0,0,1 };
	return A;
}

Matrix3x3 translate_matrix(float dx, float dy) {
  // @Note: Move (dx, dy)
	Matrix<3, 3> A;
	A = { 1,0,0,0,1,0,dx,dy,1 };
	return A;

}

Matrix3x3 scale_matrix(float sx, float sy) {
  // @Note: scale (sx, sy)
	Matrix<3, 3> A;
	A = { sx,0,0,0,sy,0,0,1 };
	return A;
}





// previous answer
// implement draw line with midpoint-bresenham algorithm
void draw_line(int src_x, int src_y, int dst_x, int dst_y,
               std::vector<std::pair<int, int>> &buffer) {
  bool reverse_xy = false;
  if (std::abs(src_x - dst_x) < std::abs(src_y - dst_y)) {
    std::swap(src_x, src_y);
    std::swap(dst_x, dst_y);
    reverse_xy = true;
  }

  if (src_x > dst_x) {
    std::swap(src_x, dst_x);
    std::swap(src_y, dst_y);
  }

  int dx = dst_x - src_x;
  int dy = dst_y - src_y;
  int derr2 = std::abs(dy) * 2, err2 = 0;
  int y = src_y, y_inc = dst_y > src_y ? 1 : -1;

  for (int x = src_x; x <= dst_x; x++) {
    if (reverse_xy) {
      buffer.emplace_back(y, x);
    } else {
      buffer.emplace_back(x, y);
    }
    err2 += derr2;
    if (err2 > dx) {
      y += y_inc;
      err2 -= dx * 2;
    }
  }
}

void draw_symmetry_point(int xc, int yc, int x, int y,
                         std::vector<std::pair<int, int>> &buffer) {
  buffer.insert(
      buffer.end(),
      {{xc + x, yc + y}, {xc - x, yc + y}, {xc + x, yc - y}, {xc - x, yc - y}});
}

// implement draw circle with midpoint algorithm
void draw_circle_midpoint_bresenham(int xc, int yc, int r,
                                    std::vector<std::pair<int, int>> &buffer) {
  int x = 0, y = r;
  int d = 5 - 4 * r;

  while (x <= y) {
    // 插入八分圆区域的8个对称点
    draw_symmetry_point(xc, yc, x, y, buffer);
    draw_symmetry_point(xc, yc, y, x, buffer);

    if (d <= 0) {
      d += 4 * (2 * x + 3);
    } else {
      d += 4 * (2 * (x - y) + 5);
      y--;
    }
    x++;
  }
}

// implement draw ellipse with midpoint algorithm
void draw_ellipse_midpoint_bresenham(int xc, int yc, int rx, int ry,
                                     std::vector<std::pair<int, int>> &buffer) {

  int dx, dy, d1, x, y;
  x = 0;
  y = ry;
  int rx2 = rx * rx;
  int ry2 = ry * ry;

  // Initial decision parameter of region 1
  d1 = 4 * (ry * ry) - 4 * (rx * rx * ry) + rx * rx;
  dx = 2 * ry * ry * x;
  dy = 2 * rx * rx * y;

  // For region 1
  while (dx < dy) {
    // Print points based on 4-way symmetry
    draw_symmetry_point(xc, yc, x, y, buffer);

    // Checking and updating value of
    // decision parameter based on algorithm
    if (d1 < 0) {
      x++;
      dx = dx + (2 * ry2);
      d1 = d1 + 4 * (dx + (ry2));
    } else {
      x++;
      y--;
      dx = dx + (2 * ry2);
      dy = dy - (2 * rx2);
      d1 = d1 + 4 * (dx - dy + ry2);
    }
  }

  // Decision parameter of region 2
  int d2 = (ry2 * (2 * x + 1) * (2 * x + 1)) +
           4 * ((rx * rx) * ((y - 1) * (y - 1))) - 4 * (rx2 * ry2);

  // Plotting points of region 2
  while (y >= 0) {
    // Print points based on 4-way symmetry
    draw_symmetry_point(xc, yc, x, y, buffer);

    // Checking and updating parameter
    // value based on algorithm
    if (d2 > 0) {
      y--;
      dy = dy - (2 * rx2);
      d2 = d2 + 4 * (rx2 - dy);
    } else {
      y--;
      x++;
      dx = dx + (2 * ry2);
      dy = dy - (2 * rx2);
      d2 = d2 + 4 * (dx - dy + rx2);
    }
  }
}
} // namespace GEO
