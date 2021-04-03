#pragma once

#ifndef __DRAW_LINE_LINE_H__
#define __DRAW_LINE_LINE_H__

#include "global.h"
#include <vector>

std::vector<Point> draw_line_DDA(Point p_src, Point p_dst);
std::vector<Point> draw_line_bresenham(Point p_src, Point p_dst);

#endif