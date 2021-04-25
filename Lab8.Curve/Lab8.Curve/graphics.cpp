#include "graphics.hpp"

/*
 *   Vector Class Usage
 *
 *   Vector2 v = {a, b};
 *   Define a two-dimension vector, and v.x() = a, v.y() = b.
 *   use v.x(), v.y() to access its value in different dimension.
 */

const OutCode INSIDE = 0;
const OutCode LEFT = 1;
const OutCode RIGHT = 2;
const OutCode BOTTOM = 4;
const OutCode TOP = 8;

// calculate point outcodes
OutCode calc_OutCode(const Vector2 &P, const Vector2 &clip_min,
                     const Vector2 &clip_max) {
  OutCode code = INSIDE;

  if (P.x() < clip_min.x()) {
    code |= LEFT;
  } else if (P.x() > clip_max.x()) {
    code |= RIGHT;
  }

  if (P.y() < clip_min.y()) {
    code |= BOTTOM;
  } else if (P.y() > clip_max.y()) {
    code |= TOP;
  }

  return code;
}

// Implement Cohen-Sutherland Line Clipping
// Should return true if line(p0, p1) is inside clip_box
// the result of clipping need be stored in (p0, p1)

bool line_clip_CohenSutherland(Vector2 &p0, Vector2 &p1,
                               const Vector2 &clip_min,
                               const Vector2 &clip_max) {
  bool accept = false;

  return accept;
}

// Implement Sutherland-Hodgman Polygons Clipping
/*
 * @Note: function "is_turn_left(u,v,w)" will help, it checks if vector2 u, v, w
 * make a turn left. You can use it to conveniently judge whether the point is
 * in the box.
 */
std::vector<Vector2> polygon_clip(const std::vector<Vector2> &poly,
                                  const Vector2 &clip_min,
                                  const Vector2 &clip_max) {

  std::vector<Vector2> clip_box = {{clip_min.x(), clip_min.y()},
                                   {clip_max.x(), clip_min.y()},
                                   {clip_max.x(), clip_max.y()},
                                   {clip_min.x(), clip_max.y()}};
  auto output_poly = poly;

  return output_poly;
}

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


int  comb(int m, int k)//(C(m,k))
{
	int i,count = 0;
	for (i = m; i >= k; i--)
	{
		if (k>1)
		{	comb(i - 1, k - 1);	}
		else
		{	count++;	}
	}
	return count;
}


// @TODO: Implement bezier curve algorithm here
//  you can multiply 'Vector' by 'double' (e.g. x * t, type(x) is Vector2) to scale them
void draw_bezier(const std::vector<Vector2> &control_points,
                 std::vector<std::pair<int, int>> &buffer) {
/*
	void draw_line(int src_x, int src_y, int dst_x, int dst_y,
	std::vector<std::pair<int, int>> &buffer)
*/
	//C(n,m) = n!/((n-m)! * m!)
	int num = control_points.size();
	if (num == 2)
	{
		draw_line(control_points[0].x(), control_points[0].y(), 
			control_points[1].x(), control_points[1].y(), 
			buffer);
	}
	else
	{
		for (int i = 0; i < num; i++)
		{
			for (double t = 0; t <= 1; t += 0.01)
			{
				Vector2 res1 = (control_points[i] * pow((1 - t), num - i) * pow(t, i) * comb(num, i));
				Vector2 res2 = res1;
				 draw_line(res2.x(),res2.y(),res1.x(),res1.y(),buffer);
			}
		}	
	}

        /*
				 draw_line((control_points[i] * pow((1 - t), num - i) * pow(t, i) * comb(num, i)).x(), 
					 (control_points[i] * pow((1 - t), num - i) * pow(t, i) * comb(num, i)).y(), 
					 (control_points[i+1] * pow((1 - t), num - i - 1) * pow(t, i+1) * comb(num, i+1)).x(), 
					 (control_points[i+1] * pow((1 - t), num - i - 1) * pow(t, i+1) * comb(num, i+1)).y(), 
					 buffer);
        */
    // calculate the Bezier curve
    // and use draw_line to draw the curve
}