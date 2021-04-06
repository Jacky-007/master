#pragma once
#include <utility>
#include <vector>

// implement draw line with midpoint-bresenham algorithm
void draw_line(int src_x, int src_y, int dst_x, int dst_y,
               std::vector<std::pair<int, int>> &buffer);

void draw_symmetry_point(int xc, int yc, int x, int y,
                         std::vector<std::pair<int, int>> &buffer);

// implement draw circle with midpoint algorithm
void draw_circle_midpoint_bresenham(int xc, int yc, int r,
                                    std::vector<std::pair<int, int>> &buffer);

// implement draw ellipse with midpoint-bresenham algorithm
void draw_ellipse_midpoint_bresenham(int xc, int yc, int rx, int ry,
                                     std::vector<std::pair<int, int>> &buffer);

// implement determine whether the point is within the polygon
void is_point_within_polygon(
    int src_x, int src_y, std::vector<std::pair<int, int>> polygon_point_list,
    bool &flg);

// implement calculate the intersection of two lines
void draw_intersection(int src_x1, int src_y1, int dst_x1, int dst_y1,
                       int src_x2, int src_y2, int dst_x2, int dst_y2,
                       std::pair<int, int> &point);

namespace DIM2 {
struct Vector {
  float x, y;
  Vector(float x, float y) : x(x), y(y) {}

  Vector operator+(const Vector &rhs) const { return  Vector(x + rhs.x, y + rhs.y); }
  Vector operator-(const Vector &rhs) const { return  Vector(x - rhs.x, y - rhs.y); }
  Vector operator*(float t) const { return   Vector(x * t, y * t); }
  // dot product
  float dot_prod(const Vector &rhs) const { return x * rhs.x + y * rhs.y; }

  // cross product in 2D return the directed area of triangle between u and v
  float cross_prod(const Vector &rhs) const { return x * rhs.y - y * rhs.x; }
};

typedef Vector Point;
typedef std::vector<Point> Polygon;

struct Line {
  Point o;
  Vector dir;
};

struct Segment {
  // start, end
  Point s, e;
};

inline int sgn(float x) { return x == 0 ? 0 : x < 0 ? -1 : 1; }

// false : outside, true : inside or on polygon
bool is_point_inside_polygon(const Point &p, const Polygon &poly);

// return false means no intersection
bool is_intersection(const Segment &A, const Point &p);

// the intersection point should store in 'inter_point'
bool calc_intersection(const Segment &u, const Segment &v, Point &inter_point);

} // namespace DIM2

namespace DIM3 {}