#include "geometry.hpp"
#include "windows.h"
#include <string>

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

namespace DIM2 {

// false : outside, true : inside or on polygon
bool is_point_inside_polygon(const Point &p, const Polygon &poly) {
  // @TODO: implement here
	int nCount = poly.size();
	int nCross = 0;
	for (int i = 0; i < nCount; i++)
	{
		Point p1 = poly[i];
		Point p2 = poly[(i + 1) % nCount];// 点P1与P2形成连线  

		if (p1.y == p2.y)
			continue;
		if (p.y < min(p1.y, p2.y))
			continue;
		if (p.y >= max(p1.y, p2.y))
			continue;
		// 求交点的x坐标（由直线两点式方程转化而来）   

		double x = (double)(p.y - p1.y) * (double)(p2.x - p1.x) / (double)(p2.y - p1.y) + p1.x;

		// 只统计p1p2与p向右射线的交点  
		if (x > p.x)
		{
			nCross++;
		}

	}
	if ((nCross % 2) == 1) return true;


  return false;

}

// Computational geometry-rapid rejection experiment and straddle experiment
bool is_intersection(const Segment &A, const Point &p) {
  // @TODO: implement here
	Vector a(A.e.x - A.s.x, A.e.y - A.s.y);
	Vector b(p.x - A.s.x, p.y - A.s.y);
	float r;
	r = a.cross_prod(b);
	r = int(r + 0.5);
	if (r == 0 and p.x <= max(A.e.x, A.s.x) and p.y <= max(A.e.y, A.s.y) and p.x >= min(A.e.x, A.s.x) and p.y >=min(A.e.y, A.s.y))
	{
		return true;
	}
  return false;

}

// return false means no intersection
// the intersection point should store in 'inter_point'
bool calc_intersection(const Segment &A, const Segment &B, Point &inter_point) {
  // @TODO: implement here
  // ax + by + c = 0
	float a1, b1, c1, a2, b2, c2, x, y;
	a1 = A.s.y - A.e.y;
	b1 = A.e.x - A.s.x;
	c1 = A.s.x * A.e.y - A.e.x * A.s.y;
	a2 = B.s.y - B.e.y;
	b2 = B.e.x - B.s.x;
	c2 = B.s.x * B.e.y - B.e.x * B.s.y;
	x = (b1 * c2 - c1 * b2) / (b2 * a1 - a2 * b1);
	y = (a1 * c2 - a2 * c1) / (a2 * b1 - a1 * b2);
	inter_point.x = x;
	inter_point.y = y;
	if (is_intersection(A, inter_point) and is_intersection(B, inter_point))
	{
		return true;
	}
  return false;
}

} // namespace DIM2
