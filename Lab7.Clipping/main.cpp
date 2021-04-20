#include "basewin.hpp"
#include "geometry.hpp"
#include "graphics.hpp"
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
    mode = EMPTY;
    is_drawing = false;
    is_holding = false;
    need_clip = true;
    pen_color = RGB(200, 60, 0);
    test_poly = {{400, 20, 1},  {340, 210, 1}, {150, 270, 1}, {340, 330, 1},
                 {400, 520, 1}, {460, 330, 1}, {650, 270, 1}, {460, 210, 1}};
    clip_dx = 100;
    transform_mat = GEO::Matrix3::identity();
  }

  PCWSTR ClassName() const override { return L"Draw Window Class"; }
  LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;

  void OnLButtonDown(int x, int y, DWORD flags);
  void OnRButtonDown(int x, int y, DWORD flags);
  void OnLButtonUp(int x, int y, DWORD flags);
  void OnMouseMove(int x, int y, DWORD flags);
  void OnKeyPress(WPARAM key);
  void OnPaint();
  void OnCreate();
  void TransformTestPolygon();

  void ClearPreview() {
    RECT rc = {0, 0, preview.get_width(), preview.get_height()};
    FillRect(preview, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
  }

  void ClearBoard() {
    RECT rc = {0, 0, board.get_width(), board.get_height()};
    FillRect(board, &rc, (HBRUSH)GetStockObject(WHITE_BRUSH));
  }

  void ClearBackground() {
    RECT rc = {0, 0, background.get_width(), background.get_height()};
    FillRect(background, &rc, (HBRUSH)GetStockObject(LTGRAY_BRUSH));
  }

  void TransferToBuffer() {
    BitBlt(buffer, 0, 0, background.get_width(), background.get_height(),
           background, 0, 0, SRCCOPY);

    TransparentBlt(buffer, 0, 0, board.get_width(), board.get_height(), board,
                   0, 0, board.get_width(), board.get_height(), MASK_COLOR);

    TransparentBlt(buffer, 0, 0, preview.get_width(), preview.get_height(),
                   preview, 0, 0, preview.get_width(), preview.get_height(),
                   MASK_COLOR);
  }

  enum DrawMode { EMPTY = 0, BRUSH, LINE, CIRCLE, ELLIPSE, POLYGON };

  enum { MASK_COLOR = RGB(255, 255, 255) };

private:
  MemoryDC background;
  MemoryDC preview;
  MemoryDC board;
  MemoryDC buffer;

  DrawMode mode;
  bool is_drawing;
  bool is_holding;
  bool need_clip;
  int src_x, src_y;
  int dst_x, dst_y;

  std::vector<GEO::Vector2> controll_points;
  std::vector<std::pair<int, int>> pixel_buffer;
  std::vector<GEO::Vector3> test_poly;
  std::vector<std::pair<GEO::Vector2, GEO::Vector2>> aux_lines;

  RECT rc;
  float clip_dx;
  GEO::Matrix3 transform_mat;

  // other attributes
  COLORREF pen_color = RGB(200, 60, 0);
};

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine,
                    int nCmdShow) {
  DrawWindow win;

  if (!win.Create(L"Lab7.Clipping", WS_OVERLAPPEDWINDOW)) {
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
    GetClientRect(m_hwnd, &rc);
    OnCreate();
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
    OnKeyPress(wParam);
    InvalidateRect(m_hwnd, NULL, FALSE);
    return 0;

  default:
    return DefWindowProc(m_hwnd, uMsg, wParam, lParam);
  }
  return TRUE;
}

void DrawWindow::OnLButtonDown(int x, int y, DWORD flags) {
  if (mode == EMPTY)
    return;

  if (is_drawing) {
    // end up drawing
    is_drawing = false;
    dst_x = x, dst_y = y;

    // set preview layer to background
    TransparentBlt(board, 0, 0, preview.get_width(), preview.get_height(),
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
      ClearPreview();
      pixel_buffer.resize(0);
    }

    switch (mode) {
    case LINE:
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

  // Prepare Background elements
  GEO::Vector2 clip_min = {rc.left + clip_dx, rc.top + clip_dx};
  GEO::Vector2 clip_max = {rc.right - clip_dx, rc.bottom - clip_dx};
  std::vector<GEO::Vector2> clip_box = {{clip_min.x(), clip_min.y()},
                                        {clip_max.x(), clip_min.y()},
                                        {clip_max.x(), clip_max.y()},
                                        {clip_min.x(), clip_max.y()}};
  ClearBackground();
  // Draw aux_line to background
  pixel_buffer.resize(0);
  for (auto line : aux_lines) {
    if (!need_clip || line_clip_CohenSutherland(line.first, line.second,
                                                clip_min, clip_max)) {
      draw_line(line.first.x(), line.first.y(), line.second.x(),
                line.second.y(), pixel_buffer);
    }
  }
  for (auto const &pixel : pixel_buffer) {
    SetPixelV(background, pixel.first, pixel.second, RGB(150, 150, 150));
  }

  pixel_buffer.resize(0);
  draw_polygon(clip_box, pixel_buffer);
  for (auto const &pixel : pixel_buffer) {
    SetPixelV(background, pixel.first, pixel.second, RGB(0, 0, 0));
  }

  pixel_buffer.resize(0);
  std::vector<Vector2> clip_poly;
  for (auto point : test_poly) {
    clip_poly.push_back({point.x(), point.y()});
  }
  if (need_clip) {
    clip_poly = polygon_clip(clip_poly, clip_min, clip_max);
  }
  draw_polygon(clip_poly, pixel_buffer);
  for (auto const &pixel : pixel_buffer) {
    SetPixelV(background, pixel.first, pixel.second, RGB(221, 80, 68));
  }

  TransferToBuffer();
  BitBlt(hdc, 0, 0, buffer.get_width(), buffer.get_height(), buffer, 0, 0,
         SRCCOPY);

  EndPaint(m_hwnd, &ps);
}

void DrawWindow::OnCreate() {
  buffer.resize(rc.right, rc.bottom);
  preview.resize(rc.right, rc.bottom);
  board.resize(rc.right, rc.bottom);
  background.resize(rc.right, rc.bottom);
  // buffer <- background <- board <- preview

  ClearPreview();
  ClearBoard();
  ClearBackground();

  for (int i = rc.left; i < rc.right; i += 40) {
    Vector2 a = {i, rc.top};
    Vector2 b = {i + i * 0.3f, rc.bottom};
    aux_lines.emplace_back(a, b);
  }

  for (int j = rc.top; j < rc.bottom; j += 30) {
    Vector2 a = {rc.left, j};
    Vector2 b = {rc.right, j + j * 0.2f};
    aux_lines.emplace_back(a, b);
  }
}

void DrawWindow::OnRButtonDown(int x, int y, DWORD flags) {
  // cancel drawing
  if (is_drawing) {
    is_drawing = false;
    is_holding = false;

    // flush preview layer
    ClearPreview();
    InvalidateRect(m_hwnd, NULL, FALSE);
  }
}

void DrawWindow::OnKeyPress(WPARAM key) {
  switch (key) {
  case VK_UP: {
    clip_dx = max(0.0f, clip_dx - 2);
    break;
  }
  case VK_DOWN: {
    clip_dx = min(min(rc.bottom, rc.right) / 2, clip_dx + 2);
    break;
  }
  case VK_SPACE: {
    TransformTestPolygon();
    break;
  }
  case 'C': {
    need_clip = !need_clip;
    break;
  }
  }
}

void DrawWindow::TransformTestPolygon() {
  // move the origin O to the center of polygon
  // transform polygon with transform_mat

  GEO::Vector2 origin = {rc.right * 0.5f, rc.bottom * 0.5f};

  transform_mat = GEO::translate_matrix(-origin.x(), -origin.y());
  // transform_mat = transform_mat * GEO::scale_matrix(0.99f, 0.99f);
  transform_mat = transform_mat * GEO::rotate_matrix(0.05f);
  transform_mat = transform_mat * GEO::translate_matrix(origin.x(), origin.y());

  for (auto &p : test_poly) {
    p = p * transform_mat;
  }
}