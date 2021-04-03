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

// implement draw circle with simple algorithm
void draw_circle_simple(int xc, int yc, int r,
                                    std::vector<std::pair<int, int>> &buffer);

// implement draw ellipse with midpoint-bresenham algorithm
void draw_ellipse_midpoint_bresenham(int xc, int yc, int rx, int ry,
                                     std::vector<std::pair<int, int>> &buffer);