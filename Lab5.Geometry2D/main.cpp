#include "basewin.hpp"
#include "geometry.hpp"
#include "memdc.hpp"
#include "windowsx.h"
#include "wingdi.h"

#include <cmath>
#include <cstdio>
#include <stdio.h>
#include <utility>
#include <vector>

#pragma comment(lib, "msimg32")

class DrawWindow : public BaseWindow<DrawWindow> {
public:
  DrawWindow() {
    // @NOTE: press 'Space' to switch mode between INTERSECTION and POLYGON
    mode = INTERSECTION;
    is_drawing = false;
    is_holding = false;
    pen_color = RGB(200, 60, 0);
    test_poly = {{400, 20},  {340, 210}, {150, 270}, {340, 330},
                 {400, 520}, {460, 330}, {650, 270}, {460, 210}};
  }

  PCWSTR ClassName() const override { return L"Draw Window Class"; }
  LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

  void OnLButtonDown(int x, int y, DWORD flags);
  void OnRButtonDown(int x, int y, DWORD flags);
  void OnLButtonUp(int x, int y, DWORD flags);
  void OnMouseMove(int x, int y, DWORD flags);
  void OnPaint();

  enum DrawMode {
    EMPTY = 0,
    BRUSH,
    LINE,
    CIRCLE,
    ELLIPSE,
    POLYGON,
    INTERSECTION
  };

  enum { MASK_COLOR = RGB(255, 255, 255) };

private:
  MemoryDC background;
  MemoryDC preview;
  MemoryDC buffer;

  DrawMode mode;
  bool is_drawing;
  bool is_holding;
  bool need_clear;
  int src_x, src_y;
  int dst_x, dst_y;
  std::vector<std::pair<int, int>> pixel_buffer;

  DIM2::Polygon test_poly;
  std::vector<DIM2::Segment> seg_list;

  // @TODO: Implement a brush class to control the drawing thickness, color and
  // other attributes
  COLORREF pen_color = RGB(200, 60, 0);
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine,
                    int nCmdShow) {
  DrawWindow win;

  if (!win.Create(L"Lab3.DrawCircle", WS_OVERLAPPEDWINDOW)) {
    return 0;
  }

  ShowWindow(win.Window(), nCmdShow);

  // Run the message loop.

  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}

// Implement your window process here
LRESULT DrawWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
  switch (uMsg) {
  case WM_CREATE: {
    RECT rc;
    GetClientRect(m_hwnd, &rc);

    buffer.resize(rc.right, rc.bottom);
    preview.resize(rc.right, rc.bottom);
    background.resize(rc.right, rc.bottom);

    rc = {0, 0, background.get_width(), background.get_height()};
    FillRect(background, &rc, (HBRUSH)GetStockObject(LTGRAY_BRUSH));

    rc = {0, 0, preview.get_width(), preview.get_height()};
    FillRect(preview, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));

    return 0;
  }

  case WM_DESTROY:
    PostQuitMessage(0);
    return 0;

  case WM_RBUTTONDOWN:
    OnRButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
    return 0;

  case WM_PAINT:
    OnPaint();
    return 0;

  case WM_LBUTTONDOWN:
    OnLButtonDown(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
    return 0;

  case WM_LBUTTONUP:
    OnLButtonUp(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
    return 0;

    // https://stackoverflow.com/questions/53958727/performance-efficient-way-of-setting-pixels-in-gdi
  case WM_MOUSEMOVE:
    OnMouseMove(GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam), (DWORD)wParam);
    return 0;

  case WM_KEYDOWN:
    if (wParam == VK_SPACE) {
      mode = mode == POLYGON ? INTERSECTION : POLYGON;
      InvalidateRect(m_hwnd, NULL, FALSE);
      return 0;
    }

  default:
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
  }
  return TRUE;
}

void DrawWindow::OnLButtonDown(int x, int y, DWORD flags) {
  if (mode == EMPTY)
    return;

  if (mode == POLYGON) {
    src_x = x, src_y = y;

    if (DIM2::is_point_inside_polygon(DIM2::Point(src_x, src_y), test_poly)) {
      OutputDebugStringW(L"The point is in the polygon\n");
    } else {
      OutputDebugStringW(L"The point is not in the polygon\n");
    }
    is_drawing = false;
    is_holding = false;
    return;
  }

  if (is_drawing) {
    // end up drawing
    is_drawing = false;
    dst_x = x, dst_y = y;

    if (mode == INTERSECTION) {
      auto src = DIM2::Point(src_x, src_y);
      auto dst = DIM2::Point(dst_x, dst_y);
      auto inter_point = DIM2::Point(rand() % preview.get_width(),
                                     rand() % preview.get_height());

      auto curr_seg = DIM2::Segment{src, dst};
      pixel_buffer.resize(0);

      // calculate last segment and current segment intersection each drawing
      if (!seg_list.empty() &&
          calc_intersection(seg_list.back(), curr_seg, inter_point)) {
        draw_circle_midpoint_bresenham(inter_point.x, inter_point.y, 3,
                                       pixel_buffer);
      }

      seg_list.push_back(curr_seg);

      for (auto const &pixel : pixel_buffer) {
        SetPixelV(preview, pixel.first, pixel.second, RGB(0, 0, 0));
      }
    }

    // set preview layer to background
    TransparentBlt(background, 0, 0, preview.get_width(), preview.get_height(),
                   preview, 0, 0, preview.get_width(), preview.get_height(),
                   MASK_COLOR);
  }

  else {
    // start up drawing
    src_x = x, src_y = y;
    is_drawing = true;
    is_holding = true;
  }

  InvalidateRect(m_hwnd, NULL, FALSE);
}

void DrawWindow::OnLButtonUp(int x, int y, DWORD flags) {
  if (is_holding) {
    is_holding = false;

    if (mode == BRUSH) {
      // set preview layer to background
      is_drawing = false;
      TransparentBlt(background, 0, 0, preview.get_width(),
                     preview.get_height(), preview, 0, 0, preview.get_width(),
                     preview.get_height(), MASK_COLOR);
    }
  }
}

void DrawWindow::OnMouseMove(int x, int y, DWORD flags) {
  if (is_drawing) {

    if (mode != BRUSH) {
      RECT rc = {0, 0, preview.get_width(), preview.get_height()};
      FillRect(preview, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
      pixel_buffer.resize(0);
    }

    switch (mode) {
    case LINE:
    case INTERSECTION:
      draw_line(src_x, src_y, x, y, pixel_buffer);
      break;

    case CIRCLE: {
      int xc = (x + src_x) / 2;
      int yc = (y + src_y) / 2;
      int rx = abs(x - src_x);
      int ry = abs(y - src_y);
      draw_circle_midpoint_bresenham(xc, yc, std::sqrt(rx * rx + ry * ry) * 0.5,
                                     pixel_buffer);
      break;
    }

    case ELLIPSE: {
      int xc = (x + src_x) / 2;
      int yc = (y + src_y) / 2;
      int rx = abs(x - src_x) / 2;
      int ry = abs(y - src_y) / 2;
      draw_ellipse_midpoint_bresenham(xc, yc, rx, ry, pixel_buffer);
      break;
    }

    case BRUSH: {
      // still not work right for now
      if (is_holding) {
        SetPixelV(preview, x, y, pen_color);
      }
      break;
    }
    }

    for (auto &i : pixel_buffer) {
      SetPixelV(preview, i.first, i.second, pen_color);
    }

    InvalidateRect(m_hwnd, NULL, FALSE);
  }
}
void DrawWindow::OnPaint() {
  PAINTSTRUCT ps;
  HDC hdc = BeginPaint(m_hwnd, &ps);

  BitBlt(buffer, 0, 0, background.get_width(), background.get_height(),
         background, 0, 0, SRCCOPY);

  TransparentBlt(buffer, 0, 0, preview.get_width(), preview.get_height(),
                 preview, 0, 0, preview.get_width(), preview.get_height(),
                 MASK_COLOR);

  // draw test polygon to background
  if (mode == POLYGON) {
    pixel_buffer.resize(0);
    int poly_size = test_poly.size();
    for (int i = 0; i < poly_size; i++) {
      int j = (i + 1) % poly_size;
      draw_line(test_poly[i].x, test_poly[i].y, test_poly[j].x, test_poly[j].y,
                pixel_buffer);
    }
    for (auto const &pixel : pixel_buffer) {
      SetPixelV(buffer, pixel.first, pixel.second, RGB(0, 0, 0));
    }
  }

  BitBlt(hdc, 0, 0, buffer.get_width(), buffer.get_height(), buffer, 0, 0,
         SRCCOPY);

  // draw test polygon here
  // if (mode == POLYGON) {
  //   std::vector<POINT> gdi_poly;
  //   for (auto &p : test_poly.p) {
  //     POINT gdi_point;
  //     gdi_point.x = p.x;
  //     gdi_point.y = p.y;
  //     gdi_poly.push_back(gdi_point);
  //   }
  //   Polygon(hdc, gdi_poly.data(), gdi_poly.size());
  // }

  EndPaint(m_hwnd, &ps);
}

void DrawWindow::OnRButtonDown(int x, int y, DWORD flags) {
  // cancel drawing
  if (is_drawing) {
    is_drawing = false;
    is_holding = false;

    // flush preview layer
    RECT rc = {0, 0, preview.get_width(), preview.get_height()};
    FillRect(preview, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
    InvalidateRect(m_hwnd, NULL, FALSE);
  }
}
