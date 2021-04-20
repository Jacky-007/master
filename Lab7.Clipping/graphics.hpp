#include "geometry.hpp"

using namespace GEO;

typedef int OutCode;
// @TODO: please implement line_clip & polygon_clip algorithm in Graphics.cpp
// clip_min contains (x_min ,y_min)
// clip_max contains (x_max, y_max)
OutCode calc_OutCode(const Vector2 &P, const Vector2 &clip_min,
                     const Vector2 &clip_max);

bool line_clip_CohenSutherland(Vector2 &P0, Vector2 &P1,
                               const Vector2 &clip_min,
                               const Vector2 &clip_max);

std::vector<Vector2> polygon_clip(const std::vector<Vector2> &poly,
                                  const Vector2 &clip_min,
                                  const Vector2 &clip_max);

// implement draw line with midpoint-bresenham algorithm
void draw_line(int src_x, int src_y, int dst_x, int dst_y,
			 std::vector<std::pair<int, int>> &buffer);

template <typename TVector>
void draw_polygon(std::vector<TVector> &poly,
                  std::vector<std::pair<int, int>> &buffer) {
  for (int i = 0, j; i < poly.size(); i++) {
    j = (i + 1 == poly.size()) ? 0 : i + 1;
    draw_line(poly[i].x(), poly[i].y(), poly[j].x(), poly[j].y(), buffer);
  }
}

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
