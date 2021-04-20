#include "graphics.hpp"

/*
 *   Vector Class Usage
 *
 *   Vector2 v = {a, b};
 *   Define a two-dimension vector, and v.x() = a, v.y() = b.
 *   use v.x(), v.y() to access its value in different dimension.
 */

const OutCode INSIDE = 0; //(0000)
const OutCode LEFT = 1;  // (0001)
const OutCode RIGHT = 2; // (0010)
const OutCode BOTTOM = 4; // (0100)
const OutCode TOP = 8;  // (1000)

// @TODO: calculate point outcodes
OutCode calc_OutCode(const Vector2 &P, const Vector2 &clip_min,
                     const Vector2 &clip_max) {
  OutCode code = INSIDE;
// Write you code here
  //int x = P.x, y = P.y;
  if (P.x() < clip_min.x()) code |= LEFT;
  if (P.x() > clip_max.x()) code |= RIGHT;
  if (P.y() < clip_min.y()) code |= TOP;
  if (P.y() > clip_max.y()) code |= BOTTOM;
  return code;
}

// @TODO: Implement Cohen-Sutherland Line Clipping
// Should return true if line(p0, p1) is inside clip_box
// the result of clipping need be stored in (p0, p1)

bool line_clip_CohenSutherland(Vector2 &p0, Vector2 &p1,
                               const Vector2 &clip_min,
                               const Vector2 &clip_max) {
  OutCode code0 = calc_OutCode(p0, clip_min, clip_max);
  OutCode code1 = calc_OutCode(p1, clip_min, clip_max);
  auto x0 = p0.x(), y0 = p0.y();
  auto x1 = p1.x(), y1 = p1.y();
  auto min_x = clip_min.x(), min_y = clip_min.y();
  auto max_x = clip_max.x(), max_y = clip_max.y();
  bool accept = false;

    // Write you code here
  while (true)
  {
	  if ((code0 | code1) == 0) {
		  accept = true;
		  break;
	  }
	  if ((code0 & code1) != 0){
		  break;
	  }
	  OutCode code_out = code1 > code0 ? code1 : code0;
	  double x, y;
	  if ((code_out & LEFT) != 0) //在左边
	  {
		  x = clip_min.x();
		  if (x1 == x0)  y = y0;
		  else y = (int)(y0 + (y1 - y0)*(min_x - x0) / (x1 - x0));
	  }
	  else if ((code_out & RIGHT) != 0) //在右边
	  {
		  x = clip_max.x();
		  if (x1 == x0)  y = y0;
		  else y = (int)(y0 + (y1 - y0)*(max_x - x0) / (x1 - x0));
	  }
	  else if ((code_out & BOTTOM) != 0) //在下边
	  {
		  y = clip_max.y();
		  if (y1 == y0)  x = x0;
		  else x = (int)(x0 + (x1 - x0)*(max_y - y0) / (y1 - y0));
	  }
	  else if ((code_out & TOP) != 0) //在上边
	  {
		  y = clip_min.y();
		  if (y1 == y0)  x = x0;
		  else x = (int)(x0 + (x1 - x0)*(min_y - y0) / (y1 - y0));
	  }
	  if (code_out == code0)
	  {
		  x0 = x;
		  y0 = y;
		  p0 = { x0, y0 };
	  }
	  else
	  {
		  x1 = x;
		  y1 = y;
		  p1 = { x1, y1 };
	  }
	  code0 = calc_OutCode(p0, clip_min, clip_max);
	  code1 = calc_OutCode(p1, clip_min, clip_max);
  }

  // Set clip result in p0 & p1
  p0 = {x0, y0};
  p1 = {x1, y1};
  return accept;
}

// @TODO: Implement Sutherland-Hodgman Polygons Clipping
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


  // Write you code here

  //修改的是inputpoly
  //auto input_poly = output_poly;
  std::vector<Vector2> input_poly;
  for (int i = 0; i < output_poly.size(); i++) 
  {		// 每一个顶点
		//下一个顶点为j = i + 1 or 0 if i == size()
		//判断四种情况，并输出响应点到output
	  int j;
	  if (i == (output_poly.size()-1)) j = 0;
	  else j = i + 1;
	  Vector2 p0, p1;
	  p0 = output_poly[i];
	  p1 = output_poly[j];
	  OutCode code0 = calc_OutCode(p0, clip_min, clip_max);
	  OutCode code1 = calc_OutCode(p1, clip_min, clip_max);
	  auto x0 = p0.x(), y0 = p0.y();
	  auto x1 = p1.x(), y1 = p1.y();
	  auto min_x = clip_min.x(), min_y = clip_min.y();
	  auto max_x = clip_max.x(), max_y = clip_max.y();
	  if (((code0 & LEFT) == 0) && ((code1 & LEFT) == 0)) //都在里面
	  {
		  input_poly.push_back(p1);
	  }
	  else if (((code0 & LEFT) != 0) && ((code1 & LEFT) == 0)) //→
	  {
		  double x, y;
		  x = clip_min.x();
		  y = (int)(y0 + (y1 - y0)*(min_x - x0) / (x1 - x0));
		  Vector2 p;
		  p = {x,y};
		  input_poly.push_back(p);
		  input_poly.push_back(p1);
	  }
	  else if (((code0 & LEFT) == 0) && ((code1 & LEFT) != 0)) //←
	  {
		  double x, y;
		  x = clip_min.x();
		  y = (int)(y0 + (y1 - y0)*(min_x - x0) / (x1 - x0));
		  Vector2 p;
		  p = {x,y};
		  input_poly.push_back(p);
	  }
	  
  }
  output_poly = input_poly;


  std::vector<Vector2> input_poly1; //右边界
  for (int i = 0; i < output_poly.size(); i++)
  {		// 每一个顶点
		//下一个顶点为j = i + 1 or 0 if i == size()
		//判断四种情况，并输出响应点到output
	  int j;
	  if (i == (output_poly.size() - 1)) j = 0;
	  else j = i + 1;
	  Vector2 p0, p1;
	  p0 = output_poly[i];
	  p1 = output_poly[j];
	  OutCode code0 = calc_OutCode(p0, clip_min, clip_max);
	  OutCode code1 = calc_OutCode(p1, clip_min, clip_max);
	  auto x0 = p0.x(), y0 = p0.y();
	  auto x1 = p1.x(), y1 = p1.y();
	  auto min_x = clip_min.x(), min_y = clip_min.y();
	  auto max_x = clip_max.x(), max_y = clip_max.y();
	  if (((code0 & RIGHT) == 0) && ((code1 & RIGHT) == 0))
	  {
		  input_poly1.push_back(p1);
	  }
	  else if (((code0 & RIGHT) != 0) && ((code1 & RIGHT) == 0)) //→
	  {
		  double x, y;
		  x = clip_max.x();
		  y = (int)(y0 + (y1 - y0)*(max_x - x0) / (x1 - x0));
		  Vector2 p;
		  p = { x,y };
		  input_poly1.push_back(p);
		  input_poly1.push_back(p1);
	  }
	  else if (((code0 & RIGHT) == 0) && ((code1 & RIGHT) != 0)) //←
	  {
		  double x, y;
		  x = clip_max.x();
		  y = (int)(y0 + (y1 - y0)*(max_x - x0) / (x1 - x0));
		  Vector2 p;
		  p = { x,y };
		  input_poly1.push_back(p);
	  }

  }
  output_poly = input_poly1;

  
  std::vector<Vector2> input_poly2; //下边界
  for (int i = 0; i < output_poly.size(); i++)
  {		// 每一个顶点
		//下一个顶点为j = i + 1 or 0 if i == size()
		//判断四种情况，并输出响应点到output
	  int j;
	  if (i == (output_poly.size() - 1)) j = 0;
	  else j = i + 1;
	  Vector2 p0, p1;
	  p0 = output_poly[i];
	  p1 = output_poly[j];
	  OutCode code0 = calc_OutCode(p0, clip_min, clip_max);
	  OutCode code1 = calc_OutCode(p1, clip_min, clip_max);
	  auto x0 = p0.x(), y0 = p0.y();
	  auto x1 = p1.x(), y1 = p1.y();
	  auto min_x = clip_min.x(), min_y = clip_min.y();
	  auto max_x = clip_max.x(), max_y = clip_max.y();
	  if (((code0 & BOTTOM) == 0) && ((code1 & BOTTOM) == 0))
	  {
		  input_poly2.push_back(p1);
	  }
	  else if (((code0 & BOTTOM) != 0) && ((code1 & BOTTOM) == 0)) //→
	  {
		  double x, y;
		  y = clip_max.y();
		  x = (int)(x0 + (x1 - x0)*(max_y - y0) / (y1 - y0));
		  Vector2 p;
		  p = { x,y };
		  input_poly2.push_back(p);
		  input_poly2.push_back(p1);
	  }
	  else if (((code0 & BOTTOM) == 0) && ((code1 & BOTTOM) != 0)) //←
	  {
		  double x, y;
		  y = clip_max.y();
		  x = (int)(x0 + (x1 - x0)*(max_y - y0) / (y1 - y0));
		  Vector2 p;
		  p = { x,y };
		  input_poly2.push_back(p);
	  }

  }
  output_poly = input_poly2;



  std::vector<Vector2> input_poly3; //上边界
  for (int i = 0; i < output_poly.size(); i++)
  {		// 每一个顶点
		//下一个顶点为j = i + 1 or 0 if i == size()
		//判断四种情况，并输出响应点到output
	  int j;
	  if (i == (output_poly.size() - 1)) j = 0;
	  else j = i + 1;
	  Vector2 p0, p1;
	  p0 = output_poly[i];
	  p1 = output_poly[j];
	  OutCode code0 = calc_OutCode(p0, clip_min, clip_max);
	  OutCode code1 = calc_OutCode(p1, clip_min, clip_max);
	  auto x0 = p0.x(), y0 = p0.y();
	  auto x1 = p1.x(), y1 = p1.y();
	  auto min_x = clip_min.x(), min_y = clip_min.y();
	  auto max_x = clip_max.x(), max_y = clip_max.y();
	  if (((code0 & TOP) == 0) && ((code1 & TOP) == 0))
	  {
		  input_poly3.push_back(p1);
	  }
	  else if (((code0 & TOP) != 0) && ((code1 & TOP) == 0)) //→
	  {

		  double x, y;
		  y = clip_min.y();
		  x = (int)(x0 + (x1 - x0)*(min_y - y0) / (y1 - y0));
		  Vector2 p;
		  p = { x,y };
		  input_poly3.push_back(p);
		  input_poly3.push_back(p1);
	  }
	  else if (((code0 & TOP) == 0) && ((code1 & TOP) != 0)) //←
	  {
		  double x, y;
		  y = clip_min.y();
		  x = (int)(x0 + (x1 - x0)*(min_y - y0) / (y1 - y0));
		  Vector2 p;
		  p = { x,y };
		  input_poly3.push_back(p);
	  }

  }
  output_poly = input_poly3;

  
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