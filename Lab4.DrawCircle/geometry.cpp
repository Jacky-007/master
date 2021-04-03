#include "geometry.hpp"

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

// implement draw circle with simple algorithm
void draw_circle_simple(int xc, int yc, int r,
                                    std::vector<std::pair<int, int>> &buffer) {
	for (int i = 0; i <= r/sqrt(2); i++) {
		int y = round(sqrt(pow(r, 2) - pow(i, 2)));
		int x = i;
		buffer.emplace_back(x + xc, y + yc);
		buffer.emplace_back(-x + xc, y + yc);
		buffer.emplace_back(x + xc, -y + yc);
		buffer.emplace_back(-x + xc, -y + yc);
		buffer.emplace_back(y + xc, x + yc);
		buffer.emplace_back(-y + xc, x + yc);
		buffer.emplace_back(y + xc, -x + yc);
		buffer.emplace_back(-y + xc, -x + yc);
	}
}

// implement draw circle with midpoint algorithm
void draw_circle_midpoint_bresenham(int xc, int yc, int r,
                                    std::vector<std::pair<int, int>> &buffer) {
	int d = 1.25 - r;
	int x = 0, y = r;
	while (x <= y)
	{
		if (d < 0) {
			d = d + 2*x + 3;
			x++;
			buffer.emplace_back(x + xc, y + yc);
			buffer.emplace_back(-x + xc, y + yc);
			buffer.emplace_back(x + xc, -y + yc);
			buffer.emplace_back(-x + xc, -y + yc);
			buffer.emplace_back(y + xc, x + yc);
			buffer.emplace_back(-y + xc, x + yc);
			buffer.emplace_back(y + xc, -x + yc);
			buffer.emplace_back(-y + xc, -x + yc);
		}
		else
		{
			d = d + 2 * (x - y) + 5;
			x++;
			y--;
			buffer.emplace_back(x + xc, y + yc);
			buffer.emplace_back(-x + xc, y + yc);
			buffer.emplace_back(x + xc, -y + yc);
			buffer.emplace_back(-x + xc, -y + yc);
			buffer.emplace_back(y + xc, x + yc);
			buffer.emplace_back(-y + xc, x + yc);
			buffer.emplace_back(y + xc, -x + yc);
			buffer.emplace_back(-y + xc, -x + yc);
		}
	}
}

// implement draw ellipse with midpoint algorithm
void draw_ellipse_midpoint_bresenham(int xc, int yc, int rx, int ry,
                                     std::vector<std::pair<int, int>> &buffer) {

}
